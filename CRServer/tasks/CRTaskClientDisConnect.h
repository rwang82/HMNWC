#ifndef __CRTASKCMDCLIENTDISCONNECT_H__
#define __CRTASKCMDCLIENTDISCONNECT_H__
#include "HMTaskEngine.h"

class CRTaskClientDisConnect : public HMTaskBase {
public:
	CRTaskClientDisConnect(SOCKET sConnect, const sockaddr_in* pAddr);
	virtual ~CRTaskClientDisConnect();

public:
	virtual void Run();

private:
	SOCKET m_sConnect;
	sockaddr_in m_sAddr;
};


#endif //__CRTASKCMDCLIENTDISCONNECT_H__