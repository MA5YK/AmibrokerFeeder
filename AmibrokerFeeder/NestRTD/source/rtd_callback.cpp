
#include "rtd_callback.h"
 
CallbackImpl::CallbackImpl(){
    
    Event_RTD_Update = OpenEvent( EVENT_MODIFY_STATE , false, _T("RTD_UPDATE") );
                
    if( Event_RTD_Update == NULL ){
        throw "RTD_UPDATE Open error - " + GetLastError() ;
    }    
}

HRESULT STDMETHODCALLTYPE CallbackImpl::UpdateNotify(){     

    if( Event_RTD_Update )        
        SetEvent ( Event_RTD_Update );                                    // Signal Update
    
    return S_OK;
}

HRESULT STDMETHODCALLTYPE  CallbackImpl::Disconnect(){
    return S_OK;
}
HRESULT STDMETHODCALLTYPE  CallbackImpl::get_HeartbeatInterval( long *value){
    *value=-1;
    return S_OK;
}
HRESULT STDMETHODCALLTYPE  CallbackImpl::put_HeartbeatInterval( long value ){
    return S_OK;
}


