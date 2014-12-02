#include "stdafx.h"
#include "HMNWPPackage.h"
#include "HMCRC16.h"
//
HMNWP_NAMESPACE_BEGIN
//
const unsigned char HMNWP_PACKAGE_BEG1 = 0xAF;
const unsigned char HMNWP_PACKAGE_BEG2 = 0xE0;
const unsigned char HMNWP_PACKAGE_VER = 0x01;
//
HMNWPHeader::HMNWPHeader()
: m_ucBeg1( HMNWP_PACKAGE_BEG1 )
, m_ucBeg2( HMNWP_PACKAGE_BEG2 )
, m_ucVer( HMNWP_PACKAGE_VER )
, m_i16BundleBufIndex( 0 )
, m_i16PackageIndex( 0 )
, m_i16PackageCount( 1 )
, m_ucBodyProtocol( 0 )
, m_i16PayloadLen( 0 ) {
	// reset();
}

HMNWPHeader::~HMNWPHeader() {

}

void HMNWPHeader::reset() {
	m_ucBeg1 = HMNWP_PACKAGE_BEG1;
	m_ucBeg2 = HMNWP_PACKAGE_BEG2;
	m_ucVer = HMNWP_PACKAGE_VER;
	m_i16BundleBufIndex = 0;
	m_i16PackageIndex = 0;
	m_i16PackageCount = 1;
	m_ucBodyProtocol = 0;
	m_i16PayloadLen = 0;
}
//////////////////////////////////////////////////////////////////////////
// m_ucFlag
#define HMNWPPACKAGE_FLAG_NONE (0x00000000)
#define HMNWPPACKAGE_FLAG_VALID (0x00000001)
HMNWPPackage::HMNWPPackage( const HMNWPHeader* header, const unsigned char* pBufPayload )
: m_pBufPackage( NULL )
, m_uLenBufData( 0 )
, m_ucFlag( HMNWPPACKAGE_FLAG_NONE ) {
	unsigned char* pPosBufData = NULL;
	__int16 i16CRC = GetCRC16( pBufPayload, header->m_i16PayloadLen );
	if ( header && pBufPayload 
		&& header->m_i16PayloadLen <= HMNWP_LEN_PAYLOAD_MAX ) {
		//
		m_uLenBufData = HMNWP_LEN_NWPHEADER + header->m_i16PayloadLen + HMNWP_LEN_CRC16;
		m_pBufPackage = new unsigned char[ m_uLenBufData ];
		pPosBufData = m_pBufPackage;
		// copy header.
		memcpy( pPosBufData, header, HMNWP_LEN_NWPHEADER );
		pPosBufData += HMNWP_LEN_NWPHEADER;
		// copy payload.
		memcpy( pPosBufData, pBufPayload, header->m_i16PayloadLen );
		pPosBufData += header->m_i16PayloadLen;
		// copy crc16.
		memcpy( pPosBufData, &i16CRC, HMNWP_LEN_CRC16 );
		//  
		m_ucFlag |= HMNWPPACKAGE_FLAG_VALID;
	}
}

HMNWPPackage::~HMNWPPackage() {
	if ( m_pBufPackage ) {
		delete[] m_pBufPackage;
		m_pBufPackage = NULL;
	}
}

bool HMNWPPackage::isPackageValid() {
	return m_ucFlag & HMNWPPACKAGE_FLAG_VALID;
}

HMNWP_NAMESPACE_END
