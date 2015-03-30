#include "stdafx.h"
#include "CRFSClientStub.h"
#include "CRSrvRoot.h"
#include "CRRMsgHandlerDepot.h"
#include "HMEndianConv.h"
////
//#define MINSIZE_RMSGFT (1+2+0+4+0)
//
CRFSClientStub::CRFSClientStub( CRSrvRoot* pSrvRoot, SOCKET sConnect, const sockaddr_in& sAddr )
: CRClientStub( pSrvRoot, sConnect, sAddr ) {

}

CRFSClientStub::~CRFSClientStub() {

}
	
void CRFSClientStub::onRMsg( const CRRMsgRaw& rmsgRaw ) {
	//CRRMsgFT* pRMsgFT = _parseRMsgFT( rmsgRaw.m_pRawBuf, rmsgRaw.m_uLenRawBuf );
	//if ( !pRMsgFT )
	//	return;
	//CRRMsgHandlerBase* pRMsgHandler = m_pSrvRoot->m_rmsgHandlerDepot.getRMsgHandler( pRMsgFT->m_nCmdType );
	//if ( !pRMsgHandler )
	//	return;
	//pRMsgFT->execute( rmsgRaw.m_metaData, pRMsgHandler, this );
}
//
//CRRMsgFT* CRFSClientStub::_parseRMsgFT( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
//    if ( uLenRawBuf < MINSIZE_RMSGFT || !pRawBuf )
//		return NULL;
//	bool bLE = isLittleEndian();
//	const unsigned char* pPosStart = pRawBuf;
//	// get ucVer
//	unsigned char ucVer = pPosStart[ 0 ];
//    ++pPosStart;
//	// get lenMetaData
//	__int16 lenMetaData = *((__int16*)pPosStart);
//	if ( bLE ) {
//	    BE2LE( lenMetaData );
//	}
//	pPosStart += 2;
//	// get pBufMetaData.
//	const unsigned char* pBufMetaData = pPosStart;
//	pPosStart += lenMetaData;
//	// get lenPayload
//	__int32 lenPayload = *((__int32*)pPosStart);
//    if ( bLE ) {
//	    BE2LE( lenPayload );
//	}
//	pPosStart += lenPayload;
//	// get pBufPayload.
//	const unsigned char* pBufPayload = pPosStart;
//
//	return new CRRMsgFT( ucVer, pBufMetaData, lenMetaData, pBufPayload, lenPayload );
//}