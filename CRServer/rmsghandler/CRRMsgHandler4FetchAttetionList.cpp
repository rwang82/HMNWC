#include "stdafx.h"
#include "CRRMsgHandler4FetchAttetionList.h"
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

CRRMsgHandler4FetchAttetionList::CRRMsgHandler4FetchAttetionList() {

}

CRRMsgHandler4FetchAttetionList::~CRRMsgHandler4FetchAttetionList() {

}
	
void CRRMsgHandler4FetchAttetionList::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
	CRFetchAttetionRecordListParam paramFARL;
	CRModuleAttetionRecord* pModuleAttetionRecord = NULL;
	CRAttetionRecordList listRecords;
	int nErrCode = CRERR_SRV_NONE;
	
	// get pModuleAttetionRecord.
	pModuleAttetionRecord = (CRModuleAttetionRecord*)g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_ATTETIONRECORD );
	if ( !pModuleAttetionRecord ) {
		_sendFailedAck( rmsgMetaData, CRERR_SRV_NONE );
		return;
	}
	// get paramFARL.
	if ( !_parseParams( pRMsgJson->m_jsonRoot, paramFARL ) ) {
		_sendFailedAck( rmsgMetaData, CRERR_SRV_PARAM_INVALID );
		return;
	}
	//
	if ( !pModuleAttetionRecord->doFetchRecords( paramFARL, listRecords, nErrCode ) ) {
	    _sendFailedAck( rmsgMetaData, nErrCode );
		return;
	}

	//
	_sendSuccessAck( rmsgMetaData, paramFARL.m_tstrAccountName, listRecords );
}

void CRRMsgHandler4FetchAttetionList::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}

bool CRRMsgHandler4FetchAttetionList::_parseParams( const Json::Value& jsonRoot, CRFetchAttetionRecordListParam& param ) {
    const Json::Value& valParams = jsonRoot[ "params" ];
	std::string strUtf8;

	param.m_eFetchMode = CRFetchAttetionRecordListParam::EFM_ATTETION;
	//
	const Json::Value& valUserName = valParams[ "username" ];
	if ( !valUserName.isString() )
		return false;
	strUtf8 = valUserName.asString();
	if ( !UTF8ToTCHAR( strUtf8, param.m_tstrAccountName ) )
		return false;
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

void CRRMsgHandler4FetchAttetionList::_sendSuccessAck( const CRRMsgMetaData& rmsgMetaData, const tstring_type& tstrAccountName, const CRAttetionRecordList& listRecords ) {
    Json::Value valParams;
	std::string strRMsg;
	std::string strUTF8;

	valParams[ "result" ] = 1;
	if ( !TCHARToUTF8( tstrAccountName, strUTF8 ) )
		return;
	valParams[ "username" ] = strUTF8;
	Json::Value& valAttetions = valParams[ "attetions" ];
	//
	for ( CRAttetionRecord* pRecord : listRecords.m_listAttetionRecords ) {
		if ( !TCHARToUTF8( pRecord->m_tstrUserNameTo, strUTF8 ) )
			return;
	    valAttetions.append( strUTF8.c_str() );
	}
	//
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_FETCH_ATTETION_LIST, strRMsg );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}

void CRRMsgHandler4FetchAttetionList::_sendFailedAck( const CRRMsgMetaData& rmsgMetaData, int nErrCode ) {
	gfnSendFailedAck( rmsgMetaData, CRCMDTYPE_ACK_FETCH_ATTETION_LIST, nErrCode );
}





















