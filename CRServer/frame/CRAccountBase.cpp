#include "stdafx.h"
#include "CRAccountBase.h"
#include "CRErrCode.h"
#include "CRTypes.h"

CRAccountRegParam::CRAccountRegParam()
: m_tstrUserName( _T("") )
, m_tstrPassword( _T("") )
, m_tstrPhoneNum( _T("") )
, m_tstrEMail( _T("") )
, m_tstrNickName( _T("") )
, m_eSortType( EACCOUNT_SORT_UNKNOWN ) {
    
}

CRAccountRegParam::~CRAccountRegParam() {
    
}

CRAccountBase::CRAccountBase() {

}

CRAccountBase::CRAccountBase( const CRAccountRegParam& paramAccountReg )
: m_regInfo( paramAccountReg ) {

}

CRAccountBase::~CRAccountBase() {

}

bool CRAccountBase::doLogin( const CRLoginParam& loginParam, int& nErrCode ) {
    CRLoginInfo loginInfo;
	//
	if ( loginParam.m_tstrPassword.compare( m_regInfo.m_tstrPassword ) != 0 ) {
	    nErrCode = CRERR_SRV_ACCOUNT_PASSWORD_INCORRECT;
		return false;
	}
	//
	if ( m_loginRecord.getLoginInfo( loginParam.m_eOSType, loginInfo ) ) {
		if ( loginInfo.m_rmsgMetaData.m_sConnect == loginParam.m_pRMsgMetaData->m_sConnect ) {
		    return true;
		}
		// make be need more code here, to kick off the older login.
	    nErrCode = CRERR_SRV_ACCOUNT_LOGINED_INSAMEOS;
		return false;
	}

	return m_loginRecord.addRecord( *(loginParam.m_pRMsgMetaData), loginParam.m_eOSType, nErrCode );
}
	
bool CRAccountBase::doLogoff( const CRLogoffParam& logoffParam, int& nErrCode ) {
	CRLoginInfo loginInfo;

	// check loginInfo.
	if ( !m_loginRecord.hasLogin( logoffParam.m_eOSType ) ) {
	    nErrCode = CRERR_SRV_ACCOUNT_NOLOGINRECORD;
		return false;
	}
	// get loginInfo.
	if ( !m_loginRecord.getLoginInfo( logoffParam.m_eOSType, loginInfo ) ) {
	    assert( false );
		return false;
	}
	//
	if ( loginInfo.m_rmsgMetaData.m_sConnect != logoffParam.m_pRMsgMetaData->m_sConnect ) {
	    nErrCode = CRERR_SRV_ACCOUNT_LOGOFF_NOTSAMESESSION;
		return false;
	}
	m_loginRecord.eraseRecord( *(logoffParam.m_pRMsgMetaData), logoffParam.m_eOSType, nErrCode );
    return true;
}

void CRAccountBase::onDisconnect( SOCKET sConnect ) {
    m_loginRecord.eraseRecord( sConnect );
}