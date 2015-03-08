#ifndef __CRTASKONACCEPT_H__
#define __CRTASKONACCEPT_H__
#include "HMTaskEngine.h"
#include "CRRMsgRaw.h"
//
class CRSrvRoot;
//
class CRTaskOnAccept : public HMTaskBase {

public:
	CRTaskOnAccept( SOCKET sConnect, const sockaddr_in* pAddr, CRSrvRoot* pSrvRoot );
	virtual ~CRTaskOnAccept();

public:
	virtual void Run();

private:
	CRRMsgMetaData m_rmsgMetaData;
	CRSrvRoot* m_pSrvRoot;;
};


#endif //__CRTASKONACCEPT_H__