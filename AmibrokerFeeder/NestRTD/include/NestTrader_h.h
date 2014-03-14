

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Mar 14 16:36:41 2014
 */
/* Compiler settings for include\NestTrader.IDL:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __NestTrader_h_h__
#define __NestTrader_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IScripRTD_FWD_DEFINED__
#define __IScripRTD_FWD_DEFINED__
typedef interface IScripRTD IScripRTD;
#endif 	/* __IScripRTD_FWD_DEFINED__ */


#ifndef __IRTDUpdateEvent_FWD_DEFINED__
#define __IRTDUpdateEvent_FWD_DEFINED__
typedef interface IRTDUpdateEvent IRTDUpdateEvent;
#endif 	/* __IRTDUpdateEvent_FWD_DEFINED__ */


#ifndef ___INestBridgeEvents_FWD_DEFINED__
#define ___INestBridgeEvents_FWD_DEFINED__
typedef interface _INestBridgeEvents _INestBridgeEvents;
#endif 	/* ___INestBridgeEvents_FWD_DEFINED__ */


#ifndef __INestBridge_FWD_DEFINED__
#define __INestBridge_FWD_DEFINED__
typedef interface INestBridge INestBridge;
#endif 	/* __INestBridge_FWD_DEFINED__ */


#ifndef __IPlusapi_FWD_DEFINED__
#define __IPlusapi_FWD_DEFINED__
typedef interface IPlusapi IPlusapi;
#endif 	/* __IPlusapi_FWD_DEFINED__ */


#ifndef __ScripRTD_FWD_DEFINED__
#define __ScripRTD_FWD_DEFINED__

#ifdef __cplusplus
typedef class ScripRTD ScripRTD;
#else
typedef struct ScripRTD ScripRTD;
#endif /* __cplusplus */

#endif 	/* __ScripRTD_FWD_DEFINED__ */


#ifndef __NestBridge_FWD_DEFINED__
#define __NestBridge_FWD_DEFINED__

#ifdef __cplusplus
typedef class NestBridge NestBridge;
#else
typedef struct NestBridge NestBridge;
#endif /* __cplusplus */

#endif 	/* __NestBridge_FWD_DEFINED__ */


#ifndef __Plusapi_FWD_DEFINED__
#define __Plusapi_FWD_DEFINED__

#ifdef __cplusplus
typedef class Plusapi Plusapi;
#else
typedef struct Plusapi Plusapi;
#endif /* __cplusplus */

#endif 	/* __Plusapi_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __NESTClientLib_LIBRARY_DEFINED__
#define __NESTClientLib_LIBRARY_DEFINED__

/* library NESTClientLib */
/* [helpstring][version][uuid] */ 







EXTERN_C const IID LIBID_NESTClientLib;

#ifndef __IScripRTD_INTERFACE_DEFINED__
#define __IScripRTD_INTERFACE_DEFINED__

/* interface IScripRTD */
/* [object][oleautomation][nonextensible][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_IScripRTD;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC0E6191-DB51-11D3-8F3E-00C04F3651B8")
    IScripRTD : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ServerStart( 
            /* [in] */ IRTDUpdateEvent *callback,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ConnectData( 
            /* [in] */ long topicId,
            /* [in] */ SAFEARRAY * *strings,
            /* [out][in] */ VARIANT_BOOL *newValues,
            /* [retval][out] */ VARIANT *values) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RefreshData( 
            /* [out][in] */ long *topicCount,
            /* [retval][out] */ SAFEARRAY * *data) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DisconnectData( 
            /* [in] */ long topicId) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Heartbeat( 
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ServerTerminate( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IScripRTDVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScripRTD * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScripRTD * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScripRTD * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IScripRTD * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IScripRTD * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IScripRTD * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IScripRTD * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ServerStart )( 
            IScripRTD * This,
            /* [in] */ IRTDUpdateEvent *callback,
            /* [retval][out] */ long *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ConnectData )( 
            IScripRTD * This,
            /* [in] */ long topicId,
            /* [in] */ SAFEARRAY * *strings,
            /* [out][in] */ VARIANT_BOOL *newValues,
            /* [retval][out] */ VARIANT *values);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RefreshData )( 
            IScripRTD * This,
            /* [out][in] */ long *topicCount,
            /* [retval][out] */ SAFEARRAY * *data);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DisconnectData )( 
            IScripRTD * This,
            /* [in] */ long topicId);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Heartbeat )( 
            IScripRTD * This,
            /* [retval][out] */ long *result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ServerTerminate )( 
            IScripRTD * This);
        
        END_INTERFACE
    } IScripRTDVtbl;

    interface IScripRTD
    {
        CONST_VTBL struct IScripRTDVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScripRTD_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IScripRTD_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IScripRTD_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IScripRTD_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IScripRTD_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IScripRTD_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IScripRTD_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IScripRTD_ServerStart(This,callback,result)	\
    ( (This)->lpVtbl -> ServerStart(This,callback,result) ) 

#define IScripRTD_ConnectData(This,topicId,strings,newValues,values)	\
    ( (This)->lpVtbl -> ConnectData(This,topicId,strings,newValues,values) ) 

#define IScripRTD_RefreshData(This,topicCount,data)	\
    ( (This)->lpVtbl -> RefreshData(This,topicCount,data) ) 

#define IScripRTD_DisconnectData(This,topicId)	\
    ( (This)->lpVtbl -> DisconnectData(This,topicId) ) 

#define IScripRTD_Heartbeat(This,result)	\
    ( (This)->lpVtbl -> Heartbeat(This,result) ) 

#define IScripRTD_ServerTerminate(This)	\
    ( (This)->lpVtbl -> ServerTerminate(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IScripRTD_INTERFACE_DEFINED__ */


#ifndef __IRTDUpdateEvent_INTERFACE_DEFINED__
#define __IRTDUpdateEvent_INTERFACE_DEFINED__

/* interface IRTDUpdateEvent */
/* [object][oleautomation][dual][uuid] */ 


EXTERN_C const IID IID_IRTDUpdateEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A43788C1-D91B-11D3-8F39-00C04F3651B8")
    IRTDUpdateEvent : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UpdateNotify( void) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_HeartbeatInterval( 
            /* [retval][out] */ long *value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_HeartbeatInterval( 
            /* [in] */ long value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTDUpdateEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRTDUpdateEvent * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRTDUpdateEvent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRTDUpdateEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRTDUpdateEvent * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRTDUpdateEvent * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRTDUpdateEvent * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRTDUpdateEvent * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UpdateNotify )( 
            IRTDUpdateEvent * This);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_HeartbeatInterval )( 
            IRTDUpdateEvent * This,
            /* [retval][out] */ long *value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_HeartbeatInterval )( 
            IRTDUpdateEvent * This,
            /* [in] */ long value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IRTDUpdateEvent * This);
        
        END_INTERFACE
    } IRTDUpdateEventVtbl;

    interface IRTDUpdateEvent
    {
        CONST_VTBL struct IRTDUpdateEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTDUpdateEvent_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRTDUpdateEvent_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRTDUpdateEvent_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRTDUpdateEvent_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRTDUpdateEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRTDUpdateEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRTDUpdateEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRTDUpdateEvent_UpdateNotify(This)	\
    ( (This)->lpVtbl -> UpdateNotify(This) ) 

#define IRTDUpdateEvent_get_HeartbeatInterval(This,value)	\
    ( (This)->lpVtbl -> get_HeartbeatInterval(This,value) ) 

#define IRTDUpdateEvent_put_HeartbeatInterval(This,value)	\
    ( (This)->lpVtbl -> put_HeartbeatInterval(This,value) ) 

#define IRTDUpdateEvent_Disconnect(This)	\
    ( (This)->lpVtbl -> Disconnect(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRTDUpdateEvent_INTERFACE_DEFINED__ */


#ifndef ___INestBridgeEvents_DISPINTERFACE_DEFINED__
#define ___INestBridgeEvents_DISPINTERFACE_DEFINED__

/* dispinterface _INestBridgeEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__INestBridgeEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5BFBF197-6FC4-4970-ACC7-494F252B390F")
    _INestBridgeEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _INestBridgeEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _INestBridgeEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _INestBridgeEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _INestBridgeEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _INestBridgeEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _INestBridgeEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _INestBridgeEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _INestBridgeEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _INestBridgeEventsVtbl;

    interface _INestBridgeEvents
    {
        CONST_VTBL struct _INestBridgeEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _INestBridgeEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _INestBridgeEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _INestBridgeEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _INestBridgeEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _INestBridgeEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _INestBridgeEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _INestBridgeEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___INestBridgeEvents_DISPINTERFACE_DEFINED__ */


#ifndef __INestBridge_INTERFACE_DEFINED__
#define __INestBridge_INTERFACE_DEFINED__

/* interface INestBridge */
/* [object][oleautomation][nonextensible][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_INestBridge;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DF90D3B6-A574-4E44-A71A-F1D6E6918E4C")
    INestBridge : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddToTabbedLog( 
            /* [in] */ BSTR bstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLoggedinUser( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvokeDialog( 
            /* [in] */ long lDialogEnum,
            /* [in] */ BSTR bsParam1,
            /* [in] */ BSTR bsParam2,
            /* [in] */ BSTR bsParam3,
            /* [in] */ BSTR bsParam4) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDialogInfo( 
            /* [in] */ long lDialogEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INestBridgeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INestBridge * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INestBridge * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INestBridge * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            INestBridge * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            INestBridge * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            INestBridge * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            INestBridge * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddToTabbedLog )( 
            INestBridge * This,
            /* [in] */ BSTR bstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLoggedinUser )( 
            INestBridge * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InvokeDialog )( 
            INestBridge * This,
            /* [in] */ long lDialogEnum,
            /* [in] */ BSTR bsParam1,
            /* [in] */ BSTR bsParam2,
            /* [in] */ BSTR bsParam3,
            /* [in] */ BSTR bsParam4);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDialogInfo )( 
            INestBridge * This,
            /* [in] */ long lDialogEnum);
        
        END_INTERFACE
    } INestBridgeVtbl;

    interface INestBridge
    {
        CONST_VTBL struct INestBridgeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INestBridge_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INestBridge_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INestBridge_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INestBridge_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define INestBridge_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define INestBridge_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define INestBridge_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define INestBridge_AddToTabbedLog(This,bstrText)	\
    ( (This)->lpVtbl -> AddToTabbedLog(This,bstrText) ) 

#define INestBridge_GetLoggedinUser(This)	\
    ( (This)->lpVtbl -> GetLoggedinUser(This) ) 

#define INestBridge_InvokeDialog(This,lDialogEnum,bsParam1,bsParam2,bsParam3,bsParam4)	\
    ( (This)->lpVtbl -> InvokeDialog(This,lDialogEnum,bsParam1,bsParam2,bsParam3,bsParam4) ) 

#define INestBridge_GetDialogInfo(This,lDialogEnum)	\
    ( (This)->lpVtbl -> GetDialogInfo(This,lDialogEnum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INestBridge_INTERFACE_DEFINED__ */


#ifndef __IPlusapi_INTERFACE_DEFINED__
#define __IPlusapi_INTERFACE_DEFINED__

/* interface IPlusapi */
/* [object][oleautomation][nonextensible][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_IPlusapi;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5C07F918-033B-4B72-8B6A-F1DB173CE8B1")
    IPlusapi : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PlaceOrder( 
            /* [in] */ BSTR bsTransType,
            /* [in] */ BSTR bsUniqueRefNo,
            /* [in] */ BSTR bsExchange,
            /* [in] */ BSTR bsTradingSymbol,
            /* [in] */ BSTR bsValidity,
            /* [in] */ BSTR bsOrderType,
            /* [in] */ long lQty,
            /* [in] */ double dPrice,
            /* [in] */ double dTriggerPrice,
            /* [in] */ long lDiscQty,
            /* [in] */ BSTR bsProductType,
            /* [in] */ BSTR bsClientID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ModifyOrder( 
            /* [in] */ BSTR bsOrderRefNo,
            /* [in] */ BSTR bsValidity,
            /* [in] */ BSTR bsOrderType,
            /* [in] */ long lQty,
            /* [in] */ double dPrice,
            /* [in] */ double dTriggerPrice,
            /* [in] */ long lDiscQty) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CancelOrder( 
            /* [in] */ BSTR bsOrderRefNum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetObjectName( 
            /* [in] */ BSTR bsObjectName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOrderStatus( 
            /* [in] */ BSTR bsOrderRefNo,
            /* [out] */ BSTR *bsStatus,
            /* [out] */ long *lFillQty,
            /* [out] */ long *lFillPrice) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPlusapiVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPlusapi * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPlusapi * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPlusapi * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPlusapi * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPlusapi * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPlusapi * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPlusapi * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PlaceOrder )( 
            IPlusapi * This,
            /* [in] */ BSTR bsTransType,
            /* [in] */ BSTR bsUniqueRefNo,
            /* [in] */ BSTR bsExchange,
            /* [in] */ BSTR bsTradingSymbol,
            /* [in] */ BSTR bsValidity,
            /* [in] */ BSTR bsOrderType,
            /* [in] */ long lQty,
            /* [in] */ double dPrice,
            /* [in] */ double dTriggerPrice,
            /* [in] */ long lDiscQty,
            /* [in] */ BSTR bsProductType,
            /* [in] */ BSTR bsClientID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ModifyOrder )( 
            IPlusapi * This,
            /* [in] */ BSTR bsOrderRefNo,
            /* [in] */ BSTR bsValidity,
            /* [in] */ BSTR bsOrderType,
            /* [in] */ long lQty,
            /* [in] */ double dPrice,
            /* [in] */ double dTriggerPrice,
            /* [in] */ long lDiscQty);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CancelOrder )( 
            IPlusapi * This,
            /* [in] */ BSTR bsOrderRefNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetObjectName )( 
            IPlusapi * This,
            /* [in] */ BSTR bsObjectName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetOrderStatus )( 
            IPlusapi * This,
            /* [in] */ BSTR bsOrderRefNo,
            /* [out] */ BSTR *bsStatus,
            /* [out] */ long *lFillQty,
            /* [out] */ long *lFillPrice);
        
        END_INTERFACE
    } IPlusapiVtbl;

    interface IPlusapi
    {
        CONST_VTBL struct IPlusapiVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPlusapi_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPlusapi_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPlusapi_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPlusapi_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPlusapi_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPlusapi_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPlusapi_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPlusapi_PlaceOrder(This,bsTransType,bsUniqueRefNo,bsExchange,bsTradingSymbol,bsValidity,bsOrderType,lQty,dPrice,dTriggerPrice,lDiscQty,bsProductType,bsClientID)	\
    ( (This)->lpVtbl -> PlaceOrder(This,bsTransType,bsUniqueRefNo,bsExchange,bsTradingSymbol,bsValidity,bsOrderType,lQty,dPrice,dTriggerPrice,lDiscQty,bsProductType,bsClientID) ) 

#define IPlusapi_ModifyOrder(This,bsOrderRefNo,bsValidity,bsOrderType,lQty,dPrice,dTriggerPrice,lDiscQty)	\
    ( (This)->lpVtbl -> ModifyOrder(This,bsOrderRefNo,bsValidity,bsOrderType,lQty,dPrice,dTriggerPrice,lDiscQty) ) 

#define IPlusapi_CancelOrder(This,bsOrderRefNum)	\
    ( (This)->lpVtbl -> CancelOrder(This,bsOrderRefNum) ) 

#define IPlusapi_SetObjectName(This,bsObjectName)	\
    ( (This)->lpVtbl -> SetObjectName(This,bsObjectName) ) 

#define IPlusapi_GetOrderStatus(This,bsOrderRefNo,bsStatus,lFillQty,lFillPrice)	\
    ( (This)->lpVtbl -> GetOrderStatus(This,bsOrderRefNo,bsStatus,lFillQty,lFillPrice) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPlusapi_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ScripRTD;

#ifdef __cplusplus

class DECLSPEC_UUID("831F7347-85AB-4F88-8252-CEC80930C7B0")
ScripRTD;
#endif

EXTERN_C const CLSID CLSID_NestBridge;

#ifdef __cplusplus

class DECLSPEC_UUID("8604D219-2102-4863-8D22-FDB68D1491FF")
NestBridge;
#endif

EXTERN_C const CLSID CLSID_Plusapi;

#ifdef __cplusplus

class DECLSPEC_UUID("91741D4F-948B-46A0-A2CC-0B925C4F5E17")
Plusapi;
#endif
#endif /* __NESTClientLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


