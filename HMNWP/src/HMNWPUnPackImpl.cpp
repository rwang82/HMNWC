#include "stdafx.h"
#include "HMNWPUnPackImpl.h"
#include "HMNWPPackage.h"
#include "HMNWPUPState_FindHeader.h"
#include "HMNWPUPState_SavePayload.h"
#include "HMNWPUPState_CheckCRC16.h"
#include "HMCRC16.h"
#include "HMPendingDataDepot.h"
#include "HMNWPPackageDepot.h"
#include "FuncPack.h"
#include "MemFuncPack.h"
#include "tchar.h"
#include <assert.h>
HMNWP_NAMESPACE_BEGIN
//
#define HMNWP_UPIMPL_FLAG_NONE (0x00000000)
#define HMNWP_UPIMPL_FLAG_RESET (0x00000001)
#define ENWPUP_STATE_HEADER_READY (0x00000002)
#define ENWPUP_STATE_PAYLOAD_READY (0x00000004)
#define ENWPUP_STATE_WHOLE_PACKAGE_READY (0x00000008)
#define ENWPUP_STATE_PACKAGE_INCOMPLETE (0x00000010)
//
HMRawBufData::HMRawBufData( const unsigned char* pRawBuf, unsigned int uLenRawData )
: m_pRawBuf( new unsigned char[ uLenRawData ] )
, m_uLenRawBuf( uLenRawData )
, m_uIndexCheckStart( 0 ) {
	memcpy( m_pRawBuf, pRawBuf, uLenRawData );
}

HMRawBufData::~HMRawBufData() {
	if ( m_pRawBuf ) {
		delete []m_pRawBuf;
		m_pRawBuf = NULL;
	}
}
//
HMNWPUnPackImpl::HMNWPUnPackImpl()
: m_pDepotPendingData( new HMPendingDataDepot() )
, m_pDepotPackage( new HMNWPPackageDepot() )
, m_pNWPHeader( new HMNWPHeader() )
, m_uFlag( HMNWP_UPIMPL_FLAG_RESET )
, m_pBufPayload( NULL )
, m_uLenBufPayload( 0 )
, m_uLenBufPayloadReady( 0 )
, m_pNWPUPStateFindHeader( new HMNWPUPState_FindHeader( this ) )
, m_pNWPUPStateSavePayload( new HMNWPUPState_SavePayload( this ) )
, m_pNWPUPStateCheckCRC16( new HMNWPUPState_CheckCRC16( this ) )
{
	m_eventPackageReady.bind( this, &HMNWPUnPackImpl::_onEvtPackageReady );
	m_pDepotPackage->m_eventRawBufReady.bind( this, &HMNWPUnPackImpl::_onEvtRawBufReady );
}

HMNWPUnPackImpl::~HMNWPUnPackImpl() {
	if ( m_pBufPayload ) {
		delete[] m_pBufPayload;
		m_pBufPayload = NULL;
	}
	if ( m_pNWPUPStateCheckCRC16 ) {
		delete m_pNWPUPStateCheckCRC16;
		m_pNWPUPStateCheckCRC16 = NULL;
	}
	if ( m_pNWPUPStateSavePayload ) {
		delete m_pNWPUPStateSavePayload;
		m_pNWPUPStateSavePayload = NULL;
	}
	if ( m_pNWPUPStateFindHeader ) {
		delete m_pNWPUPStateFindHeader;
		m_pNWPUPStateFindHeader = NULL;
	}
	if ( m_pNWPHeader ) {
		delete m_pNWPHeader;
		m_pNWPHeader = NULL;
	}
	if ( m_pDepotPendingData ) {
		delete m_pDepotPendingData;
		m_pDepotPendingData = NULL;
	}
	if ( m_pDepotPackage ) {
		delete m_pDepotPackage;
		m_pDepotPackage = NULL;
	}
}

void HMNWPUnPackImpl::onRecvRawData( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
	HMPendingData* pPendData = NULL;

	//
	if ( !_checkValidRawBuf( pRawBuf, uLenRawBuf ) )
		return;
	//
	if ( !m_pDepotPendingData->pushback( pRawBuf, uLenRawBuf ) )
		return;
	pPendData = m_pDepotPendingData->getLastPendingData();
	assert( pPendData );
	//
	_parseRawBufData( pPendData->m_pRawBuf, uLenRawBuf );
}

bool HMNWPUnPackImpl::_checkValidRawBuf( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
	ENUMRAWBUFTYPE eRawBufType;
	
	if ( !BIT_HITTEST( m_uFlag, ENWPUP_STATE_HEADER_READY ) ) {
		eRawBufType = m_pNWPUPStateFindHeader->analyseRawBufType( pRawBuf, uLenRawBuf );
		if ( eRawBufType == ERAWBUF_TYPE_NOTIN )
			return false;
	}

	return true;
}

void HMNWPUnPackImpl::_parseRawBufData( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
	HMNWPUPStateBase* pNWPUPStateCur = NULL;
	const unsigned char* pPosBufRawData = NULL;
	unsigned int uLenEatTmp;
	unsigned int uLenPending;
	ENUMRAWBUFTYPE eRawBufType;
	bool bContinue;

	//
	bContinue = true;
	uLenPending = uLenRawBuf;
	pPosBufRawData = pRawBuf;
	while ( uLenPending != 0 ) {
		pNWPUPStateCur = _getCurNWPUPState();
		assert( pNWPUPStateCur );
		uLenEatTmp = 0;
		eRawBufType = pNWPUPStateCur->analyseRawBufType( pPosBufRawData, uLenPending );
		pNWPUPStateCur->parseRawData( pPosBufRawData, uLenPending, eRawBufType, uLenEatTmp );
		//
		uLenPending -= uLenEatTmp;
		pPosBufRawData += uLenEatTmp;
		if ( pPosBufRawData > pRawBuf + uLenRawBuf ) {
			assert( false );
			return;
		}
		//
		if ( BIT_HITTEST( m_uFlag, ENWPUP_STATE_WHOLE_PACKAGE_READY ) ) {
			m_eventPackageReady.invoke( m_pNWPHeader, m_pBufPayload );
			_moveCheckStartPosTo( pPosBufRawData );
			_reset();
		} else if ( BIT_HITTEST( m_uFlag, ENWPUP_STATE_PACKAGE_INCOMPLETE ) ) {
			_moveCheckStartPosTo( pPosBufRawData );
			_reset();
		}
	}
}

void HMNWPUnPackImpl::_onEvtPackageReady( const HMNWPHeader* pNWPHeader, const unsigned char* pBufPayload ) {
	m_pDepotPackage->pushbackPackage( pNWPHeader, pBufPayload );
}

void HMNWPUnPackImpl::_onEvtRawBufReady( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
	m_eventRawBufReady.invoke( pRawBuf, uLenRawBuf );
}

void HMNWPUnPackImpl::_moveCheckStartPosTo( const unsigned char* pPosCheckStart ) {
	HMPendingData* pPendData = NULL;

	while ( pPendData = m_pDepotPendingData->get1stPendingData() ) {
		if ( ( pPosCheckStart >= pPendData->m_pRawBuf ) && ( pPosCheckStart < pPendData->m_pRawBuf + pPendData->m_uLenRawBuf ) ) {
			pPendData->m_uIndexPendingStart = ( pPosCheckStart - pPendData->m_pRawBuf );
			break;
		}
		m_pDepotPendingData->del1stPendingData();
	}
}

//void HMNWPUnPackImpl::_moveCheckStartPos1Step() {
//	HMPendingData* pPendData = NULL;
//
//	pPendData = m_pDepotPendingData->get1stPendingData();
//	if ( !pPendData )
//		return;
//	if ( pPendData->m_uIndexPendingStart + 1 >= pPendData->m_uLenRawBuf ) {
//		m_pDepotPendingData->del1stPendingData();
//		return;
//	}
//	pPendData->m_uIndexPendingStart ++;
//	
//}

HMNWPUPStateBase* HMNWPUnPackImpl::_getCurNWPUPState() {
	if ( !BIT_HITTEST( m_uFlag, ENWPUP_STATE_HEADER_READY ) ) {
		assert( BIT_HITTEST( m_uFlag, HMNWP_UPIMPL_FLAG_RESET ) );
		return m_pNWPUPStateFindHeader;
	} else if ( !BIT_HITTEST( m_uFlag, ENWPUP_STATE_PAYLOAD_READY ) ) {
		return m_pNWPUPStateSavePayload;
	} else if ( !BIT_HITTEST( m_uFlag, ENWPUP_STATE_WHOLE_PACKAGE_READY ) ) {
		return m_pNWPUPStateCheckCRC16;
	} else {
		m_uFlag = HMNWP_UPIMPL_FLAG_RESET;
		return m_pNWPUPStateFindHeader;
	}

	assert( false );
	return NULL;
}

void HMNWPUnPackImpl::_fillNWPHeader( const HMNWPHeader* pNWPHeader ) {
	memcpy( m_pNWPHeader, pNWPHeader, sizeof( HMNWPHeader ) );
	m_uFlag |= ENWPUP_STATE_HEADER_READY;
	//
	_clearBufPayload();
	//
	m_pBufPayload = new unsigned char[ m_pNWPHeader->m_i16PayloadLen ];
	m_uLenBufPayload = m_pNWPHeader->m_i16PayloadLen;
	m_uLenBufPayloadReady = 0;
}

void HMNWPUnPackImpl::_clearNWPHeader() {
	m_pNWPHeader->reset();
	m_uFlag &= ~ENWPUP_STATE_HEADER_READY;
	//
	if ( m_pBufPayload )
		delete[]m_pBufPayload;
	m_pBufPayload = NULL;
	m_uLenBufPayload = 0;
	m_uLenBufPayloadReady = 0;
}

bool HMNWPUnPackImpl::_fillBufPayload( const unsigned char* pBufPayload, unsigned int uLenBuf ) {
	if ( !m_pNWPHeader || !pBufPayload || ( m_uLenBufPayloadReady + uLenBuf > m_uLenBufPayload ) ) {
		assert( false );
		return false;
	}
	memcpy( &m_pBufPayload[ m_uLenBufPayloadReady ], pBufPayload, uLenBuf );
	m_uLenBufPayloadReady += uLenBuf;
	
	if ( m_uLenBufPayloadReady == m_pNWPHeader->m_i16PayloadLen ) {
		m_uFlag |= ENWPUP_STATE_PAYLOAD_READY;
	}

	return true;
}

void HMNWPUnPackImpl::_clearBufPayload() {
	if ( m_pBufPayload ) {
		delete []m_pBufPayload;
		m_pBufPayload = NULL;
	}
	m_uLenBufPayload = 0;
	m_uLenBufPayloadReady = 0;
}

void HMNWPUnPackImpl::_reset() {
	_clearNWPHeader();
	_clearBufPayload();
	//
	m_uFlag &= ~ENWPUP_STATE_HEADER_READY;
	m_uFlag &= ~ENWPUP_STATE_PAYLOAD_READY;
	m_uFlag &= ~ENWPUP_STATE_WHOLE_PACKAGE_READY;
	m_uFlag &= ~ENWPUP_STATE_PACKAGE_INCOMPLETE;
	m_uFlag |= HMNWP_UPIMPL_FLAG_RESET;
}

bool HMNWPUnPackImpl::_checkCRC16( unsigned __int16 uCRC16 ) {
	unsigned short uCRC16Calc;
	const unsigned char* pBufHeader = NULL;
	unsigned char* pBufErrPackage = NULL;

	uCRC16Calc = GetCRC16( m_pBufPayload, m_uLenBufPayload );

	if ( uCRC16 != uCRC16Calc ) {
	    int a = 0;
	}

	//
	m_uFlag |= ( ( uCRC16Calc == uCRC16 ) ? ENWPUP_STATE_WHOLE_PACKAGE_READY : ENWPUP_STATE_PACKAGE_INCOMPLETE );
	return ( uCRC16Calc == uCRC16 );
}



HMNWP_NAMESPACE_END
