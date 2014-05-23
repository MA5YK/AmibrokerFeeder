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


#include "rtd_client.h"
#include "misc_util.h"

#include <atlbase.h>
#include <atlsafe.h> 

#include <cstdlib>
#include <iostream>


/**
 * Setup Com objects
 * Use comObjectScripRTD->QueryInterface( IID , LPVOID*  ) to get another interface of same classid    if needed
**/
RTDClient::RTDClient( const std::string &server_prog_id ) : is_NOW(false) {
    
    is_NOW  =  MiscUtil::isStringEqualIC( server_prog_id, "NOW.ScripRTD" ) ;

    USES_CONVERSION;
    LPOLESTR   progid  =  A2OLE( server_prog_id.c_str() );
    CLSID      classid;    
    HRESULT    hr;
    
    hr = CoInitializeEx(NULL,COINIT_MULTITHREADED);                         // Initialize the COM library for this thread. This make Windows load the DLLs
                                                                            // COINIT_MULTITHREADED needed for callback to work.
    hr = CLSIDFromProgID(progid, &classid);                                 // Else need a message loop for STA - Single Thread Apartment
    hr = CoCreateInstance(classid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IScripRTD), (LPVOID*) &comObjectScripRTD );
                                                                            // Get COM Object for IScripRTD interface
    if ( FAILED( hr ) ){        
        throw( server_prog_id + " - IScripRTD object creation error. Nest down?"  );
    }
    
    CComObject<CallbackImpl>::CreateInstance(&callback);                    // Create Callback Object
}

/**
 * Cleanup
 */
RTDClient::~RTDClient(){
    try{
        for( auto i=connected_topics.begin(), j=connected_topics.end() ; i!=j ; i=connected_topics.begin() ){ 
            disconnectTopic( *i );                                          // disconnect all connected topics            
        }
        stopServer();
    }
    catch( const std::string msg ){    
        MiscUtil::printException(msg);
    }
    catch( const char *msg ){    
        MiscUtil::printException(msg);
    }
    
    if(comObjectScripRTD){
        comObjectScripRTD->Release();                                       // Release interface object
    }
    
    CoUninitialize();                                                       // Unload COM library  

    std::cout << "RTDClient Stopped" << std::endl ; 
}


void RTDClient::startServer(){
    
    long    server_status = -1;        
    HRESULT hr            = comObjectScripRTD->ServerStart( callback , &server_status );
        
    std::cout << "Server status : " << server_status << std::endl;    

    if( server_status <=0 ){                                                // Returns 0 if callback null, +ve if SUCCESS
        throw "Server start error.";        
    }
}

void RTDClient::stopServer(){        
    HRESULT hr = comObjectScripRTD->ServerTerminate();   

    if( FAILED(hr) ){
        std::cout << "stopServer Failed - " << " - hr - " << hr << std::endl;
    }
}

/**
 * Connect to input Scrip and Field, registering it with input topic number
 */
void RTDClient::connectTopic(  long topic_id, const std::string &topic_1, const std::string &topic_2  ){
    
    if( topic_2.empty()  ){                                                 // Ignore Empty Fields
        return;
    }

    int topics_count;  is_NOW ? topics_count=3 : topics_count=2;            // TODO Workaround - Pass MktWatch as Topic 1 for NOW
    CComSafeArray<VARIANT> topics(topics_count);

    if( is_NOW ){
        topics[0] = CComBSTR( "MktWatch" );
        topics[1] = CComBSTR(topic_1.c_str());
        topics[2] = CComBSTR(topic_2.c_str());
    }
    else{
        topics[0] = CComBSTR(topic_1.c_str());
        topics[1] = CComBSTR(topic_2.c_str());
    }
    
    VARIANT_BOOL getNewValues = VARIANT_TRUE;
    CComVariant  output;

    HRESULT hr = comObjectScripRTD->ConnectData(topic_id, topics.GetSafeArrayPtr(), &getNewValues, &output);
        
    if( FAILED(hr) ){
        std::cout << "Topic Connection Failed - " << topic_1 << " | " << topic_2 << " - hr - " << hr << " - " << is_NOW << std::endl;
    }
    else{
        std::cout << "Topic Connected - " << topic_id << " - " << topic_1 << " | " << topic_2 << std::endl;    
        connected_topics.insert( topic_id );
    }
}

void RTDClient::disconnectTopic( long topic_id) {  
    // TODO check - dont disconnect to avoid 30 scrip error
    /**
    HRESULT hr = comObjectScripRTD->DisconnectData(topic_id);   
    if( FAILED(hr) ){
        std::cout << "Topic Disconnection Failed - " << topic_id << " - hr - " << hr << std::endl;
    }**/
    connected_topics.erase( topic_id );  
}


/**
 * Output = Map of topic id and field data  -  Map to be deleted by caller
 */
std::map<long,CComVariant>* RTDClient::readNewData(){    
    
    SAFEARRAY  *data_sa;
    long        topic_count = 0;
    HRESULT     hr          = comObjectScripRTD->RefreshData( &topic_count, &data_sa );      
                                                                 // Pass Address of SAFEARRAY pointer so that we get pointer to 2D safearray
    if( FAILED(hr) ){                                            // Output Data has to be deleted by client
        std::cout << "RefreshData COM failure." << " - hr - " << hr <<   std::endl;    
        return 0;
    }
    CComSafeArray<VARIANT>  data;                                // Passing data_sa as Constructor input will copy it, but we need to destroy it after use
    data.Attach( data_sa );                                      // So attach instead and let CComSafeArray handle it
    

    ULONG  row_count = data.GetCount(1);                         // No of Rows = 2nd Dimension Count
    if( row_count == 0) return 0 ;
        
    std::map<long,CComVariant> *output = new std::map<long,CComVariant>;    // Map: Topicid, Field Data
         
    long index[2];
    for( ULONG i=0 ; i<row_count; i++  ){
        
        index[0] = 0;                                            // 0,x - Topic ids.   1,x - Data
        index[1] = i;
        CComVariant topic_id_var;
        data.MultiDimGetAt( index, topic_id_var);         
        long topic_id = (long)MiscUtil::getLong( topic_id_var );
        
        index[0] = 1;
        index[1] = i;
        CComVariant topic_data_var;
        data.MultiDimGetAt( index, topic_data_var); 
                
        
        if( output->count(topic_id) != 0  && (*output)[topic_id] != topic_data_var  ){            
            std::cout << "Duplicate:";  MiscUtil::printVariant((*output)[topic_id]); std::cout << "-";  MiscUtil::printVariant(topic_data_var);
            std::cout << std::endl;
            //abort();                                           // If exists - we can have multiple topic values in same call => use vector
        }
        
        (*output)[topic_id] = topic_data_var;   
    } 

    return output;
}

