#ifndef NESTRTD_RTD_CALLBACK_H
#define NESTRTD_RTD_CALLBACK_H

#include "NestTrader_h.h"

#include <atlbase.h>
#include <atlcom.h>

  
// DECLSPEC_UUID associates a GUID with the class so that you can later reference it using the __uuidof keyword.
// CComObjectRootEx provides the code for implementing the reference counting portion of the IUnknown interface that IDispatch derives from
// CComCoClass provides the code for creating instances of the COM class
// IDispatchImpl provides the implementation of IDispatch

class  DECLSPEC_UUID("d0096450-9dfd-11e3-a5e2-0800200c9a66") CallbackImpl :  
    public CComObjectRootEx<CComMultiThreadModel>,                                                                            
    public CComCoClass<CallbackImpl, &__uuidof(CallbackImpl)>,  
    public IDispatchImpl<IRTDUpdateEvent>{                        
    
public:
    CallbackImpl();

    // Implementation of IUnknown’s QueryInterface method.
    BEGIN_COM_MAP(CallbackImpl)
        COM_INTERFACE_ENTRY(IRTDUpdateEvent)
        COM_INTERFACE_ENTRY(IDispatch)
    END_COM_MAP()

    HRESULT STDMETHODCALLTYPE  UpdateNotify();                    // Callback

    HRESULT STDMETHODCALLTYPE  Disconnect();
    HRESULT STDMETHODCALLTYPE  get_HeartbeatInterval( long *value);
    HRESULT STDMETHODCALLTYPE  put_HeartbeatInterval( long value ); 

private:
    HANDLE    Event_RTD_Update;
};


#endif  
