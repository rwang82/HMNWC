#include "stdafx.h"
#include "CRAccountBase.h"
#include "CRErrCode.h"

CRAccountBase::CRAccountBase( const CRAccountRegParam& paramAccountReg )
: m_regInfo( paramAccountReg ) {

}

CRAccountBase::~CRAccountBase() {

}

bool CRAccountBase::doLogin( const CRLoginParam& loginParam, int& nErrCode ) {
    //
	if ( loginParam.m_tstrPassword.compare( m_regInfo.m_tstrPassword ) != 0 ) {
	    nErrCode = CRERR_SRV_ACCOUNT_PASSWORD_INCORRECT;
		return false;
	}
	//
	if ( m_loginRecord.hasLogin( loginParam.m_eOSType ) ) {
	    nErrCode = CRERR_SRV_ACCOUNT_LOGINED_INSAMEOS;
		return false;
	}

	return m_loginRecord.addRecord( *(loginParam.m_pRMsgMetaData), loginParam.m_eOSType, nErrCode );
}
	
void CRAccountBase::doLogoff( const CRLogoffParam& logoffParam, int& nErrCode ) {
	if ( !m_loginRecord.hasLogin( logoffParam.m_eOSType ) ) {
	    nErrCode = CRERR_SRV_ACCOUNT_NOLOGINRECORD;
		return;
	}
	m_loginRecord.eraseRecord( *(logoffParam.m_pRMsgMetaData), logoffParam.m_eOSType, nErrCode );
}

void CRAccountBase::onDisconnect( SOCKET sConnect ) {
    m_loginRecord.eraseRecord( sConnect );
}