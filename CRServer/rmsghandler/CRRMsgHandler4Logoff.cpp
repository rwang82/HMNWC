#include "stdafx.h"
#include "CRRMsgHandler4Logoff.h"
#include "CRRMsg.h"
#include "CRRMsgJsonHelper.h"
#include "CRRCmdDefs.h"
#include "CRServerRoot.h"
#include "CRModuleAccountMgr.h"
#include "CRModuleDepot.h"
#include "CRModuleIDDefs.h"
#include "HMNWPServer.h"
#include <atlconv.h>
//
const int CRLOGOFF_ERR_UNKNOWN = 0;
const int CRLOGOFF_ERR_INVALIDPARAMS = 1;
const int CRLOGOFF_RESULT_SUCCESS = 1;
const int CRLOGOFF_RESULT_FAILED = 0;
//
CRLogoffParam::CRLogoffParam()
: m_strUserName( "" )
, m_pRMsgMetaData( NULL )
, m_eOSType( EOS_UNKNOWN ) {

}

CRLogoffParam::~CRLogoffParam() {

}
//
CRRMsgHandler4Logoff::CRRMsgHandler4Logoff() {

}

CRRMsgHandler4Logoff::~CRRMsgHandler4Logoff() {

}
	
void CRRMsgHandler4Logoff::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
	int nErrCode = CRLOGOFF_ERR_UNKNOWN;
	CRLogoffParam logoffParam;
	
	if ( !_fillLogoffParam( rmsgMetaData, pRMsgJson, logoffParam ) ) {
		nErrCode = CRLOGOFF_ERR_INVALIDPARAMS;
		_sendResultAck( rmsgMetaData, pRMsgJson, logoffParam.m_strUserName, false, nErrCode );
		return;
	}
	//
	if ( _doLogoff( logoffParam, nErrCode ) ) {
		_sendResultAck( rmsgMetaData, pRMsgJson, logoffParam.m_strUserName, true );
	} else {
		_sendResultAck( rmsgMetaData, pRMsgJson, logoffParam.m_strUserName, false, nErrCode );
	}
}

void CRRMsgHandler4Logoff::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}

bool CRRMsgHandler4Logoff::_fillLogoffParam( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson, CRLogoffParam& logoffParam ) {
    if ( !pRMsgJson )
		return false;
	// m_pRMsgMetaData.
	logoffParam.m_pRMsgMetaData = &rmsgMetaData;
	// m_eOSType.
    logoffParam.m_eOSType = pRMsgJson->m_eOSType;
	// m_strUserName.
	const Json::Value& valParams = pRMsgJson->m_jsonRoot[ "params" ];
	if ( !valParams.isObject() )
		return false;
	const Json::Value& valUserName = valParams[ "username" ];
	if ( !valUserName.isString() )
		return false;
	logoffParam.m_strUserName = valUserName.asString();
	return true;
}

bool CRRMsgHandler4Logoff::_doLogoff( const CRLogoffParam& logoffParam, int& nErrCode ) {
	CRModuleAccountMgr* pModuleAccountMgr = NULL;
	nErrCode = CRLOGOFF_ERR_UNKNOWN;
		
	pModuleAccountMgr = dynamic_cast< CRModuleAccountMgr* >( g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_ACCOUNTMGR ) );
	if ( !pModuleAccountMgr )
		return false;

	return pModuleAccountMgr->doLogoff( logoffParam, nErrCode );
}

void CRRMsgHandler4Logoff::_sendResultAck( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson, const utf8_type& strUserName, bool bSuccess, int nErrCode ) {
	USES_CONVERSION;
	Json::Value ackJsonRoot;
	Json::Value& valParams = ackJsonRoot[ "params" ];
	Json::FastWriter jsonWriter;
	std::string strRMsgAck;

	// fill cmd.
	CRRMsgJsonHelper::fillCmd( ackJsonRoot, CRCMDTYPE_ACK_LOGOFF, pRMsgJson->m_nCmdSN, pRMsgJson->m_eOSType );
    // fill params.
	valParams[ "username" ] = strUserName;
	valParams[ "result" ] = bSuccess ? CRLOGOFF_RESULT_SUCCESS : CRLOGOFF_RESULT_FAILED;
	//
	strRMsgAck = jsonWriter.write( ackJsonRoot );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsgAck.c_str(), strRMsgAck.length() + 1 );
	
}

void CRRMsgHandler4Logoff::_sendResultAck( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgJson, const utf8_type& strUserName, bool bSuccess, int nErrCode ) {

}









