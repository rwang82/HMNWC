#include "stdafx.h"
#include "CRTaskClientAccept.h"
#include "CRServerRoot.h"
#include "CRClientStubDepot.h"

CRTaskClientAccept::CRTaskClientAccept(SOCKET sConnect, const sockaddr_in* pAddr)
: m_sConnect( sConnect )
, m_sAddr( *pAddr ) {

}

CRTaskClientAccept::~CRTaskClientAccept() {

}

void CRTaskClientAccept::Run() {
	g_CRSrvRoot.m_pClientStubDepot->regClientStub( m_sConnect, m_sAddr );
}


