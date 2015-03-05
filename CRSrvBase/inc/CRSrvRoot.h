#ifndef __CRSRVROOT_H__
#define __CRSRVROOT_H__
#include "CRSrvEnvCfg.h"
#include "CRModuleDepot.h"
#include "CRModuleDepot.h"
#include "CREventDepot.h"
#include "HMNWPServer.h"
#include "CRClientStubFactoryBase.h"
#include "CRClientStubDepot.h"

class CRSRV_API CRSrvRoot {
public:
	CRSrvRoot( CRClientStubFactoryBase* pCSF );
	virtual ~CRSrvRoot();

private:
	void _init();
	void _unInit();

public:
	CREventDepot m_eventDepot;
	CRModuleDepot m_moduleDepot;
	CRClientStubDepot m_clientStubDepot;
	//
	hmnwp::HMNWPServer m_nwpServer;
	//
	CRClientStubFactoryBase* m_pCSF;
};


#endif //__CRSRVROOT_H__