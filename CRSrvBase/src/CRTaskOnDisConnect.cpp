#include "stdafx.h"
#include "CRTaskOnDisConnect.h"

CRTaskOnDisConnect::CRTaskOnDisConnect( SOCKET sConnect, const sockaddr_in* pAddr, CRClientStubDepot* pClientStubDepot )
: m_sConnect( sConnect )
, m_sAddr( *pAddr )
, m_pClientStubDepot( pClientStubDepot ) {

}

CRTaskOnDisConnect::~CRTaskOnDisConnect() {

}

void CRTaskOnDisConnect::Run() {
	m_pClientStubDepot->unregClientStub( m_sConnect );
}
