#include "stdafx.h"
#include "CRModuleAccountMgr.h"
#include "CRServerRoot.h"
#include "hmcmn_event_depot.h"
#include "CRRMsgHandler4Login.h"
#include "CRAccountDepot.h"
#include "CRAccountCreator.h"
#include "CRErrCode.h"
#include "CRSrvEvtDefs.h"
#include "CRLog.h"
#include "MemFuncPack.h"
#include "FuncPack.h"

CRModuleAccountMgr::CRModuleAccountMgr()
//:  m_pFuncObjClientAccept( new hmcmn::hmcmn_event_depot::arg2event_handler_type( std::bind( &CRModuleAccountMgr::_onEvtClientAccept, this, _1, _2 ) ) )
//, m_pFuncObjClientDisConnect( new hmcmn::hmcmn_event_depot::arg2event_handler_type( std::bind( &CRModuleAccountMgr::_onEvtClientDisConnect, this, _1, _2 ) ) )
{
}

CRModuleAccountMgr::~CRModuleAccountMgr() {
	m_tsAccess.cancelAllAccess();
	
	////
	//if ( m_pFuncObjClientAccept ) {
	//    g_CRSrvRoot.m_pEventDepot->unbind( ECRSRVEVT_CLIENT_ACCEPTED, (hmcmn::hmcmn_event_depot::arg2event_handler_type*)m_pFuncObjClientAccept );
	//    delete m_pFuncObjClientAccept;
	//	m_pFuncObjClientAccept = NULL;
	//}
	//if ( m_pFuncObjClientDisConnect ) {
 //       g_CRSrvRoot.m_pEventDepot->unbind( ECRSRVEVT_CLIENT_DISCONNECTED, m_pFuncObjClientDisConnect );
	//    delete m_pFuncObjClientDisConnect;
	//	m_pFuncObjClientDisConnect= NULL;
	//}
}

const CRAccountBase* CRModuleAccountMgr::getAccount( SOCKET sConnect ) const {
    if ( !m_tsAccess.safeEnterFunc() )
		return NULL;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	socket2account_map_type::const_iterator citSocket2Account;

	citSocket2Account = m_mapSocket2Account.find( sConnect );
	if ( citSocket2Account == m_mapSocket2Account.end() ){
	    return NULL;
	}

	return citSocket2Account->second;
}

const CRAccountBase* CRModuleAccountMgr::getAccount( const utf8_type& strAccountName, int& nErrCode ) {
	return m_accountDepot.getAccount( strAccountName, nErrCode );
}

bool CRModuleAccountMgr::doLogin( const CRLoginParam& loginParam, int& nErrCode ) {
	if ( !m_tsAccess.safeEnterFunc() ) {
	    CRLOG_INFO( "cann't safe enter." );
		return false;
	}
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	//
	if ( !m_accountDepot.refreshAccountData( loginParam.m_strUserName, nErrCode ) ) {
        CRLOG_ERROR( "refreshAccountData failed." );	
		return false;
	}
	//
	CRAccountBase* pAccount = (CRAccountBase*)m_accountDepot.getAccount( loginParam.m_strUserName, nErrCode );
	if ( !pAccount ) {
		nErrCode = CRERR_SRV_ACCOUNTNAME_ISNOT_EXIST;
	    return false;
	}
	bool bSuccess = pAccount->doLogin( loginParam, nErrCode );
	if ( bSuccess ) {
	    _addAccount2SocketMap( loginParam.m_pRMsgMetaData->m_sConnect, pAccount );
	}
	return bSuccess;
}

bool CRModuleAccountMgr::doLogoff( const CRLogoffParam& logoffParam, int& nErrCode ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	CRAccountBase* pAccount = (CRAccountBase*)m_accountDepot.getAccount( logoffParam.m_strUserName, nErrCode );
	if ( !pAccount ) {
		nErrCode = CRERR_SRV_ACCOUNTNAME_ISNOT_EXIST;
	    return false;
	}

	if ( !pAccount->doLogoff( logoffParam, nErrCode ) )
		return false;
	//
	_eraseAccountFromSocketMap( logoffParam.m_pRMsgMetaData->m_sConnect );
	return true;
}

bool CRModuleAccountMgr::doRegAccount( const CRAccountData& accountRegParam, int& nErrCode ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	CRAccountBase* pAccountNew = NULL;
	bool bOK = false;
	nErrCode = CRERR_SRV_NONE;
	//
	if ( m_accountDepot.hasAccount( accountRegParam.m_strUserName, nErrCode ) ) {
	    nErrCode = CRERR_SRV_ACCOUNTNAME_EXIST;
		return false;
	} else {
	    if ( nErrCode != CRERR_SRV_NONE )
			return false;
	}
	//
	pAccountNew = CRAccountCreator::create( accountRegParam, nErrCode );
	if ( !pAccountNew )
		return false;
	CFuncPack fpkDelAccount( ::gfnDelObj< CRAccountBase >, pAccountNew );
	//
	bOK = m_accountDepot.addAccount( pAccountNew, nErrCode );
	if ( bOK ) {
	    fpkDelAccount.Cancel();
	}
	return bOK;
}

void CRModuleAccountMgr::onEvtClientAccept( void* pParam1, void* pParam2 ) {
	int a = 0;
}

void CRModuleAccountMgr::onEvtClientDisConnect( void* pParam1, void* pParam2 ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
    SOCKET sConnect = (SOCKET)pParam1;
    const sockaddr_in* psAddr = (const sockaddr_in*)pParam2;
	CRAccountBase* pAccount = NULL;

	pAccount = _getAccountInSocketMap( sConnect );
	if ( pAccount ) {
	    pAccount->onDisconnect( sConnect );
	    _eraseAccountFromSocketMap( sConnect );
	}
}

void CRModuleAccountMgr::_addAccount2SocketMap( SOCKET sConnect, CRAccountBase* pAccount ) {
    // assert( m_mapSocket2Account.find( sConnect ) == m_mapSocket2Account.end() );
	m_mapSocket2Account[ sConnect ] = pAccount;
}

void CRModuleAccountMgr::_eraseAccountFromSocketMap( SOCKET sConnect ) {
	assert( m_mapSocket2Account.find( sConnect ) != m_mapSocket2Account.end() );
	m_mapSocket2Account.erase( sConnect );
}

void CRModuleAccountMgr::_eraseAccountFromSocketMap( CRAccountBase* pAccount ) {
	socket2account_map_type::iterator itCache, iendCache;

	iendCache = m_mapSocket2Account.end();
	for ( itCache = m_mapSocket2Account.begin(); itCache!=iendCache; ++itCache ) {
	    if ( itCache->second == pAccount ) {
		    m_mapSocket2Account.erase( itCache );
			return;
		}
	}

}

bool CRModuleAccountMgr::_hasAccountInSocketMap( SOCKET sConnect ) const {
	return m_mapSocket2Account.find( sConnect ) != m_mapSocket2Account.end();
}

bool CRModuleAccountMgr::_hasAccountInSocketMap( CRAccountBase* pAccount ) const {
	socket2account_map_type::const_iterator citCache, ciendCache;

	ciendCache = m_mapSocket2Account.end();
	for ( citCache = m_mapSocket2Account.begin(); citCache!=ciendCache; ++citCache ) {
	    if ( citCache->second == pAccount ) {
		    return true;
		}
	}

	return false;
}


void CRModuleAccountMgr::getAccountsData( utf8_container_type containerAccountName, accountdata_container_type& containerAccountData ) {
	int nErrCode = CRERR_SRV_NONE;
	m_accountDepot.getAccountsData( containerAccountName, containerAccountData, nErrCode );
}

CRAccountBase* CRModuleAccountMgr::_getAccountInSocketMap( SOCKET sConnect ) {
    socket2account_map_type::iterator itCache;

	itCache = m_mapSocket2Account.find( sConnect );
	if ( itCache == m_mapSocket2Account.end() )
		return NULL;
	return itCache->second;
}






