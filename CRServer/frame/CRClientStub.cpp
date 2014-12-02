#include "stdafx.h"
#include "CRClientStub.h"

CRClientStub::CRClientStub( SOCKET sConnect, const sockaddr_in& sAddr )
: m_sConnect( sConnect )
, m_sAddr( sAddr ) {

}

CRClientStub::~CRClientStub() {

}




