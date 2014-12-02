#include "stdafx.h"
#include "HMTSHelper.h"
#include "HMNWEClientProxyDepot.h"
#include "HMNWERecvReqDepot.h"
#include "HMNWESendReqDepot.h"
#include "HMNWEEventHandler4Server.h"
#include "HMNWEFuncLoader4Server.h"
#include "FuncPack.h"
#include "MemFuncPack.h"
#include "tchar.h"
#include <assert.h>
#include <mswsock.h>
//
//
HMNWEClientProxy::HMNWEClientProxy( SOCKET sConnect, HANDLE hCompletion, HMNWEEventHandler4Server* pEventHandler )
: m_sConnect(sConnect)
, m_uID( _allocateId() )
, m_hCompletion( hCompletion )
, m_pRecvReqDepot( new HMNWERecvReqDepot() )
, m_pSendReqDepot( new HMNWESendReqDepot() )
, m_pEventHandler( pEventHandler ) {
	//
	::memset( m_szBufData4Accept, 0, BUFSIZE_ACCEPT_NWDATA );
	::memset( &m_olAccept, 0, sizeof( OVERLAPPED ) );
}

HMNWEClientProxy::~HMNWEClientProxy() {
	if ( m_sConnect ) {
		::shutdown( m_sConnect, SD_BOTH );
		::closesocket( m_sConnect );
	}
	if ( m_pSendReqDepot ) {
		delete m_pSendReqDepot;
		m_pSendReqDepot = NULL;
	}
	if ( m_pRecvReqDepot ) {
		delete m_pRecvReqDepot;
		m_pRecvReqDepot = NULL;
	}
}

unsigned int HMNWEClientProxy::_allocateId() {
	static unsigned int s_idBase = 0;
	return ++s_idBase;
}

void HMNWEClientProxy::onIOEvent( LPOVERLAPPED pOL, DWORD dwTrans, bool& bEatEvent ) {
	if ( pOL == &m_olAccept ) { // accept event.
		bEatEvent = true;

		if ( dwTrans == 0 ) {
			return; // server quit
		}
		//
		::CreateIoCompletionPort( ( HANDLE )m_sConnect, m_hCompletion, ( DWORD )m_uID, 0 );
		//
		if ( !_getPeerAddr( m_sAddr ) ) {
			assert( false );
		}
		//
		if ( m_pEventHandler ) {
			m_pEventHandler->onAccept( this, dwTrans );
		}
		//
		_postRecvReq( 1 );
	} else if ( m_pRecvReqDepot->hasRecvReq( pOL ) ) { // receive data event.
		bEatEvent = true;
		//
		if ( m_pEventHandler ) {
			if ( dwTrans != 0 ) {
				m_pEventHandler->onRecv( this, pOL, dwTrans );
			} else {
				m_pEventHandler->onDisConnect( this );
			}
		}
		//
		if ( dwTrans != 0 ) {
			m_pRecvReqDepot->removeReq( pOL );
			_postRecvReq( 1 );
		}
	} else if ( m_pSendReqDepot->hasReq( pOL ) ) { // send data event.
		bEatEvent = true;
		//
		m_pSendReqDepot->removeReq( pOL );
	} else {
		bEatEvent = false;
	}
}

bool HMNWEClientProxy::_getPeerAddr( sockaddr_in& sAddrPeer ) const {
	HMNWEFuncLoader4Server* pNWEFuncLoader = NULL;

	::OutputDebugString( _T("1\n") );
	pNWEFuncLoader = HMNWEFuncLoader4Server::getInstance();
	if ( !pNWEFuncLoader || !pNWEFuncLoader->m_pfnGetAcceptExSockaddrs ) {
		::OutputDebugString( _T( "2\n" ) );
		return false;
	}
	int nLenLocal;
	int nLenRemote;
	LPSOCKADDR pLocalAddr;
	LPSOCKADDR pRemoteAddr;
	unsigned int uLenBuf = 512 + 2 * ( sizeof( sockaddr_in )+16 );
	unsigned char* pBuf = new unsigned char[ uLenBuf ];
	::OutputDebugString( _T( "3\n" ) );
	CFuncPack fpkDelBuf( ::gfnDelBuf<unsigned char>, pBuf );
	::OutputDebugString( _T( "4\n" ) );

	pNWEFuncLoader->m_pfnGetAcceptExSockaddrs(
		(PVOID)m_szBufData4Accept,
		BUFSIZE_ACCEPT_NWDATA - ( sizeof( sockaddr_in )+16 ) * 2,
		sizeof( sockaddr_in )+16,
		sizeof( sockaddr_in )+16,
		( SOCKADDR** )&pLocalAddr,
		&nLenLocal,
		( SOCKADDR** )&pRemoteAddr,
		&nLenRemote );

	sAddrPeer = *( ( sockaddr_in* )pRemoteAddr );

	::OutputDebugString( _T( "5\n" ) );
	return true;
}

//bool HMNWEClientProxy::_postRecvReq( unsigned int uReqCount ) {
//	WSABUF* aryWSABuf = new WSABUF[ uReqCount ];
//	CFuncPack fpkDelWSABufAry( ::gfnDelArray< WSABUF >, aryWSABuf );
//
//	for ( unsigned int uReqIndex = 0; uReqIndex < uReqCount; ++uReqIndex ) {
//		aryWSABuf[ uReqIndex ].buf = 
//	}
//
//}

bool HMNWEClientProxy::_postRecvReq( unsigned int uReqCount ) {
	WSABUF buf;
	DWORD dwTrans;
	DWORD dwFlags;
	DWORD dwErr;
	const HMNWERecvReq* pNWERecvReq = NULL;

	for ( unsigned int uReqIndex = 0; uReqIndex < uReqCount; ++uReqIndex ) {
		pNWERecvReq = m_pRecvReqDepot->createRecvReq();
		dwTrans = 0;
		dwFlags = 0;
		buf.buf = ( char* )pNWERecvReq->m_pBufNWData;
		buf.len = pNWERecvReq->m_uLenBuf;
		if ( 0 != ::WSARecv( m_sConnect, &buf, 1, &dwTrans, &dwFlags, (LPWSAOVERLAPPED)&pNWERecvReq->m_ol, NULL ) ) {
			dwErr = ::WSAGetLastError();
			if ( dwErr != WSA_IO_PENDING ) {
				if ( dwErr == WSAECONNRESET ) {
					break; // An existing connection was forcibly closed by the remote host.
				}
				assert( false );
				return false;
			}
		}
	}

	return true;
}

bool HMNWEClientProxy::_send( const unsigned char* pBuf, unsigned int uLenBuf ) {
	if ( !pBuf || ( uLenBuf == 0 ) ) {
		return false;
	}
	HMNWESendReq* pSendReq = NULL;
	int nRes;
	DWORD dwTrans;
	DWORD dwFlag;
	DWORD dwErr;
	WSABUF wsaBuf;

	pSendReq = m_pSendReqDepot->createReq( pBuf, uLenBuf );
	wsaBuf.buf = ( char* )pSendReq->m_pBufNWData;
	wsaBuf.len = pSendReq->m_uLenBuf;
	dwFlag = 0;
	nRes = ::WSASend( m_sConnect, &wsaBuf, 1, &dwTrans, dwFlag, &pSendReq->m_ol, NULL );
	if ( nRes != 0 ) {
		dwErr = ::WSAGetLastError();
		if ( dwErr != WSA_IO_PENDING ) {
			assert( false );
			return false;
		}
	}

	return true;
}

const HMNWERecvReq* HMNWEClientProxy::getRecvReq( LPOVERLAPPED pOL ) {
	if ( m_pRecvReqDepot ) {
		return m_pRecvReqDepot->getRecvReq( pOL );
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
HMNWEClientDepot::HMNWEClientDepot()
: m_pTSHelper( new HMTSHelper() ) {

}

HMNWEClientDepot::~HMNWEClientDepot() {
	//
	m_pTSHelper->cancelAllAccess();
	//
	::Sleep( 1 );
	//
	_clearAll();
	//
	if ( m_pTSHelper ) {
		delete m_pTSHelper;
		m_pTSHelper = NULL;
	}
}

HMNWEClientProxy* HMNWEClientDepot::createClientProxy( SOCKET sConnect, HANDLE hCompletion, HMNWEEventHandler4Server* pEventHandler) {
	if (!m_pTSHelper->safeEnterFunc()) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );

	HMNWEClientProxy* pNWEConnectProxy = new HMNWEClientProxy( sConnect, hCompletion, pEventHandler );
	m_containerConnectProxy.push_back(pNWEConnectProxy);
	return pNWEConnectProxy;
}

HMNWEClientProxy* HMNWEClientDepot::getConnectProxy(unsigned int uCPId) {
	if (!m_pTSHelper->safeEnterFunc()) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit(m_pTSHelper, &HMTSHelper::safeExitFunc);

	return _getConnectProxy(uCPId);
}

HMNWEClientProxy* HMNWEClientDepot::_getConnectProxy(unsigned int uCPId) const {
	clientproxy_container_type::const_iterator citCP, ciendCP;
	HMNWEClientProxy* pNWECP = NULL;

	ciendCP = m_containerConnectProxy.end();
	for (citCP = m_containerConnectProxy.begin(); citCP != ciendCP; ++citCP) {
		pNWECP = ( *citCP );
		if (pNWECP->getId() == uCPId) {
			return pNWECP;
		}
	}

	assert(false);
	return NULL;
}

bool HMNWEClientDepot::hasConnectProxy(unsigned int uCPId) const {
	if (!m_pTSHelper->safeEnterFunc()) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit(m_pTSHelper, &HMTSHelper::safeExitFunc);

	return ( NULL != _getConnectProxy(uCPId) );
}

void HMNWEClientDepot::removeClientProxy( unsigned int uCPId ) {
	if ( !m_pTSHelper->safeEnterFunc() ) {
		return;
	}
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );
	clientproxy_container_type::iterator itCP, iendCP;
	HMNWEClientProxy* pNWECP = NULL;

	iendCP = m_containerConnectProxy.end();
	for ( itCP = m_containerConnectProxy.begin(); itCP != iendCP; ++itCP ) {
		pNWECP = *itCP;
		if ( pNWECP->getId() == uCPId ) {
			m_containerConnectProxy.erase( itCP );
			delete pNWECP;
			pNWECP = NULL;
			return;
		}
	}
	assert( false );
}

void HMNWEClientDepot::_clearAll() {
	clientproxy_container_type::iterator itCP, iendCP;
	HMNWEClientProxy* pNWECP = NULL;

	iendCP = m_containerConnectProxy.end();
	for ( itCP = m_containerConnectProxy.begin(); itCP != iendCP; ++itCP ) {
		pNWECP = *itCP;
		if ( pNWECP ) {
			delete pNWECP;
			pNWECP = NULL;
		}
	}
	m_containerConnectProxy.clear();
}

void HMNWEClientDepot::onIOEvent( LPOVERLAPPED pOL, DWORD dwTrans ) {
	if ( !m_pTSHelper->safeEnterFunc() ) {
		return;
	}
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );
	clientproxy_container_type::iterator itCP, iendCP;
	HMNWEClientProxy* pNWECP = NULL;
	bool bEatEvent = false;

	iendCP = m_containerConnectProxy.end();
	for ( itCP = m_containerConnectProxy.begin(); itCP != iendCP; ++itCP ) {
		pNWECP = *itCP;
		bEatEvent = false;
		pNWECP->onIOEvent( pOL, dwTrans, bEatEvent );
		if ( bEatEvent ) {
			if ( dwTrans == 0 ) { // client close socket.
				delete pNWECP;
				pNWECP = NULL;
				m_containerConnectProxy.erase( itCP );
			}
			break;
		}
	}
}

bool HMNWEClientDepot::send( SOCKET sConnect, const unsigned char* pBufData, unsigned int uLenBuf ) {
	if ( !m_pTSHelper->safeEnterFunc() ) {
		return false;
	}
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );
	clientproxy_container_type::iterator itCP, iendCP;
	HMNWEClientProxy* pNWECP = NULL;
	bool bEatEvent = false;

	iendCP = m_containerConnectProxy.end();
	for ( itCP = m_containerConnectProxy.begin(); itCP != iendCP; ++itCP ) {
		pNWECP = *itCP;
		if ( pNWECP->getSocket() == sConnect ) {
			return pNWECP->_send( pBufData, uLenBuf );
		}
	}
	return false;
}
