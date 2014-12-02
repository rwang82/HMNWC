#include "stdafx.h"
#include "HMNWPEventAdaptor4Server.h"
#include "HMNWPEventHandler4Server.h"
#include "HMNWPClientProxyDepot.h"
#include "HMNWERecvReqDepot.h"
//#include "HMTSHelper.h"
#include "MemFuncPack.h"
#include <assert.h>
HMNWP_NAMESPACE_BEGIN
HMNWPEventAdaptor4Server::HMNWPEventAdaptor4Server( HMNWPEventHandler4Server* pNWPEventHandler, HMNWPClientProxyDepot* pDepotNWPCP )
//: m_pTSAccess( new HMTSHelper() )
: m_pNWPEventHandler( pNWPEventHandler )
, m_pDepotNWPCP( pDepotNWPCP ) {
}

HMNWPEventAdaptor4Server::~HMNWPEventAdaptor4Server() {
	
	//if ( m_pTSAccess ) {
	//	m_pTSAccess->cancelAllAccess();
	//	::Sleep(1);
	//	delete m_pTSAccess;
	//	m_pTSAccess = NULL;
	//}
}

void HMNWPEventAdaptor4Server::_onAccept( HMNWEClientProxy* pNWECP, DWORD dwTrans ) {
	assert( pNWECP );
	//if ( !m_pTSAccess->safeEnterFunc() )
	//	return;
	//CMemFuncPack mfpkSafeExit( m_pTSAccess, &HMTSHelper::safeExitFunc );
	m_pNWPEventHandler->onAccept( pNWECP->getSocket( ), pNWECP->m_sAddr );
	m_pDepotNWPCP->onAccept(pNWECP->getSocket(), pNWECP->m_sAddr, pNWECP->m_szBufData4Accept, dwTrans, m_pNWPEventHandler);
}

void HMNWPEventAdaptor4Server::_onDisConnect( HMNWEClientProxy* pNWECP ) {
	//if ( !m_pTSAccess->safeEnterFunc() )
	//	return;
	//CMemFuncPack mfpkSafeExit( m_pTSAccess, &HMTSHelper::safeExitFunc );
	m_pDepotNWPCP->onDisconnect( pNWECP->getSocket() );
	m_pNWPEventHandler->onDisConnect( pNWECP->getSocket(), pNWECP->m_sAddr );

}

void HMNWPEventAdaptor4Server::_onRecv( HMNWEClientProxy* pNWECP, OVERLAPPED* pOL, DWORD dwTrans ) {
	//if ( !m_pTSAccess->safeEnterFunc() )
	//	return;
	//CMemFuncPack mfpkSafeExit( m_pTSAccess, &HMTSHelper::safeExitFunc );
	const HMNWERecvReq* pNWERecvReq = NULL;

	pNWERecvReq = pNWECP->getRecvReq( pOL );
	m_pDepotNWPCP->onRecv( pNWECP->getSocket(), pNWERecvReq->m_pBufNWData, dwTrans );
}


HMNWP_NAMESPACE_END
