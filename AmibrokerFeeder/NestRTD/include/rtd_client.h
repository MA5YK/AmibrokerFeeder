#ifndef NESTRTD_RTDCLIENT_H
#define NESTRTD_RTDCLIENT_H

#include "NestTrader_h.h"
#include "rtd_callback.h"

#include <string>
#include <map> 
#include <set> 

class RTDClient {

public: 
    RTDClient( const std::string &server_prog_id );
    ~RTDClient();

    void    startServer();
    void    stopServer();

    void    connectTopic   ( long topic_id, const std::string &topic_1, const std::string &topic_2 );
    void    disconnectTopic( long topic_id );

    std::map<long,CComVariant>*  readNewData();           // Returns Map of Topic id and Topic Value

private: 
    IScripRTD                    *comObjectScripRTD;      // NEST RTD COM object - Nest.ScripRTD for Interface IScripRTD
    CComObject<CallbackImpl>     *callback;               // Callback Object - Implementation of IRTDUpdateEvent
    std::set<long>                connected_topics;

    bool                          is_NOW;                 // Pass MktWatch as Topic 1 for NOW

    RTDClient( const RTDClient& );                        // Disable copy
    RTDClient operator=(const RTDClient& );     
};

#endif
