#include "stdafx.h"
#include "HMNWPPackageDepot.h"
#include "HMNWPPackage.h"
#include "FuncPack.h"
#include "MemFuncPack.h"
HMNWP_NAMESPACE_BEGIN

HMNWPPackageBox::HMNWPPackageBox( const HMNWPHeader* pNWPHeader, const unsigned char* pBufPayload )
: m_pHeader( NULL )
, m_pBufPayload( NULL ) {
	m_pHeader = new HMNWPHeader();
	memcpy( m_pHeader, pNWPHeader, sizeof( HMNWPHeader ) );
	m_pBufPayload = new unsigned char[ m_pHeader->m_i16PayloadLen ];
	memcpy( m_pBufPayload, pBufPayload, m_pHeader->m_i16PayloadLen );
}

HMNWPPackageBox::~HMNWPPackageBox() {
	if ( m_pBufPayload ) {
		delete[] m_pBufPayload;
		m_pBufPayload = NULL;
	}
	if ( m_pHeader ) {
		delete m_pHeader;
		m_pHeader = NULL;
	}
}

HMNWPPackageDepot::HMNWPPackageDepot() {

}

HMNWPPackageDepot::~HMNWPPackageDepot() {
	_clearAllPackage();
}

void HMNWPPackageDepot::pushbackPackage( const HMNWPHeader* pNWPHeader, const unsigned char* pBufPayload ) {
	if ( !isValidNWPHeader( pNWPHeader ) )
		return; // do nothing.
	HMNWPPackageBox* pPackageBoxLast = NULL;
	unsigned int uLenRawBuf;
	unsigned char* pBufRawBuf = NULL;

	//
	if ( m_containerPackageBox.size() != 0 ) {
		//
		pPackageBoxLast = *( m_containerPackageBox.rbegin() );
		// check m_i16PackageIndex
		if ( ( pNWPHeader->m_i16PackageIndex != m_containerPackageBox.size() )
			|| ( pPackageBoxLast->m_pHeader->m_ucVer != pNWPHeader->m_ucVer )
			|| ( pPackageBoxLast->m_pHeader->m_ucBodyProtocol != pNWPHeader->m_ucBodyProtocol )
			|| ( pPackageBoxLast->m_pHeader->m_i16PackageCount != pNWPHeader->m_i16PackageCount )
			|| ( pPackageBoxLast->m_pHeader->m_i16BundleBufIndex != pNWPHeader->m_i16BundleBufIndex ) ) {
			_clearAllPackage();
			if ( pNWPHeader->m_i16BundleBufIndex != 0 )
				return; // do nothing.
		}
	}
	m_containerPackageBox.push_back( new HMNWPPackageBox( pNWPHeader, pBufPayload ) );
	//
	if ( _isRawBufReady() ) {
		CMemFuncPack mfpkClearAllPackage( this, &HMNWPPackageDepot::_clearAllPackage );
		uLenRawBuf = _getRawBufTotalLen();
		pBufRawBuf = new unsigned char[ uLenRawBuf ];
		CFuncPack fpkDelBuf( ::gfnDelBuf<unsigned char>, pBufRawBuf );
		if ( !_fillRawBufTotal( pBufRawBuf, uLenRawBuf ) ) {
			assert( false );
			return;
		}
		m_eventRawBufReady.invoke( pBufRawBuf, uLenRawBuf );
	}
}

bool HMNWPPackageDepot::_fillRawBufTotal( unsigned char* pRawBuf, unsigned int uLenRawBuf ) const {
	if ( !pRawBuf )
		return false;
	if ( uLenRawBuf == 0 )
		return true;
	unsigned int uNeedCopy;
	unsigned int uCopied = 0;
	unsigned char* pPosCopyStart = NULL;

	pPosCopyStart = pRawBuf;
	for ( auto pPackageBox : m_containerPackageBox ) {
		uNeedCopy = pPackageBox->m_pHeader->m_i16PayloadLen;
		if ( uCopied + uNeedCopy > uLenRawBuf ) {
			assert( false );
			return false;
		}
		//
		memcpy( pPosCopyStart, pPackageBox->m_pBufPayload, uNeedCopy );
		pPosCopyStart += uNeedCopy;
		uCopied += uNeedCopy;
	}
	assert( uCopied == uLenRawBuf );
	return true;
}

bool HMNWPPackageDepot::_isRawBufReady() const{
	if ( m_containerPackageBox.size() == 0 )
		return false;
	HMNWPPackageBox* pPackageBoxLast = NULL;

	pPackageBoxLast = *(m_containerPackageBox.rbegin());
	return ( pPackageBoxLast->m_pHeader->m_i16PackageIndex + 1 == pPackageBoxLast->m_pHeader->m_i16PackageCount );
}

unsigned int HMNWPPackageDepot::_getRawBufTotalLen() const {
	unsigned int uLenRawBuf;

	uLenRawBuf = 0;
	for ( auto pPackageBox : m_containerPackageBox ) {
		uLenRawBuf += pPackageBox->m_pHeader->m_i16PayloadLen;
	}
	return uLenRawBuf;
}

bool HMNWPPackageDepot::isValidNWPHeader( const HMNWPHeader* pNWPHeader ) {
	if ( !pNWPHeader )
		return false;
	if ( pNWPHeader->m_i16PackageIndex >= pNWPHeader->m_i16PackageCount )
		return false;
	
	return true;
}


void HMNWPPackageDepot::_clearAllPackage() {
	for ( auto pPackageBox : m_containerPackageBox ) {
		delete pPackageBox;
		pPackageBox = NULL;
	}
	m_containerPackageBox.clear();
}

HMNWP_NAMESPACE_END
