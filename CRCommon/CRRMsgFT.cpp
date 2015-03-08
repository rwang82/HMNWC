#include "stdafx.h"
#include "CRRMsgFT.h"
#include "CRRMsgHandlerBase.h"

//CRRMsgFT::CRRMsgFT()
//: m_ucVer( 0 )
//, m_lenMetaData( 0 )
//, m_pBufMetaData( NULL )
//, m_lenPayload( 0 )
//, m_pBufPayload( NULL ) {
//
//}

CRRMsgFT::CRRMsgFT( unsigned char ucVer, const unsigned char* pBufMetaData, __int16 lenMetaData, 
		const unsigned char* pBufPayload, __int32 lenPayload )
: m_ucVer( ucVer )
, m_lenPayload( lenPayload )
, m_pBufPayload( pBufPayload ) {
	Json::Reader reader;
	if ( pBufMetaData && lenMetaData > 0 ) {
	    if ( reader.parse( (char*)pBufMetaData, m_jsonRoot ) ) {
		    _parseMetaData( m_jsonRoot );
		}
	}
}

CRRMsgFT::~CRRMsgFT() {
	// m_pBufPayload don't delete these.
}

bool CRRMsgFT::_parseMetaData( const Json::Value& jsonRoot ) {
	const Json::Value& valCmdNode = jsonRoot[ "cmd" ];
	if ( !valCmdNode.isObject() )
		return false;
	//
	const Json::Value& valType = valCmdNode[ "type" ];
	if ( !valType.isInt() )
		return false;
	m_nCmdType = valType.asInt();
	//
	const Json::Value& valSN = valCmdNode[ "sn" ];
	if ( !valSN.isInt() )
		return false;
	m_nCmdSN = valSN.asInt();
	//
	const Json::Value& valOS = valCmdNode[ "os" ];
	if ( !valOS.isInt() )
		return false;
	m_eOSType = (ENUMOSTYPE)valOS.asInt();

	return true;
}

void CRRMsgFT::_execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler ) {
    pRMsgHandler->accept( rmsgMetaData, this );
}

