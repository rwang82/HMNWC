#include "stdafx.h"
#include "CRTaskOnAccept.h"

CRTaskOnAccept::CRTaskOnAccept( SOCKET sConnect, const sockaddr_in* pAddr, CRClientStubDepot* pClientStubDepot )
: m_sConnect( sConnect )
, m_sAddr( *pAddr )
, m_pClientStubDepot( pClientStubDepot ) {

}

CRTaskOnAccept::~CRTaskOnAccept() {

}

void CRTaskOnAccept::Run() {
	if ( !m_pClientStubDepot )
		return;
	m_pClientStubDepot->regClientStub( m_sConnect, m_sAddr );
}