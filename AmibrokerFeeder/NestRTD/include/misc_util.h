#ifndef  NESTRTD_MISC_UTIL_H
#define  NESTRTD_MISC_UTIL_H
  
#include <string>
#include <vector>
#include <OAIdl.h>

class MiscUtil{

public:
    static void            printVariant( const VARIANT &var );
    
    static long    long    getLong  ( const VARIANT &var );
    static double          getDouble( const VARIANT &var );
    static std::string     getString( const VARIANT &var );

    static std::string     getINIString( const char * key, const char *app_name="NestRTD" );
    static int             getINIInt   ( const char * key, const char *app_name="NestRTD" );

    static void            splitString( const std::string & string,  char seperator, std::vector<std::string> &output );

    static std::string     getTime( const char *format = "%H:%M:%S"  );    

    static void            trimString          ( std::string & string  );
    static void            replaceTabsWithSpace( std::string & string  );

    static void            createDirectory( std::string & dir  );

    static void            printException( std::string msg );
     
};

 
#endif
