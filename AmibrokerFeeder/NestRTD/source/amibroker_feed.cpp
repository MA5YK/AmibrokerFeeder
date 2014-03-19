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


#include "amibroker_feed.h"
#include "misc_util.h"

#include <atlbase.h>  
#include <iostream>
#include <sstream>

/**
 * Setup COM objects, Start Amibroker if not open 
 */
Amibroker::Amibroker( const std::string &in_ab_db_path,  const std::string &in_quotes_file_name,  const std::string &in_quotes_format  ) 
: ab_db_path      (in_ab_db_path),
  quotes_file_name(in_quotes_file_name),
  quotes_format   (in_quotes_format)
{    
    
    HRESULT hr = CoInitialize(NULL);                                        // Initialize the COM library for this thread. 

    CLSID   classid;
    hr = CLSIDFromProgID(L"Broker.Application", &classid);        
    hr = CoCreateInstance(classid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (LPVOID*) &amiBrokerDispatch );
                                                                            // Get Dispatch Object for Amibroker Application
    if ( FAILED( hr ) ){
        throw "Cant Connect to Amibroker"  ;        
    } 

    dispid_visible        =    getDispid ( L"Visible" ) ;                   // Load Dispids
    dispid_save_db        =    getDispid ( L"SaveDatabase" ) ;
    dispid_load_db        =    getDispid ( L"LoadDatabase" ) ;
    dispid_import         =    getDispid ( L"Import" ) ;
    dispid_refresh_all    =    getDispid ( L"RefreshAll" ) ;

    setVisible(1);                                                          // Show Amibroker
        
    loadDB();                                                               // Load DB in Amibroker if available
}

 
/**
 * Cleanup
 **/
Amibroker::~Amibroker(){
    
    try{
        saveDB();                                                           // Save AB db before quit
    }
    catch( const std::string msg ){    
        MiscUtil::printException(msg);
    }
    catch( const char *msg ){    
        MiscUtil::printException(msg);
    }

    if(amiBrokerDispatch){
        amiBrokerDispatch->Release();                                       // Release interface object
    }
    CoUninitialize();                                                       // Unload COM library  
}


void Amibroker::setVisible( int is_visible ){ 
    setProperty( dispid_visible , CComVariant(is_visible) );
}
 

/**
 * Import File=quotes_file_name into Amibroker using Amibroker Format=quotes_format
 **/
void Amibroker::import(){    
        
    VARIANT input[3] = {  CComVariant( CComBSTR(quotes_format.c_str())    ),// 0, FileName, DefFileName - DISPPARAMS.rgvarg 
                          CComVariant( CComBSTR(quotes_file_name.c_str()) ),// Inputs in reverse order
                          CComVariant( (int)0 )    
                       };    
    
    DISPPARAMS  args = { input, NULL, 3, 0 }  ;    
    VARIANT     var_output;

    dispatch( dispid_import, DISPATCH_METHOD, args , var_output );                                                                  
}



 
void Amibroker::refreshAll(){
    VARIANT var_output;
    dispatch( dispid_refresh_all, DISPATCH_METHOD, var_output );
}
 
void Amibroker::loadDB(){

    if( ab_db_path.empty() ){
        return;
    }

    VARIANT input = CComVariant(  CComBSTR( ab_db_path.c_str() )  );

    DISPPARAMS args;
    args.rgvarg            = &input;
    args.cArgs             = 1;
    args.rgdispidNamedArgs = 0;
    args.cNamedArgs        = 0;
    
    VARIANT    var_output;
    dispatch( dispid_load_db, DISPATCH_METHOD, args, var_output );

    Sleep(100);                                                             // Sleep a little time - Sometimes get error in BackFill if DB set
                                                                            // Maybe due to fast load-import-save - check
}

void Amibroker::saveDB(){
    VARIANT  var_output;
    dispatch( dispid_save_db, DISPATCH_METHOD, var_output );
}

 


DISPID Amibroker::getDispid ( WCHAR * name ){
    DISPID  dispid;
    HRESULT hr = amiBrokerDispatch->GetIDsOfNames ( IID_NULL, &name, 1, GetUserDefaultLCID(), &dispid );
    return  dispid;
}


void Amibroker::setProperty( DISPID dispid, VARIANT &input ){
    
    DISPPARAMS  args;
    args.rgvarg            = &input;
    args.cArgs             = 1;        
    
    DISPID pos             = DISPID_PROPERTYPUT;                            // Property Setter needs this in named args or fails
    args.rgdispidNamedArgs = &pos;
    args.cNamedArgs        = 1;    
            
    VARIANT  var_output;

    dispatch( dispid, DISPATCH_PROPERTYPUT, args , var_output );
}


// No argument
void Amibroker::dispatch( DISPID dispid, WORD wFlag, VARIANT  &result ){
    
    DISPPARAMS args = { 0, 0, 0, 0 };
    dispatch( dispid, wFlag, args, result );
}

/**
 *  wFlag - DISPATCH_METHOD / DISPATCH_PROPERTYGET / DISPATCH_PROPERTYPUT
 *  Alternative - Look at COleDispatchDriver - afxdisp.h
 **/
void Amibroker::dispatch( DISPID dispid, WORD wFlag, DISPPARAMS &args, VARIANT  &result ){

    EXCEPINFO except_info;
    UINT      arg_error;
    
    HRESULT hr = amiBrokerDispatch->Invoke ( dispid, IID_NULL, GetUserDefaultLCID(), wFlag, &args, &result, &except_info, &arg_error );
    
    if( FAILED (hr)  ){
        std::stringstream msg; msg << "Dispatch Failed - " << dispid ;
        throw msg.str() ;
    }        
}


