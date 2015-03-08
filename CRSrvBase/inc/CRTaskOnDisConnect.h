#ifndef __CRTASKONDISCONNECT_H__
#define __CRTASKONDISCONNECT_H__
#include "HMTaskEngine.h"
#include "CRRMsgRaw.h"
//
class CRSrvRoot;
//
class CRTaskOnDisConnect : public HMTaskBase {

public:
	CRTaskOnDisConnect( SOCKET sConnect, const sockaddr_in* pAddr, CRSrvRoot* pSrvRoot );
	virtual ~CRTaskOnDisConnect();

public:
	virtual void Run();
	
private:
	CRRMsgMetaData m_rmsgMetaData;
	CRSrvRoot* m_pSrvRoot;
};




#endif //__CRTASKONDISCONNECT_H__