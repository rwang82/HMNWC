#include "stdafx.h"
#include "CRTaskClientDisConnect.h"
#include "CRServerRoot.h"
#include "CRClientStubDepot.h"
#include "CRModuleDepot.h"
#include "CRModuleAccountMgr.h"
#include "CRModuleIdDefs.h"

CRTaskClientDisConnect::CRTaskClientDisConnect(SOCKET sConnect, const sockaddr_in* pAddr)
: m_sConnect( sConnect )
, m_sAddr( *pAddr ) {

}

CRTaskClientDisConnect::~CRTaskClientDisConnect() {

}

void CRTaskClientDisConnect::Run() {
	//
	CRModuleAccountMgr* pAccountMgr = NULL;
	pAccountMgr = (CRModuleAccountMgr*)g_CRSrvRoot.m_pModuleDepot->getModule(ECRMODULE_ID_ACCOUNTMGR);
	if ( pAccountMgr ) {
	    pAccountMgr->onEvtClientDisConnect( (void*)m_sConnect, (void*)&m_sAddr );
	}
	//
	g_CRSrvRoot.m_pClientStubDepot->unregClientStub( m_sConnect );
}