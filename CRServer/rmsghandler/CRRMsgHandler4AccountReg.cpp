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
#include <atlconv.h>

CRRMsgHandler4AccountReg::CRRMsgHandler4AccountReg() {

}

CRRMsgHandler4AccountReg::~CRRMsgHandler4AccountReg() {

}

void CRRMsgHandler4AccountReg::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
    assert( pRMsgJson );
	CRModuleAccountMgr* pModuleAccountMgr = NULL;
	CRAccountRegParam paramAccountReg;
	int nErrCode = CRERR_SRV_NONE;

	pModuleAccountMgr = (CRModuleAccountMgr*)g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_ACCOUNTMGR );
	if ( !pModuleAccountMgr ) {
		return;
	}
	if ( !_parseParams( pRMsgJson->m_jsonRoot, paramAccountReg ) ) {
	    return;
	}
	if ( pModuleAccountMgr->doRegAccount( paramAccountReg, nErrCode ) ) {
	    _sendSuccessAck( rmsgMetaData );
	} else {
	    _sendFailedAck( rmsgMetaData, nErrCode );
	}
}

void CRRMsgHandler4AccountReg::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}


void CRRMsgHandler4AccountReg::_sendSuccessAck( const CRRMsgMetaData& rmsgMetaData ) {
	Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;

	valParams[ "result" ] = 1;
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_ACCOUNT_REG, strRMsg );
    //
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}

void CRRMsgHandler4AccountReg::_sendFailedAck( const CRRMsgMetaData& rmsgMetaData, int nErrCode ) {
	Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;

	valParams[ "result" ] = 0;
	valParams[ "reason" ] = nErrCode;
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_ACCOUNT_REG, strRMsg );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}

bool CRRMsgHandler4AccountReg::_parseParams( const Json::Value& jsonRoot, CRAccountRegParam& paramAccountReg ) {
	USES_CONVERSION;

	const Json::Value& valParams = jsonRoot[ "params" ];
	if ( !valParams.isObject() )
		return false;
	// get tstrAccountName.
	const Json::Value& valUserName = valParams[ "username" ];
	if ( !valUserName.isString() )
		return false;
	paramAccountReg.m_tstrUserName = A2T( valUserName.asString().c_str() );
	// get tstrPassword
	const Json::Value& valPassword = valParams[ "password" ];
	if ( !valPassword.isString() )
		return false;
	paramAccountReg.m_tstrPassword = A2T( valPassword.asString().c_str() );
	// get nSortType
	const Json::Value& valSort = valParams[ "sort" ];
	if ( !valSort.isInt() )
		return false;
    paramAccountReg.m_eSortType = (ENUMACCOUNTSORT)valSort.asInt();
	// get tstrPhoneNum
	const Json::Value& valPhone = valParams[ "phone" ];
	if ( !valPhone.isString() )
		return false;
	paramAccountReg.m_tstrPhoneNum = A2T( valPhone.asString().c_str() );
	// get tstrEMail
	const Json::Value& valEMail = valParams[ "email" ];
	if ( !valEMail.isString() )
		return false;
	paramAccountReg.m_tstrEMail = A2T( valEMail.asString().c_str() );

	return true;
}




