#include "misc_util.h"

#include <windows.h> 
#include <atlconv.h>

#include <iostream> 
#include <sstream>  
#include <fstream>
#include <algorithm>
#include <ctime>


 void MiscUtil::printVariant( const VARIANT &var ){
    if( var.vt == VT_I4  ){                    // Long        
        std::cout << var.lVal; 
    }
    else if( var.vt == VT_R8 ){                // Double        
        std::cout << var.dblVal ; 
    }
    else if( var.vt == VT_BSTR ){              // BSTR
        std::wcout << var.bstrVal ; 
    }    
} 
  
// 'Index Value' Field is sent by NEST as BSTR instead of double - so just make generic getters and handle all types
long long MiscUtil::getLong( const VARIANT &var ){
    long long output = 0; 

    if( var.vt == VT_I4  ){                    // Long
        output = var.lVal; 
    }
    else if( var.vt == VT_R8 ){                // Double
        output = (long long) var.dblVal ; 
    }
    else if( var.vt == VT_BSTR ){              // BSTR
        output = std::stoll( getString(var) );
    }    
    return  output;
}

double MiscUtil::getDouble( const VARIANT &var ){
    double output = 0; 

    if( var.vt == VT_I4  ){                    // Long        
        output = (double)var.lVal; 
    }
    else if( var.vt == VT_R8 ){                // Double        
        output = var.dblVal ; 
    }
    else if( var.vt == VT_BSTR ){              // BSTR
        output = std::stod( getString(var)  );
    }    
    return  output;
}

std::string MiscUtil::getString( const VARIANT &var ){
    std::string output;

    if( var.vt == VT_I4  ){                    // Long        
        output = std::to_string((long long)var.lVal);            // VC++ 2010 - Initial C++11
    }                                                                // std::to_string - long long but not long
    else if( var.vt == VT_R8 ){                // Double        
        output = std::to_string((long double)var.dblVal) ; 
    }
    else if( var.vt == VT_BSTR){
        USES_CONVERSION;
        output = std::string ( OLE2A(var.bstrVal)) ;            // OLE2A dangerous - always copy output
    }    
    return output;
} 


std::string MiscUtil::getINIString( const char * key, const char *app_name){
        
    char buffer[512];
    GetPrivateProfileStringA( app_name, key, "", buffer, 512,".\\settings.ini");

    return std::string(buffer);
}

int MiscUtil::getINIInt( const char * key, const char *app_name ){
            
    return GetPrivateProfileIntA( app_name, key, 0  , ".\\settings.ini");        
}


void MiscUtil::splitString( const std::string & string , char seperator,  std::vector<std::string> &output ){
    
    if( ! output.empty() ){
        output.clear();
    }

    std::stringstream  string_stream(string);
    std::string        segment;    

    while(std::getline(string_stream, segment, seperator)) {    // get line using ';' as end of line character
        output.push_back(segment);
    }    
}


std::string  MiscUtil::getTime( const char *format ){
        
    std::time_t  raw = std::time(0);    
    std::tm      local;
    localtime_s( &local, &raw );
    
    char buffer[16];
    strftime(buffer,16, format, &local );

    return std::string( buffer );
} 


void MiscUtil::trimString( std::string  &string  ){

    size_t begin = string.find_first_not_of(" \t\r\n");
    if (begin == std::string::npos){                            // Empty Line
        string = ""; 
        return;
    }

    size_t end    = string.find_last_not_of(" \t\r\n");    
    size_t length = end - begin + 1;

    string = string.substr(begin, length);
}

void MiscUtil::replaceTabsWithSpace( std::string & string  ){
    
    size_t size = string.size();
    
    for( size_t i=0 ; i<size ; i++ ){
        if( string[i] == '\t')
            string.replace(i, 1, " ");    
    }
}

// If folder does not exist, create it. Abort if failed
void MiscUtil::createDirectory( std::string & dir  ){
        
    if( !CreateDirectoryA( dir.c_str(), NULL)  &&  ERROR_ALREADY_EXISTS != GetLastError()  ){
        DWORD                error = GetLastError();
        std::stringstream    msg;  msg << "Could not create folder - " << dir << " Error-" << error << std::endl ;
        throw  msg.str();
    }
}


void MiscUtil::printException( std::string msg ){
    
    std::cout << msg << std::endl;

    std::ofstream log_out( "./errorLog.txt" );
    if( log_out .is_open()){
        log_out << msg << std::endl;
        log_out.close();
    }    
}

// Compare strings ignoring case
bool MiscUtil::isStringEqualIC(std::string str1 , std::string str2 ){
    std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

    return str1 == str2 ;
}

