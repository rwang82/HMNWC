#include "stdafx.h"
#include "CRFSRMsgListener.h"
#include "CRRCmdDefs.h"
#include "CRRMsgHandler4FileUpload.h"
#include "CRRMsgHandler4FetchFileMetaData.h"
#include "CRRMsgHandler4FileDownload.h"
#include "HMEndianConv.h"
#include "FuncPack.h"
//
#define MINSIZE_RMSGFT (1+2+0+4+0)
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
	CRRMsgFT* pRMsgFT = _createRMsgFT( rmsgRaw.m_pRawBuf, rmsgRaw.m_uLenRawBuf );
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

CRRMsgFT* CRFSRMsgListener::_createRMsgFT( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
    if ( uLenRawBuf < MINSIZE_RMSGFT || !pRawBuf )
		return NULL;
	bool bLE = isLittleEndian();
	const unsigned char* pPosStart = pRawBuf;
	// get ucVer
	unsigned char ucVer = pPosStart[ 0 ];
    ++pPosStart;
	// get lenMetaData
	__int16 lenMetaData = *((__int16*)pPosStart);
	if ( bLE ) {
	    BE2LE( lenMetaData );
	}
	pPosStart += 2;
	// get pBufMetaData.
	const unsigned char* pBufMetaData = pPosStart;
	pPosStart += lenMetaData;
	// get lenPayload
	__int32 lenPayload = *((__int32*)pPosStart);
    if ( bLE ) {
	    BE2LE( lenPayload );
	}
	pPosStart += lenPayload;
	// get pBufPayload.
	const unsigned char* pBufPayload = pPosStart;

	return new CRRMsgFT( ucVer, pBufMetaData, lenMetaData, pBufPayload, lenPayload );
}

void CRFSRMsgListener::_initRMHD() {
    CMDHANDLER_ADD( CRCMDTYPE_REQ_FILE_UPLOAD, CRRMsgHandler4FileUpload );
	CMDHANDLER_ADD( CRCMDTYPE_REQ_FETCH_FILE_METADATA, CRRMsgHandler4FileUpload );
	CMDHANDLER_ADD( CRCMDTYPE_REQ_FILE_DOWNLOAD, CRRMsgHandler4FileDownload );
}




