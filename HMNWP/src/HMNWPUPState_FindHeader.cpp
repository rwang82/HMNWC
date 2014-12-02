#include "stdafx.h"
#include "HMNWPUPState_FindHeader.h"
#include "HMNWPPackage.h"
#include "HMNWPUnPackImpl.h"
#include <assert.h>
HMNWP_NAMESPACE_BEGIN
//
#define HMNWP_UPSTATEFH_FLAG_NONE (0x00000000)
//
HMNWPUPState_FindHeader::HMNWPUPState_FindHeader( HMNWPUnPackImpl* pUPImpl )
: HMNWPUPStateBase( pUPImpl )
, m_uFlag( HMNWP_UPSTATEFH_FLAG_NONE )
, m_pNWPHeaderPending( new HMNWPHeader() )
, m_uLenNWPHeaderBufPending( 0 ) {
}

HMNWPUPState_FindHeader::~HMNWPUPState_FindHeader() {
	if ( m_pNWPHeaderPending ) {
		delete m_pNWPHeaderPending;
		m_pNWPHeaderPending = NULL;
	}
}

void HMNWPUPState_FindHeader::_parseRawData_ALLIN( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat ) {
	assert( m_uLenNWPHeaderBufPending == 0 );
	const unsigned char* pPosHeadStart = NULL;
	const HMNWPHeader* pNWPHeader = NULL;

	pPosHeadStart = _findHeadStartPos( pRawBuf, uLenRawBuf );
	assert( pPosHeadStart );
	pNWPHeader = ( const HMNWPHeader* )pPosHeadStart;
	assert( pPosHeadStart + sizeof( HMNWPHeader )+pNWPHeader->m_i16PayloadLen + HMNWP_LEN_CRC16 <= pRawBuf + uLenRawBuf );
	//
	_fillNWPHeader( pPosHeadStart, sizeof( HMNWPHeader ) );
	//
	uLenEat = ( pPosHeadStart - pRawBuf ) + sizeof( HMNWPHeader );
}

void HMNWPUPState_FindHeader::_parseRawData_TAILIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat ) {
	assert( m_uLenNWPHeaderBufPending > 0 );
	const unsigned char* pPosCopyStart = NULL;
	int nNeedCopy;

	nNeedCopy = min( sizeof( HMNWPHeader )-m_uLenNWPHeaderBufPending, uLenRawBuf );
	pPosCopyStart = pRawBuf;

	// 
	_fillNWPHeader( pPosCopyStart, nNeedCopy );
	//
	uLenEat = pPosCopyStart + nNeedCopy - pRawBuf;
}

void HMNWPUPState_FindHeader::_parseRawData_HEADIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat ) {
	const unsigned char* pPosHeadStart = NULL;
	const unsigned char* pPosCopyStart = NULL;
	int nNeedCopy;

	// find pPosCopyStart and nNeedCopy
	if ( m_uLenNWPHeaderBufPending == 0 ) {
		pPosHeadStart = _findHeadStartPos( pRawBuf, uLenRawBuf );
		if ( !pPosHeadStart ) {
			assert( false );
			uLenEat = uLenRawBuf;
			return;
		}
		nNeedCopy = min( pRawBuf + uLenRawBuf - pPosHeadStart, sizeof( HMNWPHeader ) );
		pPosCopyStart = pPosHeadStart;
	} else {
		
		nNeedCopy = min( sizeof( HMNWPHeader )-m_uLenNWPHeaderBufPending, uLenRawBuf );
		pPosCopyStart = pRawBuf;
	}
	//
	_fillNWPHeader( pPosCopyStart, nNeedCopy );
	//
	uLenEat = pPosCopyStart + nNeedCopy - pRawBuf;
}

void HMNWPUPState_FindHeader::_fillNWPHeader( const unsigned char* pBuf, unsigned int uLenBuf ) {
	assert( m_uLenNWPHeaderBufPending + uLenBuf <= sizeof( HMNWPHeader ) );
	// 
	memcpy( ( unsigned char* )m_pNWPHeaderPending + m_uLenNWPHeaderBufPending, pBuf, uLenBuf );
	m_uLenNWPHeaderBufPending += uLenBuf;
	if ( m_uLenNWPHeaderBufPending == sizeof( HMNWPHeader ) ) {
		m_pUPImpl->_fillNWPHeader( m_pNWPHeaderPending );
		reset();
	}
}

//void HMNWPUPState_FindHeader::parseRawData( const unsigned char* pRawBuf, unsigned int uLenRawBuf, ENUMRAWBUFTYPE eRawBufType, unsigned int& uLenEat ) {
//	if ( !pRawBuf || uLenRawBuf == 0 ) {
//		assert( false );
//		uLenEat = 0;
//		return;
//	}
//	unsigned int uLenNeedCopy;
//	unsigned int uSizeNWPHeader;
//	unsigned int uLenRawBufPending = 0;
//	const unsigned char* pRawBufPending = NULL;
//	unsigned char* pBufNWPHeaderPending = NULL;
//
//	uSizeNWPHeader = sizeof( HMNWPHeader );
//	pRawBufPending = pRawBuf;
//	uLenRawBufPending = uLenRawBuf;
//	pBufNWPHeaderPending = (unsigned char*)m_pNWPHeaderPending;
//	while ( uLenRawBufPending > 0 ) {
//		uLenNeedCopy = min( uSizeNWPHeader - m_uLenNWPHeaderBufPending, uLenRawBufPending );
//		memcpy( pBufNWPHeaderPending + m_uLenNWPHeaderBufPending, pRawBufPending, uLenNeedCopy );
//		m_uLenNWPHeaderBufPending += uLenNeedCopy;
//		uLenRawBufPending -= uLenNeedCopy;
//		//
//		if ( m_pNWPHeaderPending->m_ucBeg1 == HMNWP_PACKAGE_BEG1
//			&& m_pNWPHeaderPending->m_ucBeg2 == HMNWP_PACKAGE_BEG2
//			&& m_pNWPHeaderPending->m_ucVer == HMNWP_PACKAGE_VER ) {
//			//
//			uLenEat = uLenRawBuf - uLenRawBufPending;
//			//
//			if ( m_uLenNWPHeaderBufPending == uSizeNWPHeader ) {
//				m_pUPImpl->_fillNWPHeader( m_pNWPHeaderPending );
//				reset();
//			}
//			return;
//		}
//
//		++pRawBufPending;
//		uLenRawBufPending = ( pRawBuf + uLenRawBuf - pRawBufPending );
//		reset();
//	}
//	
//	//
//	uLenEat = uLenRawBuf;
//}

void HMNWPUPState_FindHeader::reset() {
	if ( !m_pNWPHeaderPending ) {
		assert( false );
		return;
	}
	m_pNWPHeaderPending->reset();
	m_uLenNWPHeaderBufPending = 0;
	m_uFlag = HMNWP_UPSTATEFH_FLAG_NONE;
}

ENUMRAWBUFTYPE HMNWPUPState_FindHeader::analyseRawBufType( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) const {
	if ( !pRawBuf || ( uLenRawBuf == 0 ) )
		return ERAWBUF_TYPE_UNKNOWN;
	const unsigned char* pPosHeadStart = NULL;
	int nLenAfterHeadStart;
	const HMNWPHeader* pNWPHeader = NULL;
	unsigned char szBufNWPHeaderTmp[ sizeof( HMNWPHeader ) ];

	// check if 
	if ( m_uLenNWPHeaderBufPending == 0 ) {
		pPosHeadStart = _findHeadStartPos( pRawBuf, uLenRawBuf );
		if ( !pPosHeadStart )
			return ERAWBUF_TYPE_NOTIN; // no package head.
		nLenAfterHeadStart = pRawBuf + uLenRawBuf - pPosHeadStart;
		if ( nLenAfterHeadStart < sizeof( HMNWPHeader )+HMNWP_LEN_CRC16 ) {
			return ERAWBUF_TYPE_HEADIN_ONLY; // can not contain head + crc16.
		}
		pNWPHeader = ( const HMNWPHeader* )pPosHeadStart;
		if ( nLenAfterHeadStart < ( int )sizeof( HMNWPHeader )+pNWPHeader->m_i16PayloadLen + HMNWP_LEN_CRC16 ) {
			return ERAWBUF_TYPE_HEADIN_ONLY; // can not container whole package.
		}
		return ERAWBUF_TYPE_ALLIN; // can container whole package.
	} else {
		if ( m_uLenNWPHeaderBufPending + uLenRawBuf < sizeof( HMNWPHeader )+HMNWP_LEN_CRC16 ) {
			return ERAWBUF_TYPE_HEADIN_ONLY; // can not container head + crc16.
		}
		memcpy( szBufNWPHeaderTmp, m_pNWPHeaderPending, m_uLenNWPHeaderBufPending );
		memcpy( &szBufNWPHeaderTmp[ m_uLenNWPHeaderBufPending ], pRawBuf, sizeof( HMNWPHeader )-m_uLenNWPHeaderBufPending );
		pNWPHeader = ( const HMNWPHeader* )szBufNWPHeaderTmp;
		if ( m_uLenNWPHeaderBufPending + uLenRawBuf < sizeof( HMNWPHeader )+pNWPHeader->m_i16PayloadLen + HMNWP_LEN_CRC16 ) {
			return ERAWBUF_TYPE_HEADIN_ONLY; // can not container whole package.
		}
		return ERAWBUF_TYPE_TAILIN_ONLY; // can container whole package.
	}

	assert( false );
	return ERAWBUF_TYPE_UNKNOWN;
}

const unsigned char* HMNWPUPState_FindHeader::_findHeadStartPos( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
	const unsigned char* pPosCheckStart = NULL;
	const unsigned char* pPosHeadStart = NULL;
	int nLenNoCheck;

	nLenNoCheck = uLenRawBuf;
	pPosCheckStart = pRawBuf;
	while ( ( nLenNoCheck > 0 )
		&& ( pPosHeadStart = ( const unsigned char* )memchr( pPosCheckStart, HMNWP_PACKAGE_BEG1, nLenNoCheck ) ) ) {
		//
		if ( (pPosHeadStart - pPosCheckStart) + 1 >= nLenNoCheck ) {
			// just last char match HMNWP_PACKAGE_BEG1
			return pPosHeadStart;
		}
		//
		if ( pPosHeadStart[ 1 ] == HMNWP_PACKAGE_BEG2 ) {
			return pPosHeadStart;
		} else {
			pPosCheckStart = pPosHeadStart + 1;
			nLenNoCheck = pRawBuf + uLenRawBuf - pPosCheckStart;
			continue;
		}
		assert( false );
	}

	return NULL;
}

HMNWP_NAMESPACE_END
