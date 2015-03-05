#include "stdafx.h"
#include "CRClientStub.h"
#include "CRRMsgRaw.h"

CRClientStub::CRClientStub( CRSrvRoot* pSrvRoot, SOCKET sConnect, const sockaddr_in& sAddr )
: m_pSrvRoot( pSrvRoot )
, m_sConnect( sConnect )
, m_sAddr( sAddr ) {

}

CRClientStub::~CRClientStub() {

}




