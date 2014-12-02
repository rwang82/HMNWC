#ifndef __CRTASKCMDCLIENTACCEPT_H__
#define __CRTASKCMDCLIENTACCEPT_H__
#include "HMTaskEngine.h"

class CRTaskClientAccept : public HMTaskBase {
public:
	CRTaskClientAccept( SOCKET sConnect, const sockaddr_in* pAddr );
	virtual ~CRTaskClientAccept();

public:
	virtual void Run();

private:
	SOCKET m_sConnect;
	sockaddr_in m_sAddr;
};

#endif //__CRTASKCMDCLIENTACCEPT_H__