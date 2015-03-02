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
#include "CRModuleDepot.h"
#include "CRModuleIdDefs.h"
#include "CRModuleAccountMgr.h"
#include "HMCharConv.h"
#include <atlconv.h>

CRRMsgHandler4AccountReg::CRRMsgHandler4AccountReg() {

}

CRRMsgHandler4AccountReg::~CRRMsgHandler4AccountReg() {

}

void CRRMsgHandler4AccountReg::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
    assert( pRMsgJson );
	CRModuleAccountMgr* pModuleAccountMgr = NULL;
	CRAccountData paramAccountReg;
	int nErrCode = CRERR_SRV_NONE;

	pModuleAccountMgr = (CRModuleAccountMgr*)g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_ACCOUNTMGR );
	if ( !pModuleAccountMgr ) {
		return;
	}
	if ( !_parseParams( pRMsgJson->m_jsonRoot, paramAccountReg ) ) {
	    return;
	}
	if ( pModuleAccountMgr->doRegAccount( paramAccountReg, nErrCode ) ) {
	    _sendSuccessAck( pRMsgJson->m_nCmdSN, rmsgMetaData );
	} else {
	    _sendFailedAck( pRMsgJson->m_nCmdSN, rmsgMetaData, nErrCode );
	}
}

void CRRMsgHandler4AccountReg::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}


void CRRMsgHandler4AccountReg::_sendSuccessAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData ) {
	Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;

	valParams[ "result" ] = 1;
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_ACCOUNT_REG, nCmdSN, strRMsg );
    //
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}

void CRRMsgHandler4AccountReg::_sendFailedAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, int nErrCode ) {
	Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;

	valParams[ "result" ] = 0;
	valParams[ "reason" ] = nErrCode;
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_ACCOUNT_REG, nCmdSN, strRMsg );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}

bool CRRMsgHandler4AccountReg::_parseParams( const Json::Value& jsonRoot, CRAccountData& paramAccountReg ) {
	const Json::Value& valParams = jsonRoot[ "params" ];
	if ( !valParams.isObject() )
		return false;
	// get strAccountName.
	const Json::Value& valUserName = valParams[ "username" ];
	if ( !valUserName.isString() )
		return false;
	paramAccountReg.m_strUserName = valUserName.asString();
	// get strPassword
	const Json::Value& valPassword = valParams[ "password" ];
	if ( !valPassword.isString() )
		return false;
	paramAccountReg.m_strPassword = valPassword.asString();
	// get nSortType
	const Json::Value& valSort = valParams[ "sort" ];
	if ( !valSort.isInt() )
		return false;
    paramAccountReg.m_eSortType = (ENUMACCOUNTSORT)valSort.asInt();
	// get strPhoneNum
	const Json::Value& valPhone = valParams[ "phone" ];
	if ( !valPhone.isString() )
		return false;
	paramAccountReg.m_strPhoneNum = valPhone.asString();
	// get strNickName
	const Json::Value& valNickName = valParams[ "nickname" ];
	if ( !valNickName.isString() )
		return false;
	paramAccountReg.m_strNickName = valNickName.asString();
	// get strEMail
	const Json::Value& valEMail = valParams[ "email" ];
	if ( !valEMail.isString() )
		return false;
	paramAccountReg.m_strEMail = valEMail.asString();

	return true;
}




