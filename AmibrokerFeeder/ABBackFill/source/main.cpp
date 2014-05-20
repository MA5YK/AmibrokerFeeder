  
#include "stdafx.h"

#include "settings.h"
#include "reader.h"
#include "amibroker_feed.h"
#include "misc_util.h"
#include <iostream>
 
// TODO
    // EOD Convert bars to 1 min
        // Read bars and construct 1 min bars 
        // OR - Use $TICKMODE 1 for EOD VWAP/DT IMPORT - this will delete todays tick data, replacing it with 1 min bars takn from NEST
            // take input arg to toggle this and create shortcut
    
    // Backfill only missing data - use a threshold. If no of quotes in a minute less than threshold, delete quotes and import from input data
    // Delete overlapping bars of same time in AB 
        // use AB stock-quotations - example of delete in DeleteDateRange.js
        // Delete slow in scripts - check c++ speed - 11000*3 COM calls - 75 seconds - is COM bottleneck?
            // http://msdn.microsoft.com/en-us/library/windows/apps/hh994636.aspx            
            // Worst case - just take start and end time as input - this should speed up read-delete
    
    // AHK/autoit com interface
		// Look at Sikuli - cross platform
        // Possible standalone techniques
            // https://stackoverflow.com/questions/5414313/c-c-hook-to-access-the-windows-elements-of-a-program
            // http://social.msdn.microsoft.com/Forums/vstudio/en-US/f06b9918-3e27-46f7-bf19-7cd2af4c943b/will-c-allow-me-to-manipulate-windows?forum=vcgeneral
			
    // Ignore if price 0 / out of market time ? - Nifty Index
          

int _tmain(int argc, _TCHAR* argv[]){

    try{
        //LARGE_INTEGER start, finish, freq;
        //QueryPerformanceFrequency(&freq);
        //QueryPerformanceCounter(&start);
        
        // Read settings.ini
        Settings settings;
        settings.loadSettings();        

        // Read Input and convert to CSV
        Reader reader;     
        bool vwap = reader.parseVWAPToCsv     ( settings.vwap_file_path,        settings.csv_file_path ) ;
        bool dt   = reader.parseDataTableToCsv( settings.data_table_file_path,  settings.csv_file_path ) ;
        reader.closeOutput();

        if( !vwap && !dt ){
            throw "Both VWAP and DT Input missing. VWAP:" + settings.vwap_file_path + "DT:" + settings.data_table_file_path ;
        }

        //QueryPerformanceCounter(&finish);
        //std::cout << "CSV Creation Time:" << ((finish.QuadPart - start.QuadPart) / (double)freq.QuadPart) << std::endl;

        // send CSV to AB
        Amibroker AB( settings.ab_db_path, settings.csv_file_path, "backfill.format"); 
        AB.import();        
        AB.refreshAll();
        AB.saveDB();       

        std::cout << "Done" << std::endl ;
    }    
    catch( const std::string msg ){    
        MiscUtil::printException( msg );
    }
    catch( const char *msg ){    
        MiscUtil::printException( msg );
    }

    return 0;
}

