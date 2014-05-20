// main.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "misc_util.h"

#include <iostream>


// TODO
    // Option to filter based on start time and end time + today
    // 1. Nest RTD Server stops updating (in Excel too) Nifty Index after restarting Feeder few times.
    // 2. Nest sometimes starts giving 30 max scrip error - Maybe caused by disconnects?
    // NOW - take topics from settings instead of hardcoding "MktWatch" based on server prog id?
    // Add option to input arg to override any setting	


    // Check for memory leaks in COM calls/callbacks - esp SAFEARRAY/BSTR/VARIANT/COM input/output
        // https://vld.codeplex.com/
        // https://stackoverflow.com/questions/2820223/visual-c-memory-leak-detection
    // Profile - very sleepy



// Workaround for crash on calling CComObject::CreateInstance
// Probably need to create 'ATL' project otherwise
CComModule _Module;
extern __declspec(selectany) CAtlModule* _pAtlModule=&_Module;

Worker  *worker;

// Cleanup before exit
BOOL CtrlHandler( DWORD fdwCtrlType ){

    worker->stop();                                                            // Stop and cleanup Amibroker Feeder thread in worker

    delete worker;  worker = 0;                                                // Delete RTD Client, Worker
    return false;
}


int _tmain(int argc, _TCHAR* argv[]){

    SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE );             // Register callback for program close

    try{
        worker = new Worker;
        worker->connect();
        worker->poll();
    }
    catch( const std::string msg ){
        MiscUtil::printException(msg);
    }
    catch( const char *msg ){
        MiscUtil::printException(msg);
    }

    return 0;
}



