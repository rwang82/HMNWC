#ifndef __CRFSCLIENTSTUBFACTORY_H__
#define __CRFSCLIENTSTUBFACTORY_H__
#include "CRClientStubFactoryBase.h"

class CRFSClientStubFactory : public CRClientStubFactoryBase {
public:
	CRFSClientStubFactory();
	virtual ~CRFSClientStubFactory();

public:
	virtual CRClientStub* createClientStub( CRSrvRoot* pSrvRoot, SOCKET sConnect, const sockaddr_in& sAddr );
};




#endif //__CRFSCLIENTSTUBFACTORY_H__