#include "stdafx.h"
#include "CRClientStubDepot.h"
#include "CRSrvRoot.h"
#include "HMTSHelper.h"
#include "MemfuncPack.h"

CRClientStubDepot::CRClientStubDepot( CRSrvRoot* pSrvRoot )
: m_pSrvRoot( pSrvRoot )
, m_pTSAccess( new HMTSHelper() )
, m_pMapSocket2ClientStub( new socket2clientstub_map_type() ) {

}

CRClientStubDepot::~CRClientStubDepot() {
	delete m_pMapSocket2ClientStub;
	m_pMapSocket2ClientStub = NULL;

	delete m_pTSAccess;
	m_pTSAccess = NULL;
}

void CRClientStubDepot::regClientStub( SOCKET sConnect, const sockaddr_in& sAddr ) {
	if ( !m_pTSAccess->safeEnterFunc() )
		return;
	CMemFuncPack mpfkSafeExit( m_pTSAccess, &HMTSHelper::safeExitFunc );
	//
	if ( _hasClientStub( sConnect ) ) {
		assert( false );
	    _delClientStub( sConnect );
	}
	
	//
	if ( !m_pSrvRoot->m_pCSF )
		return;
	(*m_pMapSocket2ClientStub)[ sConnect ] = m_pSrvRoot->m_pCSF->createClientStub( m_pSrvRoot, sConnect, sAddr );
}

void CRClientStubDepot::unregClientStub( SOCKET sConnect ) {
	if ( !m_pTSAccess->safeEnterFunc() )
		return;
	CMemFuncPack mpfkSafeExit( m_pTSAccess, &HMTSHelper::safeExitFunc );
	//
	assert( _hasClientStub( sConnect ) );
	_delClientStub( sConnect );
}

CRClientStub* CRClientStubDepot::getClientStub( SOCKET sConnect ) {
	if ( !m_pTSAccess->safeEnterFunc() )
		return NULL;
	CMemFuncPack mpfkSafeExit( m_pTSAccess, &HMTSHelper::safeExitFunc );
	//

	return _getClientStub( sConnect );
}

CRClientStub* CRClientStubDepot::_getClientStub( SOCKET sConnect ) {
    socket2clientstub_map_type::iterator itSocket2ClientStub;

	itSocket2ClientStub = m_pMapSocket2ClientStub->find(sConnect);
	if ( itSocket2ClientStub == m_pMapSocket2ClientStub->end() )
		return NULL;
	return itSocket2ClientStub->second;
}

bool CRClientStubDepot::_hasClientStub( SOCKET sConnect ) const {
    return m_pMapSocket2ClientStub->find( sConnect ) != m_pMapSocket2ClientStub->end();
}

bool CRClientStubDepot::_delClientStub( SOCKET sConnect ) {
    socket2clientstub_map_type::iterator itSocket2ClientStub;

	itSocket2ClientStub = m_pMapSocket2ClientStub->find(sConnect);
	if ( itSocket2ClientStub == m_pMapSocket2ClientStub->end() )
		return false;
	delete itSocket2ClientStub->second;
	itSocket2ClientStub->second = NULL;
	m_pMapSocket2ClientStub->erase( itSocket2ClientStub );
	return true;
}







