#include "stdafx.h"
#include "CRSrvEventHandler.h"
#include "CRRMsgParser.h"
#include "CRServerRoot.h"
#include "CRSrvEvtDefs.h"
#include "hmcmn_event_depot.h"
#include <atlconv.h>

CRSrvEventHandler::CRSrvEventHandler() {

}

CRSrvEventHandler::~CRSrvEventHandler() {
}

void CRSrvEventHandler::onAccept(SOCKET sConnect, const sockaddr_in& saddrConnect) {
	g_CRSrvRoot.m_pEventDepot->fire( ECRSRVEVT_CLIENT_ACCEPTED, (void*)sConnect, (void*)&saddrConnect );
}

void CRSrvEventHandler::onDisConnect(SOCKET sConnect, const sockaddr_in& saddrConnect) {
	g_CRSrvRoot.m_pEventDepot->fire( ECRSRVEVT_CLIENT_DISCONNECTED, (void*)sConnect, (void*)&saddrConnect );
}

void CRSrvEventHandler::onRecvBuffer(SOCKET sConnect, const sockaddr_in& saddrConnect, const unsigned char* pBufPayload, unsigned int uLenPayload) {
	g_CRSrvRoot.m_pEventDepot->fire( ECRSRVEVT_CLIENT_REQUEST, 
		(void*)sConnect, (void*)&saddrConnect, (void*)pBufPayload, (void*)uLenPayload );
}
