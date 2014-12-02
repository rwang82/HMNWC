#include "stdafx.h"
#include "HMNWPUPState_SavePayload.h"
#include "HMNWPUnPackImpl.h"
#include "HMNWPPackage.h"
HMNWP_NAMESPACE_BEGIN
//
HMNWPUPState_SavePayload::HMNWPUPState_SavePayload( HMNWPUnPackImpl* pUPImpl )
: HMNWPUPStateBase( pUPImpl ) {

}

HMNWPUPState_SavePayload::~HMNWPUPState_SavePayload() {

}

void HMNWPUPState_SavePayload::reset() {
	// need do nothing.
}

ENUMRAWBUFTYPE HMNWPUPState_SavePayload::analyseRawBufType( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) const {
	if ( !pRawBuf || uLenRawBuf == 0 ) {
		return ERAWBUF_TYPE_UNKNOWN;
	}

	if ( m_pUPImpl->m_pNWPHeader->m_i16PayloadLen - m_pUPImpl->m_uLenBufPayloadReady + HMNWP_LEN_CRC16 > uLenRawBuf )
		return ERAWBUF_TYPE_BODYIN_ONLY;

	return ERAWBUF_TYPE_TAILIN_ONLY;
}

void HMNWPUPState_SavePayload::_parseRawData_BODYIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat ) {
	if ( !pRawBuf || uLenRawBuf == 0 ) {
		return;
	}
	unsigned int uNeedCopy;
	assert( m_pUPImpl->m_pNWPHeader->m_i16PayloadLen == m_pUPImpl->m_uLenBufPayload );
	uNeedCopy = min( m_pUPImpl->m_pNWPHeader->m_i16PayloadLen - m_pUPImpl->m_uLenBufPayloadReady, uLenRawBuf );
	m_pUPImpl->_fillBufPayload( pRawBuf, uNeedCopy );
	//
	uLenEat = uNeedCopy;
}

void HMNWPUPState_SavePayload::_parseRawData_TAILIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat ) {
	if ( !pRawBuf || uLenRawBuf == 0 ) {
		return;
	}
	unsigned int uNeedCopy;
	assert( m_pUPImpl->m_pNWPHeader->m_i16PayloadLen == m_pUPImpl->m_uLenBufPayload );
	uNeedCopy = min( m_pUPImpl->m_pNWPHeader->m_i16PayloadLen - m_pUPImpl->m_uLenBufPayloadReady, uLenRawBuf );
	m_pUPImpl->_fillBufPayload( pRawBuf, uNeedCopy );
	//
	uLenEat = uNeedCopy;
}


HMNWP_NAMESPACE_END
