#ifndef __CRSRVROOT_H__
#define __CRSRVROOT_H__
#include "CRSrvEnvCfg.h"
#include "CRModuleDepot.h"
#include "CREventDepot.h"
#include "CRRMsgListener.h"
#include "HMNWPServer.h"

class CRSRV_API CRSrvRoot {
public:
	CRSrvRoot( const CRRMsgListener* pRMsgListener );
	virtual ~CRSrvRoot();

private:
	void _init();
	void _unInit();

public:
	CREventDepot m_eventDepot;
	CRModuleDepot m_moduleDepot;
	const CRRMsgListener* m_pRMsgListener;
	//
	hmnwp::HMNWPServer m_nwpServer;
	//
};


#endif //__CRSRVROOT_H__