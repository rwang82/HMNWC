#include "stdafx.h"
#include "CRRMsgHandler4Login.h"
#include "CRRMsg.h"
#include "CRServerRoot.h"
#include "CRModuleAccountMgr.h"
#include "CRModuleIDDefs.h"
#include "CRModuleDepot.h"
#include "CRRMsgJsonHelper.h"
#include "CRRCmdDefs.h"
#include "HMNWPServer.h"
#include "HMCharConv.h"
#include "json/json.h"
#include <atlconv.h>
//
const int CRLOGIN_ERR_UNKNOWN = -1;
const int CRLOGIN_ERR_NONE = 0;
const int CRLOGIN_ERR_LOGINED = 1;
const int CRLOGIN_ERR_INVALIDPARAMS = 2;
//
const int CRLOGIN_RESULT_FAILED = 0;
const int CRLOGIN_RESULT_SUCCESS = 1;
//
CRLoginParam::CRLoginParam()
: m_tstrUserName( _T("") )
, m_tstrPassword( _T("") )
, m_pRMsgMetaData( NULL )
, m_eOSType( EOS_UNKNOWN ) {
}

CRLoginParam::~CRLoginParam() {
}
//
CRRMsgHandler4Login::CRRMsgHandler4Login() {

}

CRRMsgHandler4Login::~CRRMsgHandler4Login() {

}

void CRRMsgHandler4Login::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
    CRLoginParam loginParam;
	int nErrCode = CRLOGIN_ERR_NONE;
	
	if ( !_fillLoginParam( rmsgMetaData, pRMsgJson, loginParam ) ) {
		nErrCode = CRLOGIN_ERR_INVALIDPARAMS;
		_sendFailedAck( loginParam, rmsgMetaData, pRMsgJson, nErrCode );
		return;
	}
	//
	if ( _doLogin( loginParam, nErrCode ) ) {
	    _sendSuccessAck( loginParam, rmsgMetaData, pRMsgJson );
	} else {
	    _sendFailedAck( loginParam, rmsgMetaData, pRMsgJson, nErrCode );
	}
}

void CRRMsgHandler4Login::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}

bool CRRMsgHandler4Login::_doLogin( const CRLoginParam& loginParam, int& nErrCode ) {
    CRModuleAccountMgr* pModuleAccountMgr = NULL;
	nErrCode = CRLOGIN_ERR_UNKNOWN;
		
	pModuleAccountMgr = dynamic_cast< CRModuleAccountMgr* >( g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_ACCOUNTMGR ) );
	if ( !pModuleAccountMgr )
		return false;

	return pModuleAccountMgr->doLogin( loginParam, nErrCode );
}

bool CRRMsgHandler4Login::_fillLoginParam( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson, CRLoginParam& loginParam ) {
    if ( !pRMsgJson )
		return false;
	USES_CONVERSION;
	
	// m_pRMsgMetaData
	loginParam.m_pRMsgMetaData = &rmsgMetaData;
	// m_eOSType
	loginParam.m_eOSType = pRMsgJson->m_eOSType;
	//
	const Json::Value& valParams = pRMsgJson->m_jsonRoot[ "params" ];
	if ( !valParams.isObject() )
		return false;
	// m_tstrUserName
	const Json::Value& valUserName = valParams[ "username" ];
	if ( !valUserName.isString() )
		return false;
	loginParam.m_tstrUserName = A2T(valUserName.asString().c_str());
	// m_tstrPassword
	const Json::Value& valPassword = valParams[ "password" ];
	if ( !valPassword.isString() )
		return false;
	loginParam.m_tstrPassword = A2T(valPassword.asString().c_str());

	return true;
}

bool CRRMsgHandler4Login::_fillLoginParam( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary, CRLoginParam& loginParam ) {
	if ( !pRMsgBinary )
		return false;

	// need more code here.
	return false;
	

	return true;
}


void CRRMsgHandler4Login::_sendSuccessAck( const CRLoginParam& loginParam, const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
	USES_CONVERSION;
	Json::Value ackJsonRoot;
	Json::Value& valParams = ackJsonRoot[ "params" ];
	Json::FastWriter jsonWriter;
	std::string strRMsgAck;
	const CRAccountBase* pAccountObj = NULL;
	CRModuleAccountMgr* pAccountMgr = (CRModuleAccountMgr*)g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_ACCOUNTMGR );
	std::string strTmp;
	tstring_type tstrTmp;

	pAccountObj = pAccountMgr->getAccount( rmsgMetaData.m_sConnect );
	// fill cmd.
	CRRMsgJsonHelper::fillCmd( ackJsonRoot, CRCMDTYPE_ACK_LOGIN, pRMsgJson->m_nCmdSN, pRMsgJson->m_eOSType );
    // fill params.
	valParams[ "result" ] = CRLOGIN_RESULT_SUCCESS;
	if ( !TCHARToUTF8( loginParam.m_tstrUserName, strTmp ) ) {
	    assert( false );
		return;
	}
	valParams[ "username" ] = strTmp;
	if ( pAccountObj ) {
		//
        valParams[ "phone" ] = T2A( pAccountObj->m_regInfo.m_tstrPhoneNum.c_str() );
		//
		if ( !TCHARToUTF8( pAccountObj->m_regInfo.m_tstrEMail, strTmp ) ) {
			assert( false );
			return;
		}
		valParams[ "email" ] = strTmp;
		//
		if ( !TCHARToUTF8( pAccountObj->m_regInfo.m_tstrNickName, strTmp ) ) {
			assert( false );
			return;
		}
		valParams[ "nickname" ] = strTmp;
		//
		valParams[ "sort" ] = (int)pAccountObj->m_regInfo.m_eSortType;
	} else {
	    assert( false );
	}
	//
	strRMsgAck = jsonWriter.write( ackJsonRoot );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsgAck.c_str(), strRMsgAck.length() + 1 );
	
}

void CRRMsgHandler4Login::_sendFailedAck( const CRLoginParam& loginParam, const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson, int nErrCode ) {
	USES_CONVERSION;
	Json::Value ackJsonRoot;
	Json::Value& valParams = ackJsonRoot[ "params" ];
	Json::FastWriter jsonWriter;
	std::string strRMsgAck;

	// fill cmd.
	CRRMsgJsonHelper::fillCmd( ackJsonRoot, CRCMDTYPE_ACK_LOGIN, pRMsgJson->m_nCmdSN, pRMsgJson->m_eOSType );
    // fill params.
	valParams[ "username" ] = T2A( loginParam.m_tstrUserName.c_str() );
	valParams[ "result" ] = CRLOGIN_RESULT_FAILED;
	valParams[ "reason" ] = nErrCode;
	//
	strRMsgAck = jsonWriter.write( ackJsonRoot );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsgAck.c_str(), strRMsgAck.length() + 1 );
}

void CRRMsgHandler4Login::_sendSuccessAck( const CRLoginParam& loginParam, const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgJson ) {

}

void CRRMsgHandler4Login::_sendFailedAck( const CRLoginParam& loginParam, const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgJson, int nErrCode ) {

}





