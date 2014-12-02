#include "stdafx.h"
#include "HMNWPClientProxyDepot.h"
#include "HMNWPUnPackImpl.h"
#include "HMNWEFuncLoader4Server.h"
#include "HMTSHelper.h"
#include "MemFuncPack.h"
#include <assert.h>
HMNWP_NAMESPACE_BEGIN
//
HMNWPClientProxy::HMNWPClientProxy( SOCKET sConnect, const sockaddr_in& sAddr, HMNWPEventHandler4Server* pNWPEventHandler4Server )
: m_sConnect( sConnect )
, m_sAddr( sAddr )
, m_pNWPUnPackImpl( new HMNWPUnPackImpl() )
, m_pNWPEventHandler4Server( pNWPEventHandler4Server ) {
	m_pNWPUnPackImpl->m_eventRawBufReady.bind( this, &HMNWPClientProxy::onEvtRawBufReady );
	
}

HMNWPClientProxy::~HMNWPClientProxy() {
	if ( m_pNWPUnPackImpl ) {
		delete m_pNWPUnPackImpl;
		m_pNWPUnPackImpl = NULL;
	}
}

//void HMNWPClientProxy::send( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
//	
//}

void HMNWPClientProxy::onRecv( const unsigned char* pPackageBuf, unsigned int uLenPackageBuf ) {
	if ( m_pNWPUnPackImpl ) {
		m_pNWPUnPackImpl->onRecvRawData( pPackageBuf, uLenPackageBuf );
	}
}

void HMNWPClientProxy::onDisconnect() {

}

void HMNWPClientProxy::onEvtRawBufReady( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
	if ( m_pNWPEventHandler4Server ) {
		m_pNWPEventHandler4Server->onRecvBuffer( m_sConnect, m_sAddr, pRawBuf, uLenRawBuf );
	}
}

//////////////////////////////////////////////////////////////////////////
HMNWPClientProxyDepot::HMNWPClientProxyDepot()
: m_pTSHelper( new HMTSHelper() ) {

}

HMNWPClientProxyDepot::~HMNWPClientProxyDepot() {
	if ( m_pTSHelper ) {
		delete m_pTSHelper;
		m_pTSHelper = NULL;
	}
	//
	_clearAllNWPCP();
}

void HMNWPClientProxyDepot::onRecv( SOCKET sConnect, const unsigned char* pBuf, unsigned int uLenBuf ) {
	if ( !m_pTSHelper->safeEnterFunc() ) {
		return;
	}
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );
	socket2cp_map_type::iterator itS2CP;
	HMNWPClientProxy* pNWPCP = NULL;

	itS2CP = m_mapSocket2CP.find( sConnect );
	if ( itS2CP == m_mapSocket2CP.end() ) {
		return;
	}
	pNWPCP = itS2CP->second;
	assert( pNWPCP );
	pNWPCP->onRecv( pBuf, uLenBuf );
}

void HMNWPClientProxyDepot::onAccept( SOCKET sConnect, const sockaddr_in& sAddr, const unsigned char* pBuf, unsigned int uLenBuf, HMNWPEventHandler4Server* pNWPEventHandler4Server ) {
	if ( !m_pTSHelper->safeEnterFunc() ) {
		return;
	}
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );
	socket2cp_map_type::iterator itS2CP, iendS2CP;
	HMNWPClientProxy* pNWPCP = NULL;

	itS2CP = m_mapSocket2CP.find( sConnect );
	assert( itS2CP == m_mapSocket2CP.end() );
	pNWPCP = new HMNWPClientProxy( sConnect, sAddr, pNWPEventHandler4Server );
	m_mapSocket2CP[ sConnect ] = pNWPCP;
	//
	pNWPCP->onRecv( pBuf, uLenBuf );
}

void HMNWPClientProxyDepot::onDisconnect(SOCKET sConnect) {
	if (!m_pTSHelper->safeEnterFunc()) {
		return;
	}
	CMemFuncPack mfpkSafeExit(m_pTSHelper, &HMTSHelper::safeExitFunc);
	socket2cp_map_type::iterator itS2CP;
	HMNWPClientProxy* pNWPCP = NULL;

	itS2CP = m_mapSocket2CP.find( sConnect );
	if ( itS2CP == m_mapSocket2CP.end()) {
		assert( false );
		return;
	}
	//
	pNWPCP = itS2CP->second;
	pNWPCP->onDisconnect();
	//
	delete pNWPCP;
	pNWPCP = NULL;
	m_mapSocket2CP.erase( itS2CP );
}

void HMNWPClientProxyDepot::_clearAllNWPCP() {
	socket2cp_map_type::iterator itS2CP, iendS2CP;
	HMNWPClientProxy* pNWPCP = NULL;

	iendS2CP = m_mapSocket2CP.end();
	for ( itS2CP = m_mapSocket2CP.begin(); itS2CP != iendS2CP; ++itS2CP ) {
		pNWPCP = itS2CP->second;
		delete pNWPCP;
		pNWPCP = NULL;
	}
	m_mapSocket2CP.clear();
	m_mapSocket2CP.swap( socket2cp_map_type() );
}

HMNWP_NAMESPACE_END
