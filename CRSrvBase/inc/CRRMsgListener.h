#ifndef __CRRMSGLISTENER_H__
#define __CRRMSGLISTENER_H__
#include "CRRMsgRaw.h"
#include "CRSrvEnvCfg.h"
//
class CRSrvRoot;
//
class CRSRV_API CRRMsgListener {
public:
	virtual void onAccept( CRSrvRoot* pSrvRoot, const CRRMsgMetaData& rmsgMetaData ) const = 0;
    virtual void onDisConnect( CRSrvRoot* pSrvRoot, const CRRMsgMetaData& rmsgMetaData ) const = 0;
	virtual void onRMsg( CRSrvRoot* pSrvRoot, const CRRMsgRaw& rmsgRaw ) const = 0;
};



#endif //__CRRMSGLISTENER_H__