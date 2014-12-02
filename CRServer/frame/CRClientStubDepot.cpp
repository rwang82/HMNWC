#include "stdafx.h"
#include "CRClientStubDepot.h"
#include "MemfuncPack.h"

CRClientStubDepot::CRClientStubDepot() {

}

CRClientStubDepot::~CRClientStubDepot() {

}

void CRClientStubDepot::regClientStub( SOCKET sConnect, const sockaddr_in& sAddr ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return;
	CMemFuncPack mpfkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	//
	if ( _hasClientStub( sConnect ) ) {
		assert( false );
	    _delClientStub( sConnect );
	}
	m_mapSocket2ClientStub[ sConnect ] = new CRClientStub( sConnect, sAddr );
}

void CRClientStubDepot::unregClientStub( SOCKET sConnect ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return;
	CMemFuncPack mpfkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	//
	assert( _hasClientStub( sConnect ) );
	_delClientStub( sConnect );
}

CRClientStub* CRClientStubDepot::getClientStub( SOCKET sConnect ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return NULL;
	CMemFuncPack mpfkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	//

	return _getClientStub( sConnect );
}

CRClientStub* CRClientStubDepot::_getClientStub( SOCKET sConnect ) {
    socket2clientstub_map_type::iterator itSocket2ClientStub;

	itSocket2ClientStub = m_mapSocket2ClientStub.find(sConnect);
	if ( itSocket2ClientStub == m_mapSocket2ClientStub.end() )
		return NULL;
	return itSocket2ClientStub->second;
}

bool CRClientStubDepot::_hasClientStub( SOCKET sConnect ) const {
    return m_mapSocket2ClientStub.find( sConnect ) != m_mapSocket2ClientStub.end();
}

bool CRClientStubDepot::_delClientStub( SOCKET sConnect ) {
    socket2clientstub_map_type::iterator itSocket2ClientStub;

	itSocket2ClientStub = m_mapSocket2ClientStub.find(sConnect);
	if ( itSocket2ClientStub == m_mapSocket2ClientStub.end() )
		return false;
	delete itSocket2ClientStub->second;
	itSocket2ClientStub->second = NULL;
	m_mapSocket2ClientStub.erase( itSocket2ClientStub );
	return true;
}







