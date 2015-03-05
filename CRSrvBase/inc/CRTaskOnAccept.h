#ifndef __CRTASKONACCEPT_H__
#define __CRTASKONACCEPT_H__
#include "HMTaskEngine.h"
#include "CRClientStubDepot.h"

class CRTaskOnAccept : public HMTaskBase {

public:
	CRTaskOnAccept( SOCKET sConnect, const sockaddr_in* pAddr, CRClientStubDepot* pClientStubDepot );
	virtual ~CRTaskOnAccept();

public:
	virtual void Run();

private:
	SOCKET m_sConnect;
	sockaddr_in m_sAddr;
	CRClientStubDepot* m_pClientStubDepot;
};


#endif //__CRTASKONACCEPT_H__