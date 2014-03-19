/**
  Copyright (C) 2014  SpiffSpaceman

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>
**/


#include "worker.h"
#include "misc_util.h"
#include "amibroker_feed.h"

#include <windows.h> 
#include <process.h>

#include <iostream>
#include <sstream>
#include <limits>
 

/**
 * Read Scrips and setup DS. Start Timers and start AB thread
 */
Worker::Worker(){
                                                                           // _T()  - character set Neutral
    Event_RTD_Update = CreateEvent( NULL, false, TRUE, _T("RTD_UPDATE") ); // Manual Reset = false - Event resets to nonsignaled on 1 wait release                                                                
    Event_StopNow    = CreateEvent( NULL, true,  FALSE, NULL );                // Initialize state to TRUE to read data once on start
    Event_Stopped    = CreateEvent( NULL, true,  FALSE, NULL );
    AB_timer         = CreateWaitableTimer( NULL, false,NULL );

    today_date       = MiscUtil::getTime("%Y%m%d");                        // Get todays date - yyyymmdd

    settings.loadSettings();

    rtd_client = new RTDClient( settings.rtd_server_prog_id  );
    current    = new ScripState[ settings.no_of_scrips ] ;
    previous   = new ScripState[ settings.no_of_scrips ] ;
                                                                                    
    for( int i=0 ; i<settings.no_of_scrips ; i++ ){                        // Make map key topic_id and value = scripd_id,field_id 
        for( int j=0 ; j<FIELD_COUNT ; j++ ){                              // topic_id generated using FIELD_COUNT as base multiplier for each scrip
            topic_id_to_scrip_field_map[ i*FIELD_COUNT + j  ]  =  std::make_pair( i,j );
        }
    }    

    LARGE_INTEGER start_now = {0};                                         // Start Timers immediately    
    SetWaitableTimer( AB_timer , &start_now, settings.bar_period, NULL, NULL, false );
    
    InitializeCriticalSection( &lock );
    _beginthread( threadEntryDummy, 0, this );                             // Start Amibroker Poller Thread
}


/**
 * Cleanup
 */
Worker::~Worker(){    
    CancelWaitableTimer( AB_timer ) ;
        
    CloseHandle(AB_timer) ;    
    CloseHandle(Event_RTD_Update) ;    
    CloseHandle(Event_StopNow) ;
    CloseHandle(Event_Stopped) ;

    if( csv_file_out.is_open() ){                                          // Close file if not done - just in case
        csv_file_out.close();
    }    

    delete [] current;     current    = 0;
    delete [] previous;    previous   = 0;
    delete rtd_client;     rtd_client = 0;
}

/**
 * Signal Thread to stop and wait for it - Wait Maximum 3 seconds
 **/
void Worker::stop(){    

    if( SetEvent(Event_StopNow)   ){        
        WaitForSingleObject( Event_Stopped, 3*1000 );        
    }    
}

Worker::ScripState::ScripState() : 
    ltp(0), vol_today(0), oi(0), bar_high(0), bar_low(std::numeric_limits<double>::infinity()), bar_open(0)    
{}

void Worker::ScripState::reset(){
    ltp = 0; vol_today = 0; oi =0; bar_high = 0; bar_low = std::numeric_limits<double>::infinity(); bar_open = 0;    
}

bool Worker::ScripState::operator==(const ScripState& right) const{
    return (ltp == right.ltp)  && (vol_today == right.vol_today) &&
           (oi  == right.oi )  && (bar_high  == right.bar_high)  &&
           (ltt == right.ltt)  && (bar_low   == right.bar_low ); 
}



/** 
 * Connect Topics
 */
void Worker::connect(){
    
    rtd_client->startServer();

    for( int i=0 ; i<settings.no_of_scrips ; i++ ){        
        
        std::cout <<  settings.scrips_array[i].ticker  << std::endl ;

        long        topic_id = i * FIELD_COUNT;
        std::string topic_1  = settings.scrips_array[i].topic_name;
                        
        rtd_client->connectTopic(topic_id+LTP,          topic_1, settings.scrips_array[i].topic_LTP       );
        rtd_client->connectTopic(topic_id+LTT,          topic_1, settings.scrips_array[i].topic_LTT       );
        rtd_client->connectTopic(topic_id+VOLUME_TODAY, topic_1, settings.scrips_array[i].topic_vol_today );
        rtd_client->connectTopic(topic_id+OI,           topic_1, settings.scrips_array[i].topic_OI        );
    }     
}

    
/**
 * Wait for RTD Update event. On event, read new data and setup Current Bars
 */
void Worker::poll(){
        
    while(1){    
        if( WaitForSingleObject( Event_RTD_Update, INFINITE ) ==  WAIT_OBJECT_0 ){                    

            std::map<long,CComVariant>*  data = rtd_client->readNewData() ;
            if( data != 0 && !data->empty() ){                             // Extra calls will give empty output most of the time
                processRTDData( data );                
            }            
            delete data;            
        }
    }
}

/**
 * Read TopicId-Value data from COM and update Current Bar
 **/
void Worker::processRTDData( const std::map<long,CComVariant>* data ){
                
    for( auto i=data->begin(), end=data->end() ;  i!=end ; ++i  ){
            
        const long   topic_id     = i->first;
        CComVariant  topic_value  = i->second;
                
        std::pair<int,int> &ids = topic_id_to_scrip_field_map.at( topic_id ) ; 
        int script_id   =  ids.first;                                      // Resolve Topic id to Scrip id and field
        int field_id    =  ids.second;

        EnterCriticalSection( &lock );                                     // Lock when accessing current[] / previous[]

        switch( field_id ){                        
            case LTP :{
                double      ltp      = MiscUtil::getDouble( topic_value );
                ScripState *_current = & current[script_id];

                _current->ltp = ltp;
                if( _current->bar_high < ltp )    _current->bar_high = ltp;
                if( _current->bar_low  > ltp )    _current->bar_low  = ltp;
                if( _current->bar_open == 0  )    _current->bar_open = ltp;                
                break ;    
            }
            case VOLUME_TODAY :{  
                long long vol_today          = MiscUtil::getLong  ( topic_value );
                current[script_id].vol_today = vol_today;

                if( vol_today !=0  &&  previous[script_id].vol_today == 0  ){
                    previous[script_id].vol_today = vol_today;             // On startup prev vol is 0, Set it so that we can get first bar volume
                }
                break ;
            }
            case LTT  :  current[script_id].ltt  = MiscUtil::getString( topic_value ); break ;            
            case OI   :  current[script_id].oi   = MiscUtil::getLong  ( topic_value ); break ;
        }

        LeaveCriticalSection( &lock ) ;
    }    
}


/**
 *    New Thread Entry Point
 **/
void Worker::threadEntryDummy(void* _this){
    ((Worker*)_this)->amibrokerPoller();
}

void Worker::amibrokerPoller(){

    std::vector<ScripBar>  new_bars;
    amibroker = new Amibroker( settings.ab_db_path, settings.csv_path, std::string("rtd.format") );
                                                                           // amibroker constructor has to be called in new thread 
    while(1){    
        // Use events and timers instead of sleep which would be blocking 
        // Need to exit thread cleanly and immediately on application quit - sleep would block

        HANDLE   events[]    = {Event_StopNow,AB_timer};                   // (A) Wait For Timer Event / Application Quit Event
        DWORD    return_code = WaitForMultipleObjects( 2, events , false, INFINITE );                
                                                                            
        if( return_code == WAIT_OBJECT_0 ){                                // Quit Event
            delete amibroker; amibroker = 0;
            SetEvent(Event_Stopped) ;
            std::cout << "AB Feeder Thread Stopped" << std::endl;
            return;
        }
        else if( return_code != WAIT_OBJECT_0 + 1 ){                       // If not Timer Event, then we have some error
            std::stringstream msg;  msg << "WaitForSingleObject Failed - " << return_code;
            throw( msg.str() );                
        }        

    // Shared data access start
        EnterCriticalSection( &lock );

        for( int i=0 ; i<settings.no_of_scrips ; i++  ){                   // (B) Setup Bar data for each updated scrip using current and previous

            ScripState *_current  =  &current[i];
            ScripState *_prev     =  &previous[i];
            long long bar_volume  =  _current->vol_today - _prev->vol_today ;
                                                                           // If data not changed, skip
            if( (_current->bar_open == 0)                   ||             // 1. No New data from readNewData()     
                (bar_volume==0 && _current->vol_today!=0)   ||             // 2. Also skip if bar volume 0 but allow 0 volume scrips like forex
                ((*_current) == (*_prev))                                  // 3. We got new data from readNewData() but its duplicate
              )    continue;                                               //    NEST RTD sends all fields even if unconnected field (ex B/A) changes    
                                    
            if( !_current->ltt.empty() &&  _current->ltt == _prev->ltt  ){ // IF LTT of current is same as previous, but data is different                
                continue;                                                  // skip to avoid overwrite with same timestamp
            }                                                              // This can happen if we have more than 1 update in a second 
                                                                           // and poller took data in between 
            new_bars.push_back( ScripBar() );
            ScripBar* bar = &new_bars.back();
                                                                           // Use ltt if present else use current time                                                                                
            !_current->ltt.empty()  ? bar->ltt    = _current->ltt : bar->ltt    = MiscUtil::getTime( settings.time_format.c_str() );                        
            _prev->vol_today !=0    ? bar->volume = bar_volume    : bar->volume = 0;
                                                                           // Ignore First bar volume as prev bar is not set.
            bar->ticker     = settings.scrips_array[i].ticker;             // Otherwise, we get today's volume = First Bar volume
            bar->bar_open   = _current->bar_open;                                
            bar->bar_high   = _current->bar_high;
            bar->bar_low    = _current->bar_low;
            bar->bar_close  = _current->ltp;            
            bar->oi         = _current->oi;                                            
                
            (*_prev)  =  (*_current) ;                                     // Copy current to previous and reset current
            _current->reset();
        }
        LeaveCriticalSection( &lock );
    // Shared data access end


        if( !new_bars.empty() ){                                           // (C) Write to csv    and Send to Amibroker
            writeCsv( new_bars );
            amibroker->import();                                            
            amibroker->refreshAll();
        }
        new_bars.clear();
    }
}
 

void Worker::writeCsv( const std::vector<ScripBar> & bars ){
    
    csv_file_out.open( settings.csv_path  );                               // Setup output stream to csv file
    if( !csv_file_out.is_open() ){                                         // Reopening will also clear old content by default
        throw( "Error opening file - " + settings.csv_path );        
    }

    size_t          size = bars.size();
    const ScripBar *bar;

    for( size_t i=0 ; i<size ; i++ ){                                      // $FORMAT Ticker, Date_YMD, Time, Open, High, Low, Close, Volume, OpenInt
        bar = &bars[i];
        csv_file_out << bar->ticker     << ',' 
                     << today_date      << ',' 
                     << bar->ltt        << ',' 
                     << bar->bar_open   << ',' 
                     << bar->bar_high   << ',' 
                     << bar->bar_low    << ',' 
                     << bar->bar_close  << ',' 
                     << bar->volume     << ',' 
                     << bar->oi         << std::endl ;
    }

    csv_file_out.close();
}

