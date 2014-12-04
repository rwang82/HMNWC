#include "stdafx.h"
#include "CRAccountDepot.h"
#include "MemFuncPack.h"

CRAccountDepot::CRAccountDepot() {

}

CRAccountDepot::~CRAccountDepot() {
	m_tsAccess.cancelAllAccess();
	_clearAllAccount();
}

bool CRAccountDepot::hasAccount( const tstring_type& tstrAccountName ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );

	return _hasAccount( tstrAccountName );
}

bool CRAccountDepot::addAccount( CRAccountBase* pAccountNew ) {
	if ( !pAccountNew )
		return false;
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );

	if ( _hasAccount( pAccountNew->m_regInfo.m_tstrUserName ) )
		return false;
	//
	m_mapName2AccountObj[ pAccountNew->m_regInfo.m_tstrUserName ] = pAccountNew;
	return true;
}

CRAccountBase* CRAccountDepot::getAccount( const tstring_type& tstrAccountName ) const {
	if ( !m_tsAccess.safeEnterFunc() )
		return NULL;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	name2obj_map_type::const_iterator citName2Obj;

	citName2Obj = m_mapName2AccountObj.find( tstrAccountName );
	if ( citName2Obj == m_mapName2AccountObj.end() )
		return NULL;
	return citName2Obj->second;
}

bool CRAccountDepot::_hasAccount( const tstring_type& tstrAccount ) const {
	return m_mapName2AccountObj.find( tstrAccount ) != m_mapName2AccountObj.end();
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