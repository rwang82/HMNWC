#include "stdafx.h"
#include "HMNWPPackImpl.h"
#include "HMNWPPackage.h"
#include <assert.h>
HMNWP_NAMESPACE_BEGIN
//
HMNWPPackImpl::HMNWPPackImpl() {

}

HMNWPPackImpl::~HMNWPPackImpl() {

}

bool HMNWPPackImpl::createPackages( const unsigned char* pRawBuf, unsigned int uLenRawData, nwppackage_container_type& containerNWPPackage ) {
	if ( !pRawBuf || uLenRawData == 0 ) {
		assert( false );
		return false;
	}
	unsigned int uPackageCount = 0;
	unsigned int uLenDataNoPacked = uLenRawData;
	HMNWPPackage* pNWPPackageNew = NULL;
	const unsigned char* pPosRawData = NULL;

	pPosRawData = pRawBuf;
	uPackageCount = ( ( uLenRawData - 1 ) / HMNWP_LEN_PAYLOAD_MAX ) + 1;
	for ( unsigned int uPackageIndex = 0; uPackageIndex != uPackageCount; ++uPackageIndex ) {
		HMNWPHeader header;
		header.m_i16PackageCount = uPackageCount;
		header.m_i16PackageIndex = uPackageIndex;
		if ( ( uPackageIndex + 1 ) < uPackageCount ) {
			header.m_i16PayloadLen = HMNWP_LEN_PAYLOAD_MAX;
		} else {
			header.m_i16PayloadLen = uLenDataNoPacked;
		}
		pNWPPackageNew = new HMNWPPackage( &header, pPosRawData );
		pPosRawData += header.m_i16PayloadLen;
		uLenDataNoPacked -= header.m_i16PayloadLen;
		containerNWPPackage.push_back( pNWPPackageNew );
	}
	return true;
}

void HMNWPPackImpl::destroyPackages( nwppackage_container_type* pContainerNWPPackage ) {
	if ( !pContainerNWPPackage )
		return;
	nwppackage_container_type::iterator itNWPPackage, iendNWPPackage;
	HMNWPPackage* pNWPPackage = NULL;

	iendNWPPackage = pContainerNWPPackage->end();
	for ( itNWPPackage = pContainerNWPPackage->begin(); itNWPPackage != iendNWPPackage; ++itNWPPackage ) {
		pNWPPackage = *itNWPPackage;
		if ( pNWPPackage ) {
			delete pNWPPackage;
			pNWPPackage = NULL;
		}
	}
	pContainerNWPPackage->clear();
}




HMNWP_NAMESPACE_END
