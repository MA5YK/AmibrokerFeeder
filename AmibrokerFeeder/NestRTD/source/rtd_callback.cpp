
#include "rtd_callback.h"
#include <iostream>

HRESULT STDMETHODCALLTYPE CallbackImpl::UpdateNotify(){
	
	std::cout << "UpdateNotify" << std::endl;
	 
	if( Event_RTD_Update )
		SetEvent ( Event_RTD_Update );									// Signal Update
	
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


