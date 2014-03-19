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


#include "reader.h"
#include "misc_util.h"

#include <iostream>
#include <sstream>

Reader::Reader(){}

Reader::~Reader(){
    if( fin.is_open() ){
        fin.close();
    }
    if( fout.is_open() ){
        fout.close();
    }                                                        
}
 

void Reader::parseVWAPToCsv(  const std::string &vwap_file, const std::string &csv_file_path  ){
        
    setUpInputStream( vwap_file);
    if( !fout.is_open() ){                                                     // Dont reset - use single csv import
        setUpOutputStream( csv_file_path );
    }

    std::string               today_date = MiscUtil::getTime("%Y%m%d");        // Get todays date - yyyymmdd
    std::string               line;
    std::string               scrip_name;
    std::vector<std::string>  split;

    while( std::getline( fin, line  ) ){
                
        MiscUtil::trimString( line );                                          // Remove leading and trailing spaces
        MiscUtil::replaceTabsWithSpace(line);                                  // Replace Tabs with space

        if( line.empty() ) continue;                                           // Ignore Empty lines
                
        MiscUtil::splitString( line , '=', split ) ;                           // Check for Scrip Name
        if( split.size() == 2 && split[0] == "name" ){
            scrip_name = split[1];
            continue;
        }

        if( scrip_name.empty() ){
            throw "Scrip Name not Found";
        }        
        
        MiscUtil::splitString( line , ' ', split ) ;                           // Data. Expected format is 
                                                                               // "09:15:00 AM 6447.00 6465.00 6439.55 6444.40 318900"    
        if( split.size() != 7  ){                                              // Time AM/PM O H L C V            
            std::stringstream msg;  
            msg << "Could Not Parse Line - " << split.size() << " - " << line;
            throw msg.str();
        }
        
        std::string time  = split[0];
        std::string am_pm = split[1];        
        
        if( am_pm == "PM" || am_pm == "pm" ){                                    
            changeHHFrom12To24( time );    
        }
        
        // $FORMAT Ticker, Date_YMD, Time, Open, High, Low, Close, Volume
        fout << scrip_name << ',' << today_date << ',' << time << ',' << split[2] << ',' << split[3] << ',' << split[4] << ',' 
             << split[5]   << ',' << split[6]   << std::endl ;
    }    
}


// "NIFTY14MARFUT    17-02-2014 09:20:00    6078.7000    6081.2000    6078.5000    6080.9500    53350"
void Reader::parseDataTableToCsv( const std::string &dt_file, const std::string &csv_file_path  ){
        
    setUpInputStream( dt_file);
    if( !fout.is_open() ){                                                     // Dont reset - use single csv import
        setUpOutputStream( csv_file_path );
    }
        
    std::string               line;
    std::string               custom_name;
    std::vector<std::string>  split;
    std::vector<std::string>  date_split;

    while( std::getline( fin, line  ) ){
                
        MiscUtil::trimString( line );                                          // Remove leading and trailing spaces
        MiscUtil::replaceTabsWithSpace(line);                                  // Replace Tabs with space

        if( line.empty() ) continue;                                           // Ignore Empty lines
                
        MiscUtil::splitString( line , '=', split ) ;                           // Check for Scrip Name
        if( split.size() > 0 && split[0] == "name" ){
            if( split.size() == 2 ){
                custom_name = split[1];
            }
            else custom_name = "" ; 
            continue;
        }        
        
        MiscUtil::splitString( line , ' ', split ) ;                           // Data. Expected format is 
                                                                               // Name dd-mm-yyyy Time O H L C V
        if( split.size() != 8  ){
            std::stringstream msg;  
            msg << "Could Not Parse Line - " << split.size() << " - " << line;
            throw msg.str();
        }
        
        std::string name;  
        custom_name.empty() ?  name = split[0] : name = custom_name ;

        std::string date = split[1];
        MiscUtil::splitString( date , '-', date_split ) ;
        
        // $FORMAT Ticker, Date_YMD, Time, Open, High, Low, Close, Volume
        fout << name     << ',' << date_split[2]   << date_split[1] << date_split[0] << ','
             << split[2] << ',' << split[3]        << ','           << split[4]      << ',' 
             << split[5] << ',' << split[6]        << ','           << split[7]      << std::endl ;
    }    
}

void Reader::closeOutput(){
    if( fout.is_open() ){
        fout.close();
    }
}

void Reader::setUpInputStream(  const std::string &in_file  ){
    if( fin.is_open() ){
        fin.close();    
    }
    fin.open ( in_file );
    if( !fin.is_open() ){
        throw "Could not Read Backfill File - " + in_file;
    }
}


void Reader::setUpOutputStream( const std::string &out_file   ){  
    if( fout.is_open() ){
        fout.close();
    }
    fout.open( out_file );
    if( !fout.is_open() ){
        throw "Error opening CSV file - " + out_file;        
    }
}

 
 
void Reader::changeHHFrom12To24( std::string &time ){                          // Increase hh by 12 (except 12 PM)
    
    std::vector<std::string>  split_strings;

    MiscUtil::splitString( time , ':', split_strings ) ;
    long long hh = std::stoll( split_strings[0] );

    if( hh < 12 ){
        hh += 12;
                
        std::stringstream concat;
        concat << hh << ':' << split_strings[1] << ':' << split_strings[2] ;
        time =  concat.str();
    } 
} 





