#ifndef __CRRMSGLISTENER_H__
#define __CRRMSGLISTENER_H__
#include "CRRMsgRaw.h"
#include "CRClientStub.h"
//
class CRSrvRoot;
//
class CRRMsgListener {
public:
	virtual void onRMsg( CRSrvRoot* pSrvRoot, const CRRMsgRaw& rmsgRaw, CRClientStub* pClientStub ) = 0;
};



#endif //__CRRMSGLISTENER_H__