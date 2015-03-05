#include "stdafx.h"
#include "CRRMsgHandler4FetchAttetionedList.h"
#include "CRRMsg.h"
#include "CRSrvMisc.h"
#include "CRRCmdDefs.h"
#include "CRErrCode.h"
#include "CRModuleAttetionRecord.h"
#include "CRServerRoot.h"
#include "CRModuleDepot.h"
#include "CRModuleIDDefs.h"
#include "CRAttetionRecord.h"
#include "CRRMsgMaker.h"
#include "CRServerRoot.h"
#include "HMCharConv.h"
#include "HMNWPServer.h"

CRRMsgHandler4FetchAttetionedList::CRRMsgHandler4FetchAttetionedList() {

}

CRRMsgHandler4FetchAttetionedList::~CRRMsgHandler4FetchAttetionedList() {

}
	
void CRRMsgHandler4FetchAttetionedList::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
	CRFetchAttetionRecordListParam paramFARL;
	CRModuleAttetionRecord* pModuleAttetionRecord = NULL;
	CRAttetionRecordList listRecords;
	int nErrCode = CRERR_SRV_NONE;
	
	// get pModuleAttetionRecord.
	pModuleAttetionRecord = (CRModuleAttetionRecord*)g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_ATTETIONRECORD );
	if ( !pModuleAttetionRecord ) {
		_sendFailedAck( pRMsgJson->m_nCmdSN, rmsgMetaData, CRERR_SRV_NONE );
		return;
	}
	// get paramFARL.
	if ( !_parseParams( pRMsgJson->m_jsonRoot, paramFARL ) ) {
		_sendFailedAck( pRMsgJson->m_nCmdSN, rmsgMetaData, CRERR_SRV_PARAM_INVALID );
		return;
	}
	//
	if ( !pModuleAttetionRecord->doFetchRecords( paramFARL, listRecords, nErrCode ) ) {
	    _sendFailedAck( pRMsgJson->m_nCmdSN, rmsgMetaData, nErrCode );
		return;
	}

	//
	_sendSuccessAck( pRMsgJson->m_nCmdSN, rmsgMetaData, paramFARL.m_strAccountName, listRecords );
}

bool CRRMsgHandler4FetchAttetionedList::_parseParams( const Json::Value& jsonRoot, CRFetchAttetionRecordListParam& param ) {
    const Json::Value& valParams = jsonRoot[ "params" ];
	std::string strUtf8;

	param.m_eFetchMode = CRFetchAttetionRecordListParam::EFM_ATTETIONED;
	//
	const Json::Value& valUserName = valParams[ "username" ];
	if ( !valUserName.isString() )
		return false;
	param.m_strAccountName = valUserName.asString();
	//
	const Json::Value& valIndexStart = valParams[ "index_start" ];
	if ( !valIndexStart.isInt() )
		return false;
	param.m_uIndexStart = valIndexStart.asInt();
	//
	const Json::Value& valCount = valParams[ "count" ];
	if ( !valCount.isInt() )
		return false;
	param.m_uCount = valCount.asInt();
	//
	return true;
}

void CRRMsgHandler4FetchAttetionedList::_sendSuccessAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, const utf8_type& strAccountName, const CRAttetionRecordList& listRecords ) {
    Json::Value valParams;
	std::string strRMsg;
	std::string strUTF8;

	valParams[ "result" ] = 1;
	valParams[ "username" ] = strAccountName;
	Json::Value& valAttetions = valParams[ "attetioneds" ];
	//
	for ( CRAttetionRecord* pRecord : listRecords.m_listAttetionRecords ) {
	    valAttetions.append( pRecord->m_strUserNameFrom );
	}
	//
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_FETCH_ATTETIONED_LIST, nCmdSN, strRMsg );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}

void CRRMsgHandler4FetchAttetionedList::_sendFailedAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, int nErrCode ) {
	gfnSendFailedAck( rmsgMetaData, CRCMDTYPE_ACK_FETCH_ATTETIONED_LIST, nCmdSN, nErrCode );
}





















