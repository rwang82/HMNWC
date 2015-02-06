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
	CRAddAttetion paramAddAttetion;
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

bool CRRMsgHandler4AddAttetion::checkParams( const CRAddAttetion& paramAddAttetion, int& nErrCode ) {
	CRModuleAccountMgr* pAccountMgr = (CRModuleAccountMgr*)g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_ACCOUNTMGR );
	if ( !pAccountMgr )
		return false;

	if ( !pAccountMgr->getAccount( paramAddAttetion.m_tstrDestUserName, nErrCode ) )
		return false;

	if ( !pAccountMgr->getAccount( paramAddAttetion.m_tstrUserName, nErrCode ) )
		return false;

	return true;
}

bool CRRMsgHandler4AddAttetion::execute( const CRAddAttetion& paramAddAttetion, int& nErrCode ) {
    return g_CRSrvRoot.m_pSrvDBProxy->save2DB( &paramAddAttetion, nErrCode );
}

void CRRMsgHandler4AddAttetion::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}

bool CRRMsgHandler4AddAttetion::parseParams( const Json::Value& jsonRoot, CRAddAttetion& paramAddAttetion ) {
	const Json::Value& valParams = jsonRoot[ "params" ];
	std::string strUtf8;
	tstring_type tstrData;

	if ( !valParams.isObject() )
		 return false;
	//
	const Json::Value& valUserName = valParams[ "username" ];
	if ( !valUserName.isString() )
		return false;
	strUtf8 = valUserName.asString();
	if ( !UTF8ToTCHAR( (const unsigned char*)strUtf8.c_str(), strUtf8.size(), tstrData ) )
		return false;
	paramAddAttetion.m_tstrUserName = tstrData;
	//
	const Json::Value& valAttetion = valParams[ "attetion" ];
	if ( !valAttetion.isString() )
		return false;
	strUtf8 = valAttetion.asString();
	if ( !UTF8ToTCHAR( (const unsigned char*)strUtf8.c_str(), strUtf8.size(), tstrData ) )
		return false;
	paramAddAttetion.m_tstrDestUserName = tstrData;

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

void CRRMsgHandler4AddAttetion::sendSuccessAck( const CRRMsgMetaData& rmsgMetaData, const CRAddAttetion& paramAddAttetion ) {
	Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;
	std::string strUtf8;

	valParams[ "result" ] = 1;
	if ( !TCHARToUTF8( paramAddAttetion.m_tstrDestUserName, strUtf8 ) ) {
	    assert( false );
		return;
	}
	valParams[ "attetion" ] = strUtf8.c_str();
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_ADD_ATTETION, strRMsg );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}