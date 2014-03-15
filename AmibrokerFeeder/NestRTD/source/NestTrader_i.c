

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Mar 15 12:56:41 2014
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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_NESTClientLib,0x302DC8E2,0xFAA2,0x4E96,0xAC,0xFE,0x07,0xA3,0x31,0x8D,0xCB,0xDD);


MIDL_DEFINE_GUID(IID, IID_IScripRTD,0xEC0E6191,0xDB51,0x11D3,0x8F,0x3E,0x00,0xC0,0x4F,0x36,0x51,0xB8);


MIDL_DEFINE_GUID(IID, IID_IRTDUpdateEvent,0xA43788C1,0xD91B,0x11D3,0x8F,0x39,0x00,0xC0,0x4F,0x36,0x51,0xB8);


MIDL_DEFINE_GUID(IID, DIID__INestBridgeEvents,0x5BFBF197,0x6FC4,0x4970,0xAC,0xC7,0x49,0x4F,0x25,0x2B,0x39,0x0F);


MIDL_DEFINE_GUID(IID, IID_INestBridge,0xDF90D3B6,0xA574,0x4E44,0xA7,0x1A,0xF1,0xD6,0xE6,0x91,0x8E,0x4C);


MIDL_DEFINE_GUID(IID, IID_IPlusapi,0x5C07F918,0x033B,0x4B72,0x8B,0x6A,0xF1,0xDB,0x17,0x3C,0xE8,0xB1);


MIDL_DEFINE_GUID(CLSID, CLSID_ScripRTD,0x831F7347,0x85AB,0x4F88,0x82,0x52,0xCE,0xC8,0x09,0x30,0xC7,0xB0);


MIDL_DEFINE_GUID(CLSID, CLSID_NestBridge,0x8604D219,0x2102,0x4863,0x8D,0x22,0xFD,0xB6,0x8D,0x14,0x91,0xFF);


MIDL_DEFINE_GUID(CLSID, CLSID_Plusapi,0x91741D4F,0x948B,0x46A0,0xA2,0xCC,0x0B,0x92,0x5C,0x4F,0x5E,0x17);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



