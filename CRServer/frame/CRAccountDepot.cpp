#include "stdafx.h"
#include "CRAccountDepot.h"
#include "CRServerRoot.h"
#include "CRSrvDBProxy.h"
#include "CRAccountCreator.h"
#include "MemFuncPack.h"

CRAccountDepot::CRAccountDepot() {

}

CRAccountDepot::~CRAccountDepot() {
	m_tsAccess.cancelAllAccess();
	_clearAllAccount();
}

bool CRAccountDepot::hasAccount( const tstring_type& tstrAccountName, int& nErrCode ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );

	return _hasAccount( tstrAccountName, nErrCode );
}

bool CRAccountDepot::addAccount( CRAccountBase* pAccountNew, int& nErrCode ) {
	if ( !pAccountNew )
		return false;
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );

	if ( _hasAccount( pAccountNew->m_regInfo.m_tstrUserName, nErrCode ) )
		return false;
	//
	if ( !g_CRSrvRoot.m_pSrvDBProxy->save2DB( pAccountNew, nErrCode ) )
		return false;
	m_mapName2AccountObj[ pAccountNew->m_regInfo.m_tstrUserName ] = pAccountNew;
	//
	return true;
}

CRAccountBase* CRAccountDepot::getAccount( const tstring_type& tstrAccountName, int& nErrCode ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return NULL;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	name2obj_map_type::const_iterator citName2Obj;

	if ( !_hasAccount( tstrAccountName, nErrCode ) )
		return NULL;
	citName2Obj = m_mapName2AccountObj.find( tstrAccountName );
	if ( citName2Obj != m_mapName2AccountObj.end() ) {
	    return citName2Obj->second;
	}
	
	assert( false );
	return citName2Obj->second;
}

bool CRAccountDepot::_hasAccount( const tstring_type& tstrAccountName, int& nErrCode ) {
	if ( m_mapName2AccountObj.find( tstrAccountName ) != m_mapName2AccountObj.end() )
		return true;

	return _loadAccountFromDB( tstrAccountName, nErrCode );
}

bool CRAccountDepot::_loadAccountFromDB( const tstring_type& tstrAccountName, int& nErrCode ) {
	CRAccountBase* pAccountObj = NULL;

	pAccountObj = CRAccountCreator::loadFromDB( tstrAccountName, nErrCode );
	if ( !pAccountObj )
		return false;
	m_mapName2AccountObj[ tstrAccountName ] = pAccountObj;
	return true;
}

void CRAccountDepot::_clearAllAccount() {
    name2obj_map_type::iterator itName2Obj, iendName2Obj;
	CRAccountBase* pAccountObj = NULL;

	iendName2Obj = m_mapName2AccountObj.end();
	for ( itName2Obj = m_mapName2AccountObj.begin(); itName2Obj!=iendName2Obj; ++itName2Obj ) {
	    pAccountObj = itName2Obj->second;
		delete pAccountObj;
		pAccountObj = NULL;
	}
	m_mapName2AccountObj.clear();
}