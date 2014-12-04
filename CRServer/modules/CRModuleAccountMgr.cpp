#include "stdafx.h"
#include "CRModuleAccountMgr.h"
#include "CRServerRoot.h"
#include "hmcmn_event_depot.h"
#include "CRRMsgHandler4Login.h"
#include "CRAccountDepot.h"
#include "CRAccountCreator.h"
#include "CRErrCode.h"
#include "CRSrvEvtDefs.h"
#include "MemFuncPack.h"

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

bool CRModuleAccountMgr::doLogin( const CRLoginParam& loginParam, int& nErrCode ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	CRAccountBase* pAccount = (CRAccountBase*)m_accountDepot.getAccount( loginParam.m_tstrUserName );
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
	CRAccountBase* pAccount = (CRAccountBase*)m_accountDepot.getAccount( logoffParam.m_tstrUserName );
	if ( !pAccount ) {
		nErrCode = CRERR_SRV_ACCOUNTNAME_ISNOT_EXIST;
	    return false;
	}

	pAccount->doLogoff( logoffParam, nErrCode );
	//
	_eraseAccountFromSocketMap( logoffParam.m_pRMsgMetaData->m_sConnect );
	return true;
}

bool CRModuleAccountMgr::doRegAccount( const CRAccountRegParam& accountRegParam, int& nErrCode ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	CRAccountBase* pAccountNew = NULL;
	//
	if ( m_accountDepot.hasAccount( accountRegParam.m_tstrUserName ) ) {
	    nErrCode = CRERR_SRV_ACCOUNTNAME_EXIST;
		return false;
	}
	//
	pAccountNew = CRAccountCreator::create( accountRegParam, nErrCode );
	if ( !pAccountNew )
		return false;
	return m_accountDepot.addAccount( pAccountNew );
}

void CRModuleAccountMgr::onEvtClientAccept( void* pParam1, void* pParam2 ) {

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
    assert( m_mapSocket2Account.find( sConnect ) == m_mapSocket2Account.end() );
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

CRAccountBase* CRModuleAccountMgr::_getAccountInSocketMap( SOCKET sConnect ) {
    socket2account_map_type::iterator itCache;

	itCache = m_mapSocket2Account.find( sConnect );
	if ( itCache == m_mapSocket2Account.end() )
		return NULL;
	return itCache->second;
}






