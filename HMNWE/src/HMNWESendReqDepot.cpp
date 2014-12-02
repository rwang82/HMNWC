#include "stdafx.h"
#include "HMNWESendReqDepot.h"
#include "MemFuncPack.h"

HMNWESendReq::HMNWESendReq( const unsigned char* pBufNWData, unsigned int uLenBuf )
: m_pBufNWData( NULL )
, m_uLenBuf( 0 ) {
	//
	m_pBufNWData = new unsigned char[ uLenBuf ];
	memcpy_s( m_pBufNWData, uLenBuf, pBufNWData, uLenBuf );
	m_uLenBuf = uLenBuf;
	//
	memset( &m_ol, 0, sizeof( m_ol ) );
}

HMNWESendReq::~HMNWESendReq() {
	if ( m_pBufNWData ) {
		delete[] m_pBufNWData;
		m_pBufNWData = NULL;
	}
	m_uLenBuf = 0;
}

HMNWESendReqDepot::HMNWESendReqDepot() {

}

HMNWESendReqDepot::~HMNWESendReqDepot() {
	m_TSHelper.cancelAllAccess();
	::Sleep( 1 );
	_clearAll();
}

HMNWESendReq* HMNWESendReqDepot::createReq( const unsigned char* pBufNWData, unsigned int uLenBuf ) {
	if ( !m_TSHelper.safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( &m_TSHelper, &HMTSHelper::safeExitFunc );

	HMNWESendReq* pSendReq = NULL;
	pSendReq = new HMNWESendReq( pBufNWData, uLenBuf );
	m_containerSendReq.push_back( pSendReq );
	return pSendReq;
}

void HMNWESendReqDepot::removeReq( const OVERLAPPED* pOL ) {
	if ( !m_TSHelper.safeEnterFunc() ) {
		return;
	}
	CMemFuncPack mfpkSafeExit( &m_TSHelper, &HMTSHelper::safeExitFunc );
	sendreq_container_type::iterator itReq, iendReq;
	HMNWESendReq* pSendReq = NULL;

	iendReq = m_containerSendReq.end();
	for ( itReq = m_containerSendReq.begin(); itReq != iendReq; ++itReq ) {
		pSendReq = *itReq;
		if ( pSendReq 
		&& ( &( pSendReq->m_ol ) == pOL ) ) {
			delete pSendReq;
			pSendReq = NULL;
			m_containerSendReq.erase( itReq );
			return;
		}
	}
}

HMNWESendReq* HMNWESendReqDepot::getReq( const OVERLAPPED* pOL ) {
	if ( !m_TSHelper.safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( &m_TSHelper, &HMTSHelper::safeExitFunc );

	return _getReq( pOL );
}


bool HMNWESendReqDepot::hasReq( const OVERLAPPED* pOL ) const{
	if ( !m_TSHelper.safeEnterFunc() ) {
		return NULL;
	}
	CMemFuncPack mfpkSafeExit( &m_TSHelper, &HMTSHelper::safeExitFunc );

	return ( _getReq( pOL ) != NULL );
}

HMNWESendReq* HMNWESendReqDepot::_getReq( const OVERLAPPED* pOL ) const {
	sendreq_container_type::const_iterator citReq, ciendReq;
	HMNWESendReq* pSendReq = NULL;

	ciendReq = m_containerSendReq.end();
	for ( citReq = m_containerSendReq.begin(); citReq != ciendReq; ++citReq ) {
		pSendReq = *citReq;
		if ( pSendReq
			&& ( &( pSendReq->m_ol ) == pOL ) ) {
			return pSendReq;
		}
	}

	return NULL;
}

void HMNWESendReqDepot::_clearAll() {
	sendreq_container_type::iterator itReq, iendReq;
	HMNWESendReq* pSendReq = NULL;

	iendReq = m_containerSendReq.end();
	for ( itReq = m_containerSendReq.begin(); itReq != iendReq; ++itReq ) {
		pSendReq = *itReq;
		if ( pSendReq ) {
			delete pSendReq;
			pSendReq = NULL;
		}
	}
	m_containerSendReq.clear();
}