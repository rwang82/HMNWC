#ifndef __CRCLIENTSTUBFACTORYBASE_H__
#define __CRCLIENTSTUBFACTORYBASE_H__
#include "winsock2.h"
//
class CRClientStub;
class CRSrvRoot;
//
class CRClientStubFactoryBase {
public:
	CRClientStubFactoryBase(){};
	virtual ~CRClientStubFactoryBase(){};

public:
	virtual CRClientStub* createClientStub( CRSrvRoot* pSrvRoot, SOCKET sConnect, const sockaddr_in& sAddr ) = 0;
};



#endif //__CRCLIENTSTUBFACTORYBASE_H__