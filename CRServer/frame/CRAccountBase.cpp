#include "stdafx.h"
#include "CRAccountBase.h"
#include "CRErrCode.h"
#include "CRTypes.h"

CRAccountData::CRAccountData( const CRAccountData& val )
: m_tstrUserName( val.m_tstrUserName )
, m_tstrPassword( val.m_tstrPassword )
, m_tstrPhoneNum( val.m_tstrPhoneNum )
, m_tstrEMail( val.m_tstrEMail )
, m_tstrNickName( val.m_tstrNickName )
, m_eSortType( val.m_eSortType )
, m_nCountAttetioned( val.m_nCountAttetioned )
, m_nCountAttetion( val.m_nCountAttetion )
, m_nCountPublished( val.m_nCountPublished ) {

}

CRAccountData::CRAccountData()
: m_tstrUserName( _T("") )
, m_tstrPassword( _T("") )
, m_tstrPhoneNum( _T("") )
, m_tstrEMail( _T("") )
, m_tstrNickName( _T("") )
, m_eSortType( EACCOUNT_SORT_UNKNOWN )
, m_nCountAttetion( 0 )
, m_nCountAttetioned( 0 )
, m_nCountPublished( 0 ) {
    
}

CRAccountData& CRAccountData::operator=( const CRAccountData& val ) {
	if ( &val == this ) {
	    return *this;
	}
    m_tstrUserName = val.m_tstrUserName;
    m_tstrPassword = val.m_tstrPassword;
    m_tstrPhoneNum = val.m_tstrPhoneNum;
    m_tstrEMail = val.m_tstrEMail;
    m_tstrNickName = val.m_tstrNickName;
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
	if ( loginParam.m_tstrPassword.compare( m_data.m_tstrPassword ) != 0 ) {
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