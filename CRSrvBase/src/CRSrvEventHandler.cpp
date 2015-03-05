#include "stdafx.h"
#include "CRSrvEventHandler.h"
#include "CREventDepot.h"
#include "CRSrvEvtDefs.h"

CRSrvEventHandler::CRSrvEventHandler( CREventDepot* pEventDepot )
: m_pEventDepot( pEventDepot ) {

}

CRSrvEventHandler::~CRSrvEventHandler() {

}

void CRSrvEventHandler::onAccept( SOCKET sConnect, const sockaddr_in& saddrConnect ) {
	if ( !m_pEventDepot )
		return;
	m_pEventDepot->fire( ECRSRVEVT_CLIENT_ACCEPTED, (void*)sConnect, (void*)&saddrConnect );
}

void CRSrvEventHandler::onDisConnect( SOCKET sConnect, const sockaddr_in& saddrConnect ) {
	if ( !m_pEventDepot )
		return;
	m_pEventDepot->fire( ECRSRVEVT_CLIENT_DISCONNECTED, (void*)sConnect, (void*)&saddrConnect );
}

void CRSrvEventHandler::onRecvBuffer( SOCKET sConnect, const sockaddr_in& saddrConnect, const unsigned char* pBufPayload, unsigned int uLenPayload ) {
	if ( !m_pEventDepot )
		return;
	m_pEventDepot->fire( ECRSRVEVT_CLIENT_REQUEST, 
		(void*)sConnect, 
		(void*)&saddrConnect, 
		(void*)pBufPayload, 
		(void*)uLenPayload );
}


