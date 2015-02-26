#include "stdafx.h"
#include "CRRMsgHandler4FetchAccountInfo.h"
#include "HMCharConv.h"
#include "CRServerRoot.h"
#include "CRModuleDepot.h"
#include "CRModuleIDDefs.h"
#include "CRModuleAccountMgr.h"
#include "CRAccountDepot.h"
#include "CRErrCode.h"
#include "CRRCmdDefs.h"
#include "CRSrvMisc.h"
#include "CRRMsgMaker.h"
#include "CRServerRoot.h"
#include "HMNWPServer.h"
#include "HMCharConv.h"
#include "Json/json.h"
#include <atlconv.h>

CRRMsgHandler4FetchAccountInfo::CRRMsgHandler4FetchAccountInfo() {

}

CRRMsgHandler4FetchAccountInfo::~CRRMsgHandler4FetchAccountInfo() {

}
	
void CRRMsgHandler4FetchAccountInfo::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
	CRFetchAccountInfoParam fetchAccountInfoParam;
	CRAccountDepot::accountdata_container_type containerAccountData;
	//
	if ( !_parseParams( pRMsgJson->m_jsonRoot, fetchAccountInfoParam ) ) {
	    _sendFailedAck( rmsgMetaData, CRERR_SRV_PARAM_INVALID );
		return;
	}
	//
	CRModuleAccountMgr* pModuleAccountMgr = (CRModuleAccountMgr*)g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_ACCOUNTMGR );
	if ( !pModuleAccountMgr ) {
	    assert( false );
		return;
	}
	pModuleAccountMgr->getAccountsData( fetchAccountInfoParam.m_containerAccountName, containerAccountData );
	//
	_sendSuccessAck( rmsgMetaData, containerAccountData );
}

void CRRMsgHandler4FetchAccountInfo::_sendSuccessAck( const CRRMsgMetaData& rmsgMetaData, CRAccountDepot::accountdata_container_type containerAccountData ) {
    Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;
	std::string strUtf8;
	CRAccountDepot::accountdata_container_type::const_iterator citAccountData, ciendAccountData;

	valParams[ "result" ] = 1;
	Json::Value& valAccountInfoList = valParams[ "account_info_list" ];
	ciendAccountData = containerAccountData.end();
	for ( citAccountData = containerAccountData.begin(); citAccountData!=ciendAccountData; ++citAccountData ) {
	    Json::Value valItem;
		//
		valItem[ "username" ] = citAccountData->m_strUserName;
		valItem[ "phone" ] = citAccountData->m_strPhoneNum;
		valItem[ "email" ] = citAccountData->m_strEMail;
		valItem[ "nickname" ] = citAccountData->m_strNickName;
		valItem[ "sort" ] = citAccountData->m_eSortType;
		valItem[ "attetioned" ] = citAccountData->m_nCountAttetioned;
        valItem[ "attetion" ] = citAccountData->m_nCountAttetion;
		valItem[ "published" ] = citAccountData->m_nCountPublished;
		//
		valAccountInfoList.append( valItem );
	}
	//
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_FETCH_ACCOUNT_INFO, strRMsg );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );

}

void CRRMsgHandler4FetchAccountInfo::_sendFailedAck( const CRRMsgMetaData& rmsgMetaData, int nErrCode ) {
    gfnSendFailedAck( rmsgMetaData, CRCMDTYPE_ACK_FETCH_ACCOUNT_INFO, nErrCode );
}

void CRRMsgHandler4FetchAccountInfo::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}

bool CRRMsgHandler4FetchAccountInfo::_parseParams( Json::Value jsonRoot, CRFetchAccountInfoParam& param ) {
    utf8_type strAccountName;
	
	const Json::Value& valParams = jsonRoot[ "params" ];
	if ( !valParams.isObject() )
		return false;
    const Json::Value& valAccountNames = valParams[ "username_list" ];
	if ( !valAccountNames.isArray() )
		return false;
	int nCount = valAccountNames.size();
	for ( int nIndex = 0; nIndex<nCount; ++nIndex ) {
	    const Json::Value& valAccountName = valAccountNames[ nIndex ];
		if ( !valAccountName.isString() )
            return false;
		param.m_containerAccountName.push_back( valAccountName.asString() );
	}
    
	return true;
}