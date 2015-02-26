#include "stdafx.h"
#include "CRAccountBase.h"
#include "CRErrCode.h"
#include "CRTypes.h"

CRAccountData::CRAccountData( const CRAccountData& val )
: m_strUserName( val.m_strUserName )
, m_strPassword( val.m_strPassword )
, m_strPhoneNum( val.m_strPhoneNum )
, m_strEMail( val.m_strEMail )
, m_strNickName( val.m_strNickName )
, m_eSortType( val.m_eSortType )
, m_nCountAttetioned( val.m_nCountAttetioned )
, m_nCountAttetion( val.m_nCountAttetion )
, m_nCountPublished( val.m_nCountPublished ) {

}

CRAccountData::CRAccountData()
: m_strUserName( "" )
, m_strPassword( "" )
, m_strPhoneNum( "" )
, m_strEMail( "" )
, m_strNickName( "" )
, m_eSortType( EACCOUNT_SORT_UNKNOWN )
, m_nCountAttetion( 0 )
, m_nCountAttetioned( 0 )
, m_nCountPublished( 0 ) {
    
}

CRAccountData& CRAccountData::operator=( const CRAccountData& val ) {
	if ( &val == this ) {
	    return *this;
	}
    m_strUserName = val.m_strUserName;
    m_strPassword = val.m_strPassword;
    m_strPhoneNum = val.m_strPhoneNum;
    m_strEMail = val.m_strEMail;
    m_strNickName = val.m_strNickName;
    m_eSortType = val.m_eSortType;
    m_nCountAttetion = val.m_nCountAttetion;
    m_nCountAttetioned = val.m_nCountAttetioned;
    m_nCountPublished = val.m_nCountPublished;
	return *this;
}

CRAccountData::~CRAccountData() {
    
}

CRAccountBase::CRAccountBase() {

}

CRAccountBase::CRAccountBase( const CRAccountData& paramAccountReg )
: m_data( paramAccountReg ) {

}

CRAccountBase::~CRAccountBase() {

}

bool CRAccountBase::doLogin( const CRLoginParam& loginParam, int& nErrCode ) {
    CRLoginInfo loginInfo;
	//
	if ( loginParam.m_strPassword.compare( m_data.m_strPassword ) != 0 ) {
	    nErrCode = CRERR_SRV_ACCOUNT_PASSWORD_INCORRECT;
		return false;
	}
	//
	if ( m_loginRecord.getLoginInfo( loginParam.m_eOSType, loginInfo ) ) {
		if ( loginInfo.m_rmsgMetaData.m_sConnect == loginParam.m_pRMsgMetaData->m_sConnect ) {
		    return true;
		}
		// kick off the older login.
		m_loginRecord.eraseRecord( loginInfo.m_rmsgMetaData.m_sConnect );
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