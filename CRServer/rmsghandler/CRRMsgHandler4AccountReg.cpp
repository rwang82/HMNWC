#include "stdafx.h"
#include "CRRMsgHandler4AccountReg.h"
#include "CRRMsg.h"
#include "CRAccountAdmin.h"
#include "CRAccountUser.h"
#include "CRAccountDepot.h"
#include "CRServerRoot.h"
#include "HMNWPServer.h"
#include "CRRMsgMaker.h"
#include "CRErrCode.h"
#include "CRRCmdDefs.h"
#include <atlconv.h>

CRRMsgHandler4AccountReg::CRRMsgHandler4AccountReg() {

}

CRRMsgHandler4AccountReg::~CRRMsgHandler4AccountReg() {

}

void CRRMsgHandler4AccountReg::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
	tstring_type tstrAccountName;
	tstring_type tstrPassword;
	int nSortType;
	tstring_type tstrPhoneNum;
	tstring_type tstrEMail;

	if ( !_parseParams( pRMsgJson, tstrAccountName, tstrPassword, nSortType, tstrPhoneNum, tstrEMail ) )
		return;

	if ( g_CRSrvRoot.m_pAccountDepot->addAccount( new CRAccountUser( tstrAccountName, tstrPassword, tstrPhoneNum, tstrEMail ) ) ) {
	    _sendSuccessAck( rmsgMetaData, tstrAccountName );
	} else {
	    _sendFailedAck( rmsgMetaData, tstrAccountName, CRERR_SRV_ACCOUNTNAME_EXIST );
	}
}

void CRRMsgHandler4AccountReg::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}

bool CRRMsgHandler4AccountReg::_parseParams( const CRRMsgJson* pRMsgJson
	, tstring_type& tstrAccountName
	, tstring_type& tstrPassword
	, int& nSortType
	, tstring_type& tstrPhoneNum
	, tstring_type& tstrEMail ) {
	USES_CONVERSION;
	if ( !pRMsgJson )
		return false;
	const Json::Value& valParams = pRMsgJson->m_jsonRoot[ "params" ];
	if ( !valParams.isObject() )
		return false;
	// get tstrAccountName.
	const Json::Value& valUserName = valParams[ "username" ];
	if ( !valUserName.isString() )
		return false;
	tstrAccountName = A2T( valUserName.asString().c_str() );
	// get tstrPassword
	const Json::Value& valPassword = valParams[ "password" ];
	if ( !valPassword.isString() )
		return false;
	tstrPassword = A2T( valPassword.asString().c_str() );
	// get nSortType
	const Json::Value& valSort = valParams[ "sort" ];
	if ( !valSort.isInt() )
		return false;
    nSortType = valSort.asInt();
	// get tstrPhoneNum
	const Json::Value& valPhone = valParams[ "phone" ];
	if ( !valPhone.isString() )
		return false;
	tstrPhoneNum = A2T( valPhone.asString().c_str() );
	// get tstrEMail
	const Json::Value& valEMail = valParams[ "email" ];
	if ( !valEMail.isString() )
		return false;
	tstrEMail = A2T( valEMail.asString().c_str() );

	return true;
}

void CRRMsgHandler4AccountReg::_sendSuccessAck( const CRRMsgMetaData& rmsgMetaData, const tstring_type& tstrAccountName ) {
	Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;

	valParams[ "username" ] = T2A( tstrAccountName.c_str() );
	valParams[ "result" ] = 1;
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_ACCOUNT_REG, strRMsg );
    //
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}

void CRRMsgHandler4AccountReg::_sendFailedAck( const CRRMsgMetaData& rmsgMetaData, const tstring_type& tstrAccountName, int nErrCode ) {
	Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;

	valParams[ "username" ] = T2A( tstrAccountName.c_str() );
	valParams[ "result" ] = 0;
	valParams[ "reason" ] = nErrCode;
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_ACCOUNT_REG, strRMsg );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}