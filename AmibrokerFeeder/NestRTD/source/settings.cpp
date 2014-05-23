
#include "settings.h"
#include "misc_util.h"

void Settings::loadSettings(){
    
    rtd_server_prog_id    = MiscUtil::getINIString("RTDServerProgID");     
    bar_period            = MiscUtil::getINIInt   ("BarPeriod");
    csv_path              = MiscUtil::getINIString("CSVFolderPath"); 
    time_format           = MiscUtil::getINIString("TimeFormat"); 
    ab_db_path            = MiscUtil::getINIString("AbDbPath");     
    no_of_scrips          = 0 ;    

    std::string scrip_value;
    std::string scrip_key;

    if( bar_period < 1000  ){                                                // check $TICKMODE 1
        throw "Minimum Bar Interval is 1000ms";        
    }
        
    MiscUtil::createDirectory( csv_path );                                   // If folder does not exist, create it.
    csv_path.append("quotes.rtd");
    
    while(1){
        scrip_key    = "Scrip";  scrip_key.append( std::to_string( (long long)no_of_scrips+1 ) );
        scrip_value  = MiscUtil::getINIString( scrip_key.c_str() ) ;

        if(scrip_value.empty()){                                             // No more Scrips left
            if( no_of_scrips == 0 ){
                throw( "Atleast one scrip needed" );
            }
            else break;
        }

        //  ScripID(mandatory);Alias(mandatory);LTP(mandatory);LTT;Todays Volume;OI  
        std::vector<std::string>  split_strings;
        MiscUtil::splitString( scrip_value , ';', split_strings ) ;
        if(split_strings.size() < 3 ){                                       // 3 mandatory field at start
            throw( scrip_key + " Invalid" ); 
        }

        Scrip    scrip_topics;

        scrip_topics.topic_name   =  split_strings[0];     
        scrip_topics.ticker       =  split_strings[1];
        scrip_topics.topic_LTP    =  split_strings[2];

        if(split_strings.size() >=4 ){
            scrip_topics.topic_LTT       =  split_strings[3];
        }
        if(split_strings.size() >=5 ){
            scrip_topics.topic_vol_today =  split_strings[4];
        }
        if(split_strings.size() >=6 ){
            scrip_topics.topic_OI        =  split_strings[5];
        } 

        scrips_array.push_back(  scrip_topics ) ;
        no_of_scrips++;
    } 
}


