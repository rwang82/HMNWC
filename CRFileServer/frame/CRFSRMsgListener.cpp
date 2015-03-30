#include "stdafx.h"
#include "CRFSRMsgListener.h"
#include "CRRCmdDefs.h"
#include "CRRMsgHandler4FileUpload.h"
#include "CRRMsgHandler4FetchFileMetaData.h"
#include "CRRMsgHandler4FileDownload.h"
#include "CRFTMsgParser.h"
#include "FuncPack.h"
//
#define CMDHANDLER_ADD( cmd_type, cmm_handler_cls ) \
	do { \
        m_rmsgHandlerDepot.regRMsgHandler( cmd_type, new cmm_handler_cls() ); \
	} while( 0 )
//
CRFSRMsgListener::CRFSRMsgListener() {
	_initRMHD();
}

CRFSRMsgListener::~CRFSRMsgListener() {

}

void CRFSRMsgListener::onAccept( CRSrvRoot* pSrvRoot, const CRRMsgMetaData& rmsgMetaData ) const {

}

void CRFSRMsgListener::onDisConnect( CRSrvRoot* pSrvRoot, const CRRMsgMetaData& rmsgMetaData ) const {

}

void CRFSRMsgListener::onRMsg( CRSrvRoot* pSrvRoot, const CRRMsgRaw& rmsgRaw ) const {
	CRRMsgFT* pRMsgFT = CRFTMsgParser::parseFTMsg( rmsgRaw.m_pRawBuf, rmsgRaw.m_uLenRawBuf );
    if ( !pRMsgFT )
		return;
	CFuncPack fpkDelRMsgFT( ::gfnDelObj< CRRMsgFT >, pRMsgFT );
	//
	CRRMsgHandlerBase* pRMsgHandler = m_rmsgHandlerDepot.getRMsgHandler( pRMsgFT->m_nCmdType );
	if ( !pRMsgHandler )
		return;
	//
	pRMsgFT->execute( rmsgRaw.m_metaData, pRMsgHandler );
}

void CRFSRMsgListener::_initRMHD() {
    CMDHANDLER_ADD( CRCMDTYPE_REQ_FILE_UPLOAD, CRRMsgHandler4FileUpload );
	CMDHANDLER_ADD( CRCMDTYPE_REQ_FETCH_FILE_METADATA, CRRMsgHandler4FetchFileMetaData );
	CMDHANDLER_ADD( CRCMDTYPE_REQ_FILE_DOWNLOAD, CRRMsgHandler4FileDownload );
}




