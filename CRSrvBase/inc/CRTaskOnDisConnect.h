#ifndef __CRTASKONDISCONNECT_H__
#define __CRTASKONDISCONNECT_H__
#include "HMTaskEngine.h"
#include "CRClientStubDepot.h"

class CRTaskOnDisConnect : public HMTaskBase {

public:
	CRTaskOnDisConnect( SOCKET sConnect, const sockaddr_in* pAddr, CRClientStubDepot* pClientStubDepot );
	virtual ~CRTaskOnDisConnect();

public:
	virtual void Run();
	
private:
	SOCKET m_sConnect;
	sockaddr_in m_sAddr;
	CRClientStubDepot* m_pClientStubDepot;
};




#endif //__CRTASKONDISCONNECT_H__