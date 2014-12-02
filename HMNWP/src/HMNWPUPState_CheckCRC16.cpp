#include "stdafx.h"
#include "HMNWPUPState_CheckCRC16.h"
#include "HMNWPPackage.h"
#include "HMNWPUnPackImpl.h"
#include <assert.h>
HMNWP_NAMESPACE_BEGIN
//
HMNWPUPState_CheckCRC16::HMNWPUPState_CheckCRC16( HMNWPUnPackImpl* pUPImpl )
: HMNWPUPStateBase( pUPImpl )
, m_uLenCRC16Ready( 0 ){
	reset();
}

HMNWPUPState_CheckCRC16::~HMNWPUPState_CheckCRC16() {

}

//void HMNWPUPState_CheckCRC16::parseRawData( const unsigned char* pRawBuf, unsigned int uLenRawBuf, ENUMRAWBUFTYPE eRawBufType, unsigned int& uLenEat ) {
//	if ( !pRawBuf || uLenRawBuf == 0 || m_uLenCRC16Ready >= HMNWP_LEN_CRC16 ) {
//		assert( false );
//		return;
//	}
//	unsigned int uNeedCopy;
//	unsigned __int16 uCRC16;
//	bool bCRCCheckOK = false;
//
//	//
//	uNeedCopy = min( uLenRawBuf, HMNWP_LEN_CRC16 - m_uLenCRC16Ready );
//	memcpy( m_bufCRC16 + m_uLenCRC16Ready, pRawBuf, uNeedCopy );
//	m_uLenCRC16Ready += uNeedCopy;
//	//
//	uLenEat = uNeedCopy;
//
//	if ( m_uLenCRC16Ready == HMNWP_LEN_CRC16 ) {
//		memcpy( &uCRC16, m_bufCRC16, HMNWP_LEN_CRC16 );
//		bCRCCheckOK = m_pUPImpl->_checkCRC16( uCRC16 );
//		reset();
//	}
//}

void HMNWPUPState_CheckCRC16::reset() {
	memset( m_bufCRC16, 0, sizeof( m_bufCRC16 ) );
	m_uLenCRC16Ready = 0;
}


ENUMRAWBUFTYPE HMNWPUPState_CheckCRC16::analyseRawBufType( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) const {
	if ( !pRawBuf || uLenRawBuf == 0 ) {
		return ERAWBUF_TYPE_UNKNOWN;
	}

	return ( m_uLenCRC16Ready + uLenRawBuf < HMNWP_LEN_CRC16 )
		? ERAWBUF_TYPE_BODYIN_ONLY
		: ERAWBUF_TYPE_TAILIN_ONLY;
}

void HMNWPUPState_CheckCRC16::_parseRawData_BODYIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat ) {
	assert( m_uLenCRC16Ready + uLenRawBuf < HMNWP_LEN_CRC16 );
	unsigned int uNeedCopy;

	uNeedCopy = min( HMNWP_LEN_CRC16 - m_uLenCRC16Ready, uLenRawBuf );
	memcpy( &m_bufCRC16[ m_uLenCRC16Ready ], pRawBuf, uNeedCopy );
	uLenEat = uNeedCopy;
	m_uLenCRC16Ready += uNeedCopy;
	assert( m_uLenCRC16Ready < HMNWP_LEN_CRC16 );
}

void HMNWPUPState_CheckCRC16::_parseRawData_TAILIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat ) {
	assert( m_uLenCRC16Ready + uLenRawBuf >= HMNWP_LEN_CRC16 );
	unsigned int uNeedCopy;
	bool bMatchCRC16;

	uNeedCopy = min( HMNWP_LEN_CRC16 - m_uLenCRC16Ready, uLenRawBuf );
	memcpy( &m_bufCRC16[ m_uLenCRC16Ready ], pRawBuf, uNeedCopy );
	uLenEat = uNeedCopy;
	//
	bMatchCRC16 = m_pUPImpl->_checkCRC16( *( ( unsigned short* )m_bufCRC16 ) );
	//
//	bContinue = false;
	//
	reset();
}

HMNWP_NAMESPACE_END
