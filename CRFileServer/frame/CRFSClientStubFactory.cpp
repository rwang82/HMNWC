#include "stdafx.h"
#include "CRFSClientStubFactory.h"
#include "CRFSClientStub.h"

CRFSClientStubFactory::CRFSClientStubFactory() {

}

CRFSClientStubFactory::~CRFSClientStubFactory() {

}

CRClientStub* CRFSClientStubFactory::createClientStub( CRSrvRoot* pSrvRoot, SOCKET sConnect, const sockaddr_in& sAddr ) {
    return new CRFSClientStub( pSrvRoot, sConnect, sAddr );
}