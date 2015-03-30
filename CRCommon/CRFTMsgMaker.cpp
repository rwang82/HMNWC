#include "stdafx.h"
#include "CRFTMsgMaker.h"
#include "FuncPack.h"
#include "HMEndianConv.h"
#include "HMDataAccess.h"
#include <assert.h>

CRFTMsgMaker::CRFTMsgMaker() {

}

CRFTMsgMaker::~CRFTMsgMaker() {

}

bool CRFTMsgMaker::buildFTMsg( const CRRMsgFT& rmsgFT, unsigned char** ppBufFTMsg, unsigned int& uLenBufFTMsg ) {
	Json::FastWriter jsonWriter;
	unsigned char* pBufFTMsg = NULL;
	unsigned char* pPosStart = NULL;
	int nLenMetaData = 0;
	int nLenPayload = 0;

	std::string strJsonMetaData = jsonWriter.write( rmsgFT.m_jsonRoot );
	nLenMetaData = strJsonMetaData.length() + 1;
    uLenBufFTMsg = 1 + 4 + nLenMetaData + 4 + rmsgFT.m_lenPayload;
	pBufFTMsg = new unsigned char[ uLenBufFTMsg ];
	CFuncPack fpkDelBuf( ::gfnDelBuf<unsigned char>, pBufFTMsg );
	pPosStart = pBufFTMsg;
	//
	HM_BYTE_STORE_AND_MOVE( 1, pPosStart );
	//
	nLenMetaData = strJsonMetaData.length() + 1;
	if ( isLittleEndian() ) {
	   LE2BE( nLenMetaData );
	}
	HM_INT32_STORE_AND_MOVE( nLenMetaData, pPosStart );
	//
	nLenMetaData = strJsonMetaData.length() + 1;
	memcpy_s( pPosStart, nLenMetaData, strJsonMetaData.c_str(), nLenMetaData );
	pPosStart += nLenMetaData;
	//
	nLenPayload = rmsgFT.m_lenPayload;
	HM_INT32_STORE_AND_MOVE( nLenPayload, pPosStart );
	//
	memcpy_s( pPosStart, nLenPayload, rmsgFT.m_pBufPayload, nLenPayload );

	//
	*ppBufFTMsg = pBufFTMsg;
	fpkDelBuf.Cancel();
	return true;
}


