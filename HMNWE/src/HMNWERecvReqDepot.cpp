#include "stdafx.h"
#include "HMTSHelper.h"
#include "HMNWERecvReqDepot.h"
#include "HMNWEEnvCfg.h"
#include "MemFuncPack.h"
#include <assert.h>
//
HMNWERecvReq::HMNWERecvReq()
: m_pBufNWData( new unsigned char[ BUFSIZE_RECV_NWDATA ] )
, m_uLenBuf( BUFSIZE_RECV_NWDATA ) {
	::memset( &m_ol, 0, sizeof( OVERLAPPED ) );
}

HMNWERecvReq::~HMNWERecvReq() {
	if ( m_pBufNWData ) {
		delete[] m_pBufNWData;
		m_pBufNWData = NULL;
	}
}

HMNWERecvReqDepot::HMNWERecvReqDepot()
: m_pTSHelper( new HMTSHelper() ) {

}

HMNWERecvReqDepot::~HMNWERecvReqDepot() {
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

const HMNWERecvReq* HMNWERecvReqDepot::createRecvReq() {
	if ( !m_pTSHelper->safeEnterFunc() ) {
		assert( false );
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );
	HMNWERecvReq* pRecvReq = NULL;

	pRecvReq = new HMNWERecvReq();
	m_containerRecvReq.push_back( pRecvReq );
	return pRecvReq;
}


bool HMNWERecvReqDepot::hasRecvReq( const OVERLAPPED* pOL ) const {
	if ( !m_pTSHelper->safeEnterFunc() ) {
		assert( false );
		return false;
	}
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );

	return _hasRecvReq( pOL );
}

bool HMNWERecvReqDepot::_hasRecvReq( const OVERLAPPED* pOL ) const {
	recvreq_container_type::const_iterator citRecvReq, ciendRecvReq;
	const HMNWERecvReq* pRecvReq = NULL;

	ciendRecvReq = m_containerRecvReq.end();
	for ( citRecvReq = m_containerRecvReq.begin(); citRecvReq != ciendRecvReq; ++citRecvReq ) {
		pRecvReq = *citRecvReq;
		if ( &( pRecvReq->m_ol ) == pOL ) {
			return true;
		}
	}

	return false;
}

void HMNWERecvReqDepot::removeReq( const OVERLAPPED* pOL ) {
	if ( !m_pTSHelper->safeEnterFunc() ) {
		assert( false );
		return;
	}
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );

	_removeReq( pOL );
}

void HMNWERecvReqDepot::_removeReq( const OVERLAPPED* pOL ) {
	recvreq_container_type::iterator itRecvReq, iendRecvReq;
	const HMNWERecvReq* pRecvReq = NULL;

	iendRecvReq = m_containerRecvReq.end();
	for ( itRecvReq = m_containerRecvReq.begin(); itRecvReq != iendRecvReq; ++itRecvReq ) {
		pRecvReq = *itRecvReq;
		if ( pRecvReq && ( &( pRecvReq->m_ol ) == pOL ) ) {
			delete pRecvReq;
			pRecvReq = NULL;
			m_containerRecvReq.erase( itRecvReq );
			return;
		}
	}
}

void HMNWERecvReqDepot::_clearAll() {
	recvreq_container_type::iterator itRecvReq, iendRecvReq;
	HMNWERecvReq* pRecvReq = NULL;

	iendRecvReq = m_containerRecvReq.end();
	for ( itRecvReq = m_containerRecvReq.begin(); itRecvReq != iendRecvReq; ++itRecvReq ) {
		pRecvReq = *itRecvReq;
		if ( pRecvReq ) {
			delete pRecvReq;
			pRecvReq = NULL;
		}
	}
	m_containerRecvReq.clear();
}

const HMNWERecvReq* HMNWERecvReqDepot::getRecvReq( const OVERLAPPED* pOL ) const {
	if ( !m_pTSHelper->safeEnterFunc() ) {
		assert( false );
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );
	
	return _getRecvReq( pOL );
}

const HMNWERecvReq* HMNWERecvReqDepot::_getRecvReq( const OVERLAPPED* pOL ) const {
	recvreq_container_type::const_iterator citRecvReq, ciendRecvReq;
	const HMNWERecvReq* pNWERecvReq = NULL;

	ciendRecvReq = m_containerRecvReq.end();
	for ( citRecvReq = m_containerRecvReq.begin(); citRecvReq != ciendRecvReq; ++citRecvReq ) {
		pNWERecvReq = *citRecvReq;
		if ( &pNWERecvReq->m_ol == pOL ) {
			return pNWERecvReq;
		}
	}

	return NULL;
}

void HMNWERecvReqDepot::clearAllReq() {
	if ( !m_pTSHelper->safeEnterFunc() ) {
		assert( false );
		return;
	}
	CMemFuncPack mfpkSafeExit( m_pTSHelper, &HMTSHelper::safeExitFunc );

	_clearAll();
}





































