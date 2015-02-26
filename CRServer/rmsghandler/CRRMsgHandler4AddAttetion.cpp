#include "stdafx.h"
#include "CRRMsgHandler4AddAttetion.h"
#include "CRRMsg.h"
#include "CRRMsgMaker.h"
#include "CRServerRoot.h"
#include "CRSrvDBProxy.h"
#include "CRRCmdDefs.h"
#include "CRErrCode.h"
#include "CRModuleDepot.h"
#include "CRModuleAccountMgr.h"
#include "CRModuleIDDefs.h"
#include "HMNWPServer.h"
#include "HMCharConv.h"
#include "json/json.h"
#include <atlconv.h>

CRRMsgHandler4AddAttetion::CRRMsgHandler4AddAttetion() {

}

CRRMsgHandler4AddAttetion::~CRRMsgHandler4AddAttetion() {

}

void CRRMsgHandler4AddAttetion::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
	CRAttetionRecord paramAddAttetion;
	int nErrCode = CRERR_SRV_NONE;

	if ( !parseParams( pRMsgJson->m_jsonRoot, paramAddAttetion ) ) {
		sendFailedAck( rmsgMetaData, CRERR_SRV_PARAM_INVALID );
		return;
	}
	if ( !checkParams( paramAddAttetion, nErrCode ) ) {
		sendFailedAck( rmsgMetaData, nErrCode );
		return;
	}

	if ( !execute( paramAddAttetion, nErrCode ) ) {
	    sendFailedAck( rmsgMetaData, nErrCode );
		return;
	}

	sendSuccessAck( rmsgMetaData, paramAddAttetion );
}

bool CRRMsgHandler4AddAttetion::checkParams( const CRAttetionRecord& paramAddAttetion, int& nErrCode ) {
	CRModuleAccountMgr* pAccountMgr = (CRModuleAccountMgr*)g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_ACCOUNTMGR );
	if ( !pAccountMgr )
		return false;

	if ( !pAccountMgr->getAccount( paramAddAttetion.m_strUserNameTo, nErrCode ) )
		return false;

	if ( !pAccountMgr->getAccount( paramAddAttetion.m_strUserNameFrom, nErrCode ) )
		return false;

	return true;
}

bool CRRMsgHandler4AddAttetion::execute( const CRAttetionRecord& paramAddAttetion, int& nErrCode ) {
    return g_CRSrvRoot.m_pSrvDBProxy->save2DB( &paramAddAttetion, nErrCode );
}

void CRRMsgHandler4AddAttetion::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}

bool CRRMsgHandler4AddAttetion::parseParams( const Json::Value& jsonRoot, CRAttetionRecord& paramAddAttetion ) {
	const Json::Value& valParams = jsonRoot[ "params" ];
	std::string strUtf8;
	utf8_type strData;

	if ( !valParams.isObject() )
		 return false;
	//
	const Json::Value& valUserName = valParams[ "username" ];
	if ( !valUserName.isString() )
		return false;
	paramAddAttetion.m_strUserNameFrom = valUserName.asString();
	//
	const Json::Value& valAttetion = valParams[ "attetion" ];
	if ( !valAttetion.isString() )
		return false;
	paramAddAttetion.m_strUserNameTo = valAttetion.asString();

	return true;
}

void CRRMsgHandler4AddAttetion::sendFailedAck( const CRRMsgMetaData& rmsgMetaData, int nErrCode ) {
	Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;

	valParams[ "result" ] = 0;
	valParams[ "reason" ] = nErrCode;
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_ADD_ATTETION, strRMsg );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}

void CRRMsgHandler4AddAttetion::sendSuccessAck( const CRRMsgMetaData& rmsgMetaData, const CRAttetionRecord& paramAddAttetion ) {
	Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;
	std::string strUtf8;

	valParams[ "result" ] = 1;
	valParams[ "attetion" ] = paramAddAttetion.m_strUserNameTo;
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_ADD_ATTETION, strRMsg );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}