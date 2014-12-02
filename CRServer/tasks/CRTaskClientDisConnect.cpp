#include "stdafx.h"
#include "CRTaskClientDisConnect.h"
#include "CRServerRoot.h"
#include "CRClientStubDepot.h"

CRTaskClientDisConnect::CRTaskClientDisConnect(SOCKET sConnect, const sockaddr_in* pAddr)
: m_sConnect( sConnect )
, m_sAddr( *pAddr ) {

}

CRTaskClientDisConnect::~CRTaskClientDisConnect() {

}

void CRTaskClientDisConnect::Run() {
	g_CRSrvRoot.m_pClientStubDepot->unregClientStub( m_sConnect );
}