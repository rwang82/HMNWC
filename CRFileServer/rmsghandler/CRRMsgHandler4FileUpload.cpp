#include "stdafx.h"
#include "CRRMsgHandler4FileUpload.h"
#include "CRRMsgFT.h"
#include "CRFileSrvApp.h"
#include "CRSrvRoot.h"
#include "CRFSSettings.h"
#include "CRFTMsgMaker.h"
#include "CRRMsgMaker.h"
#include "CRRCmdDefs.h"
#include "HMCharConv.h"
#include "Funcpack.h"
#include <assert.h>
//
extern CRFileSrvApp g_srvApp;
extern CRSrvRoot g_srvRoot;
//
CRFUParam::CRFUParam()
: m_strOwner( "" )
, m_strFId( "" )
, m_uPosStart( 0 )
, m_uSegment( 0 )
, m_uTotalSize( 0 ) {

}

CRFUParam::~CRFUParam() {
}
//
CRRMsgHandler4FileUpload::CRRMsgHandler4FileUpload() {

}

CRRMsgHandler4FileUpload::~CRRMsgHandler4FileUpload() {

}

void CRRMsgHandler4FileUpload::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgFT* pRMsgFT ) {
	CRFUParam fuParam;
	const Json::Value& valParams = pRMsgFT->m_jsonRoot[ "params" ];

	if ( !_parseFUParam( valParams, fuParam ) )
	    return;
	
	if ( !_saveFile( &fuParam, pRMsgFT ) )
		return;

	// send success ack.
	_sendSuccessAck( pRMsgFT->m_nCmdSN, rmsgMetaData, fuParam );
}

bool CRRMsgHandler4FileUpload::_saveFile( const CRFUParam* pFUParam, const CRRMsgFT* pRMsgFT ) {
    tstring_type tstrAccountDir;
    tstring_type tstrFilePathSave;
	tstring_type tstrFileName;
	DWORD dwWritten;
	
	if ( !_createAccountDir( pFUParam, tstrAccountDir ) )
		return false;
	//
	if ( !UTF8ToTCHAR( pFUParam->m_strFId, tstrFileName ) )
		return false;
	tstrFilePathSave = tstrAccountDir + _T("/") + tstrFileName;
	//
	HANDLE hDestFile = ::CreateFile( tstrFilePathSave.c_str(),  GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( INVALID_HANDLE_VALUE == hDestFile )
		return false;
	CFuncPack fpkCloseHandle( ::CloseHandle, hDestFile );
	
	// modify write start position.
	::SetFilePointer( hDestFile, pFUParam->m_uPosStart, NULL, FILE_BEGIN );
    // write data.
	return ( TRUE == ::WriteFile( hDestFile, pRMsgFT->m_pBufPayload, pFUParam->m_uSegment, &dwWritten, NULL ) );

}

bool CRRMsgHandler4FileUpload::_createAccountDir( const CRFUParam* pFUParam, tstring_type& tstrAccountDir ) {
	tstring_type tstrOwner;
	BOOL bSuccess;

	if ( !UTF8ToTCHAR( pFUParam->m_strOwner, tstrOwner ) )
		return false;

	tstrAccountDir = g_srvApp.m_pFSSettings->m_tstrFileDepotDir + _T("\\") + tstrOwner;
	
	if ( _taccess( tstrAccountDir.c_str(), 0 ) == 0 )
		return true;

	bSuccess = ::CreateDirectory( tstrAccountDir.c_str(), NULL );
	if ( bSuccess )
		return true;
	DWORD dwErrCode = ::GetLastError();
	return dwErrCode == ERROR_ALREADY_EXISTS;
}

bool CRRMsgHandler4FileUpload::_parseFUParam( const Json::Value& valParams, CRFUParam& fuParam ) {
	//
	const Json::Value& valOwner = valParams[ "owner" ];
	if ( !valOwner.isString() )
		return false;
	fuParam.m_strOwner = valOwner.asString();
	//
	const Json::Value& valFId = valParams[ "fid" ];
	if ( !valFId.isString() )
		return false;
	fuParam.m_strFId = valFId.asString();
	//
	const Json::Value& valStart = valParams[ "start" ];
	if ( !valStart.isInt() )
		return false;
	fuParam.m_uPosStart = valStart.asInt();
	//
	const Json::Value& valSegment = valParams[ "segment" ];
	if ( !valSegment.isInt() )
		return false;
	fuParam.m_uSegment = valSegment.asInt();
	//
	const Json::Value& valTotalSize = valParams[ "total" ];
	if ( !valTotalSize.isInt() )
		return false;
	fuParam.m_uTotalSize = valTotalSize.asInt();

	return true;
}

void CRRMsgHandler4FileUpload::_sendSuccessAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, const CRFUParam& fuParam ) {
	Json::Value valParams;
	unsigned char* pBufFTMsg = NULL;
	unsigned int uLenBufFTMsg = 0;
	std::string strRMsg;

	valParams[ "result" ] = 1;
	valParams[ "reason" ] = 0;
	valParams[ "owner" ] = fuParam.m_strOwner;
	valParams[ "fid" ] = fuParam.m_strFId;
	valParams[ "start" ] = fuParam.m_uPosStart;
	valParams[ "segment" ] = fuParam.m_uSegment;
	valParams[ "total" ] = fuParam.m_uTotalSize;
	//
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_FILE_UPLOAD, nCmdSN, strRMsg );
	//
	CRRMsgFT rmsgFT( 1, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1, NULL, 0 );
	//
	if ( !CRFTMsgMaker::buildFTMsg( rmsgFT, &pBufFTMsg, uLenBufFTMsg ) ) {
	    assert( false );
		return;
	}
	CFuncPack fpkDelBufFTMsg( ::gfnDelBuf< unsigned char >, pBufFTMsg );

	//
	g_srvRoot.m_nwpServer.send( rmsgMetaData.m_sConnect, pBufFTMsg, uLenBufFTMsg );
}

void CRRMsgHandler4FileUpload::_sendFailedAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, const CRFUParam& fuParam ) {

}