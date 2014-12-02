#include "stdafx.h"
#include "HMPendingDataDepot.h"
#include <assert.h>
HMNWP_NAMESPACE_BEGIN
//
HMPendingData::HMPendingData( const unsigned char* pBufPending, unsigned int uLenBufPending )
: m_pRawBuf( NULL )
, m_uLenRawBuf( 0 )
, m_uIndexPendingStart( 0 )
, m_uId( _allocalId() ){
	if ( uLenBufPending == 0 || !pBufPending ) {
		assert( false );
		return;
	}
	m_pRawBuf = new unsigned char[ uLenBufPending ];
	memcpy( m_pRawBuf, pBufPending, uLenBufPending );
	m_uLenRawBuf = uLenBufPending;
}

HMPendingData::~HMPendingData() {
	if ( m_pRawBuf ) {
		delete []m_pRawBuf;
		m_pRawBuf = NULL;
	}
}

unsigned int HMPendingData::_allocalId() const {
	static unsigned int s_idBase = 0;
	return ++s_idBase;
}

HMPendingDataDepot::HMPendingDataDepot() {

}

HMPendingDataDepot::~HMPendingDataDepot() {
	_clearAllPendData();
}

bool HMPendingDataDepot::pushback( const unsigned char* pBufPending, unsigned int uLenBufPending ) {
	if ( !pBufPending || ( uLenBufPending == 0 ) ) {
		assert( false );
		return false;
	}
	HMPendingData* pPendDataNew = NULL;

	pPendDataNew = new HMPendingData( pBufPending, uLenBufPending );
	m_containerPendingData.push_back( pPendDataNew );
	return true;
}

void HMPendingDataDepot::_clearAllPendData() {
	for ( auto pPendData : m_containerPendingData ) {
		if ( pPendData )
			delete pPendData;
		pPendData = NULL;
	}
}

//bool HMPendingDataDepot::getPendingData( unsigned char** ppBufPending, unsigned int& uLenBufPending ) {
//	if ( !ppBufPending ) {
//		assert( false );
//		return false;
//	}
//	pendingdata_container_type::iterator itPData, iendPData;
//	unsigned int uLenAll;
//	HMPendingData* pPendingData = NULL;
//	unsigned char* pBufAllPending = NULL;
//	unsigned char* pBufCopyStart = NULL;
//
//	// calc uLenAll;
//	uLenAll = 0;
//	iendPData = m_containerPendingData.end();
//	for ( itPData = m_containerPendingData.begin(); itPData != iendPData; ++itPData ) {
//		pPendingData = *itPData;
//		if ( !pPendingData ) {
//			assert( false );
//			continue;
//		}
//		uLenAll += pPendingData->m_uLenRawBuf;
//	}
//	//
//	pBufAllPending = new unsigned char[ uLenAll ];
//	pBufCopyStart = pBufAllPending;
//	iendPData = m_containerPendingData.end();
//	for ( itPData = m_containerPendingData.begin(); itPData != iendPData; ++itPData ) {
//		pPendingData = *itPData;
//		if ( !pPendingData || !pPendingData->m_pRawBuf ) {
//			continue;
//		}
//		memcpy( pBufCopyStart, pPendingData->m_pRawBuf, pPendingData->m_uLenRawBuf );
//		pBufCopyStart += pPendingData->m_uLenRawBuf;
//	}
//	assert( pBufCopyStart == ( pBufAllPending + uLenAll ) );
//	//
//	*ppBufPending = pBufAllPending;
//	uLenBufPending = uLenAll;
//	return true;
//}
//
//unsigned int HMPendingDataDepot::getPendingDataLen() {
//	pendingdata_container_type::iterator itPData, iendPData;
//	unsigned int uLenAll;
//	HMPendingData* pPendingData = NULL;
//
//	uLenAll = 0;
//	iendPData = m_containerPendingData.end();
//	for ( itPData = m_containerPendingData.begin(); itPData != iendPData; ++itPData ) {
//		pPendingData = *itPData; 
//		if ( !pPendingData ) {
//			assert( false );
//			continue;
//		}
//		assert( pPendingData->m_uLenRawBuf > pPendingData->m_uIndexPendingStart );
//		uLenAll += ( pPendingData->m_uLenRawBuf - pPendingData->m_uIndexPendingStart );
//	}
//
//	return uLenAll;
//}

const HMPendingData* HMPendingDataDepot::get1stPendingData() const {
	if ( m_containerPendingData.size() == 0 )
		return NULL;
	return *( m_containerPendingData.begin() );
}

HMPendingData* HMPendingDataDepot::get1stPendingData() {
	if ( m_containerPendingData.size() == 0 )
		return NULL;
	return *( m_containerPendingData.begin() );
}

void HMPendingDataDepot::del1stPendingData() {
	if ( m_containerPendingData.size() == 0 )
		return;
	HMPendingData* pPendData = NULL;

	pPendData = *( m_containerPendingData.begin() );
	m_containerPendingData.pop_front();
	if ( pPendData ) {
		delete pPendData;
		pPendData = NULL;
	}
}

unsigned int HMPendingDataDepot::getPendDataCount() const {
	return m_containerPendingData.size();
}

const HMPendingData* HMPendingDataDepot::getLastPendingData() const {
	if ( m_containerPendingData.size() == 0 )
		return NULL;
	return *( m_containerPendingData.rbegin() );
}

HMPendingData* HMPendingDataDepot::getLastPendingData() {
	if ( m_containerPendingData.size() == 0 )
		return NULL;
	return *( m_containerPendingData.rbegin() );
}

HMNWP_NAMESPACE_END
