#include "stdafx.h"
#include "CRAccountDepot.h"
#include "CRServerRoot.h"
#include "CRSrvDBProxy.h"
#include "CRAccountCreator.h"
#include "CRAccountList.h"
#include "CRErrCode.h"
#include "CRLog.h"
#include "MemFuncPack.h"

CRAccountDepot::CRAccountDepot() {

}

CRAccountDepot::~CRAccountDepot() {
	m_tsAccess.cancelAllAccess();
	_clearAllAccount();
}

bool CRAccountDepot::hasAccount( const utf8_type& strAccountName, int& nErrCode ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );

	return _hasAccount( strAccountName, nErrCode );
}

bool CRAccountDepot::addAccount( CRAccountBase* pAccountNew, int& nErrCode ) {
	if ( !pAccountNew )
		return false;
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );

	if ( _hasAccount( pAccountNew->m_data.m_strUserName, nErrCode ) )
		return false;
	//
	if ( !g_CRSrvRoot.m_pSrvDBProxy->save2DB( pAccountNew, nErrCode ) )
		return false;
	m_mapName2AccountObj[ pAccountNew->m_data.m_strUserName ] = pAccountNew;
	//
	return true;
}

bool CRAccountDepot::refreshAccountsData( const utf8_container_type& containerAccountName, int& nErrCode ) {
	nErrCode = CRERR_SRV_NONE;
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	name2obj_map_type::const_iterator citName2Obj, ciendName2Obj;
	utf8_container_type::const_iterator citName, ciendName;
	CRAccountData* pAccountData = NULL;

	// fetch account info from db.
	return _loadAccountFromDB( containerAccountName, nErrCode );
}

bool CRAccountDepot::refreshAccountData( const utf8_type& strAccountName, int& nErrCode ) {
	utf8_container_type containerAccountName;

	containerAccountName.push_back( strAccountName );

	return refreshAccountsData( containerAccountName, nErrCode );
}

bool CRAccountDepot::getAccountsData( const utf8_container_type& containerAccountName, accountdata_container_type& containerAccountData, int& nErrCode ) {
	nErrCode = CRERR_SRV_NONE;
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	name2obj_map_type::const_iterator citName2Obj, ciendName2Obj;
	utf8_container_type::const_iterator citName, ciendName;
	CRAccountData* pAccountData = NULL;

	// fetch account info from db.
	if ( !_loadAccountFromDB( containerAccountName, nErrCode ) )
	    return false;

	// save account data.
	ciendName2Obj = m_mapName2AccountObj.end();
	ciendName = containerAccountName.end();
	for ( citName = containerAccountName.begin(); citName!=ciendName; ++citName ) {
	    citName2Obj = m_mapName2AccountObj.find( citName->c_str() );
		if ( citName2Obj != ciendName2Obj ) {
		    containerAccountData.push_back( citName2Obj->second->m_data );
		}
	}

	return true;
}

CRAccountBase* CRAccountDepot::getAccount( const utf8_type& strAccountName, int& nErrCode ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return NULL;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	name2obj_map_type::const_iterator citName2Obj;

	if ( !_hasAccount( strAccountName, nErrCode ) )
		return NULL;
	citName2Obj = m_mapName2AccountObj.find( strAccountName );
	if ( citName2Obj != m_mapName2AccountObj.end() ) {
	    return citName2Obj->second;
	}
	
	assert( false );
	return citName2Obj->second;
}

bool CRAccountDepot::_loadAccountFromDB( const utf8_container_type& containerAccountName, int& nErrCode ) {
	CRAccountList accountList;
	CRAccountList::accountuser_container_type::iterator itAccount, iendAccount;
	name2obj_map_type::iterator itName2Obj, iendName2Obj;
	CRAccountBase* pAccountObjNew = NULL;

	if ( !g_CRSrvRoot.m_pSrvDBProxy->loadFromDB( (void*)&containerAccountName, &accountList, nErrCode ) ) {
	    return false;
	}
	//
	iendAccount = accountList.m_containerAccount.end();
	for ( itAccount = accountList.m_containerAccount.begin(); itAccount!=iendAccount; ++itAccount ) {
	    pAccountObjNew = (*itAccount);
		itName2Obj = m_mapName2AccountObj.find( pAccountObjNew->m_data.m_strUserName );
	    if ( itName2Obj != m_mapName2AccountObj.end() ) {
		    itName2Obj->second->m_data = pAccountObjNew->m_data;
			delete pAccountObjNew;
			pAccountObjNew = NULL;
		} else {
		    m_mapName2AccountObj[ pAccountObjNew->m_data.m_strUserName ] = pAccountObjNew;
		}
	}

	return true;
}

bool CRAccountDepot::_hasAccount( const utf8_type& strAccountName, int& nErrCode ) {
	if ( m_mapName2AccountObj.find( strAccountName ) != m_mapName2AccountObj.end() )
		return true;

	return _loadAccountFromDB( strAccountName, nErrCode );
}

bool CRAccountDepot::_loadAccountFromDB( const utf8_type& strAccountName, int& nErrCode ) {
	CRAccountBase* pAccountObj = NULL;

	pAccountObj = CRAccountCreator::loadFromDB( strAccountName, nErrCode );
	if ( !pAccountObj )
		return false;
	m_mapName2AccountObj[ strAccountName ] = pAccountObj;
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