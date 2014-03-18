
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
RTDClient::RTDClient( const std::string &server_prog_id ){
        
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
}

/**
 * Connect to input Scrip and Field, registering it with input topic number
 */
void RTDClient::connectTopic(  long topic_id, const std::string &topic_1, const std::string &topic_2  ){
    
    if( topic_2.empty()  ){                                                 // Ignore Empty Fields
        return;
    }

    CComSafeArray<VARIANT> topics(2);    
    topics[0] = CComBSTR(topic_1.c_str());
    topics[1] = CComBSTR(topic_2.c_str());
    
    VARIANT_BOOL getNewValues = VARIANT_TRUE;
    CComVariant  output;

    HRESULT hr = comObjectScripRTD->ConnectData(topic_id, topics.GetSafeArrayPtr(), &getNewValues, &output);
        
    if( FAILED(hr) ){
        std::cout << "Topic Connection Failed - " << topic_1 << " | " << topic_2 << std::endl;    
    }
    else{
        std::cout << "Topic Connected - " << topic_id << " - " << topic_1 << " | " << topic_2 << std::endl;    
        connected_topics.insert( topic_id );
    }
}

void RTDClient::disconnectTopic( long topic_id) {               // TODO
    HRESULT hr = comObjectScripRTD->DisconnectData(topic_id);   // 1. Nest RTD Server starts giving max 30 subscription errors on multiple disconnects 
    connected_topics.erase( topic_id );                             // maybe server buggy - dont disconnect ?
}                                                               // 2. - Nifty Index rtd updates stop sometimes on Feeder restart
                                                                    // check if caused by not disconnecting

/**
 * Output = Map of topic id and field data  -  Map to be deleted by caller
 */
std::map<long,CComVariant>* RTDClient::readNewData(){    
    
    SAFEARRAY  *data_sa;
    long        topic_count = 0;
    HRESULT     hr          = comObjectScripRTD->RefreshData( &topic_count, &data_sa );      
                                                                 // Pass Address of SAFEARRAY pointer so that we get pointer to 2D safearray
    if( FAILED(hr) ){                                            // Output Data has to be deleted by client
        std::cout << "RefreshData COM failure." << std::endl;    
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

