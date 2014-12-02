#include "stdafx.h"
#include "CRRMsgParser.h"
#include "CRRMsg.h"
#include "FuncPack.h"
#include "json/json.h"
#include "atlconv.h"
#include <assert.h>
////////////////////////////////////////////////////////////
// CRRMsgJson.
static bool isMatchCRRMsgJson( const unsigned char* pRawBuf, unsigned int uLenRawBuf );
static CRRMsgJson* createCRRMsgJson( const unsigned char* pRawBuf, unsigned int uLenRawBuf );
////////////////////////////////////////////////////////////
// CRRMsgXML.
////////////////////////////////////////////////////////////
// CRRMsgBinary.
static bool isMatchCRRMsgBinary( const unsigned char* pRawBuf, unsigned int uLenRawBuf );
static CRRMsgBinary* createCRRMsgBinary( const unsigned char* pRawBuf, unsigned int uLenRawBuf );

CRRMsgParser::CRRMsgParser() {

}

CRRMsgParser::~CRRMsgParser() {

}

CRRMsgBase* CRRMsgParser::createRMsg( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
	if ( !pRawBuf || uLenRawBuf == 0 ) 
	   return NULL;
	bool bRes = false;
	CRRMsgBase* pRMsgNew = NULL;

	// check if it match CRRMsgJson.
	if ( isMatchCRRMsgJson( pRawBuf, uLenRawBuf ) ){
		pRMsgNew = createCRRMsgJson( pRawBuf, uLenRawBuf );
	    if ( pRMsgNew ) {
			return pRMsgNew;
		} else {
		    goto check_CRRMsgBinary;
		}
		assert( false );
		return false;
	} 

	// check if it match CRRMsgXML.


	
check_CRRMsgBinary:
	// check if it match CRRMsgBinary.
	if ( isMatchCRRMsgBinary( pRawBuf, uLenRawBuf ) ) {
	    pRMsgNew = createCRRMsgBinary( pRawBuf, uLenRawBuf );
		assert( pRMsgNew );
		return pRMsgNew;
	}


	//
	assert( false );
	return NULL;
}


bool isMatchCRRMsgJson( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
    assert( pRawBuf && uLenRawBuf > 0 );
	return pRawBuf[ 0 ] == '{';
}

CRRMsgJson* createCRRMsgJson( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
	if ( !pRawBuf || uLenRawBuf == 0 ) 
	   return NULL;
	assert( pRawBuf[0] == '{' ); //
	Json::Reader jsonReader;
	USES_CONVERSION;
	CRRMsgJson* pRMsgJson = NULL;

	//
	pRMsgJson = new CRRMsgJson();
	CFuncPack fpkRMsgJson( ::gfnDelObj<CRRMsgJson>, pRMsgJson );
	//
	if ( !jsonReader.parse( (const char*)pRawBuf, pRMsgJson->m_jsonRoot ) )
		return NULL;
	Json::Value& valCmdNode = pRMsgJson->m_jsonRoot[ "cmd" ];
	if ( !valCmdNode.isObject() )
		return NULL;
	//
	Json::Value& valType = valCmdNode[ "type" ];
	if ( !valType.isInt() )
		return NULL;
	pRMsgJson->m_nCmdType = valType.asInt();
	//
	Json::Value& valSN = valCmdNode[ "sn" ];
	if ( !valSN.isInt() )
		return NULL;
	pRMsgJson->m_nCmdSN = valSN.asInt();
	//
	Json::Value& valOS = valCmdNode[ "os" ];
	if ( !valOS.isInt() )
		return NULL;
	pRMsgJson->m_eOSType = (ENUMOSTYPE)valOS.asInt();
	//
	fpkRMsgJson.Cancel();
	return pRMsgJson;
}


bool isMatchCRRMsgBinary( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
    return false;
}

CRRMsgBinary* createCRRMsgBinary( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) {
    return NULL;
}