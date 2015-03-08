#include "stdafx.h"
#include "CRTaskOnAccept.h"
#include "CRSrvRoot.h"
#include "CRRMsgListener.h"

CRTaskOnAccept::CRTaskOnAccept( SOCKET sConnect, const sockaddr_in* pAddr, CRSrvRoot* pSrvRoot )
: m_rmsgMetaData( sConnect, *pAddr )
, m_pSrvRoot( pSrvRoot ) {

}

CRTaskOnAccept::~CRTaskOnAccept() {

}

void CRTaskOnAccept::Run() {
	if ( !m_pSrvRoot && !m_pSrvRoot->m_pRMsgListener )
		return;
	m_pSrvRoot->m_pRMsgListener->onAccept( m_pSrvRoot, m_rmsgMetaData );
}