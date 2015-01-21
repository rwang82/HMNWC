#include "stdafx.h"
#include "CRRMsgHandler4ProductPublish.h"
#include "CRModuleProductMgr.h"
#include "CRServerRoot.h"
#include "CRModuleDepot.h"
#include "CRModuleIDDefs.h"
#include "CRErrCode.h"
#include "CRRMsgMaker.h"
#include "HMCharConv.h"
#include "HMNWPServer.h"
#include "CRRCmdDefs.h"
#include <atlconv.h>

CRRMsgHandler4ProductPublish::CRRMsgHandler4ProductPublish() {

}

CRRMsgHandler4ProductPublish::~CRRMsgHandler4ProductPublish() {

}

void CRRMsgHandler4ProductPublish::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
	CRProductPublishParam paramPublishProduct;
	int nErrCode = CRERR_SRV_NONE;
	CRModuleProductMgr* pProductMgr = (CRModuleProductMgr*)g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_PRODUCTMGR );

	if ( !pProductMgr )
		return;

	// fill product/username/requestcode.
	if ( !_parseParams( pRMsgJson->m_jsonRoot, paramPublishProduct ) ) {
		return;
	}
	// fill rmsg meta data.
	paramPublishProduct.m_pRMsgMetaData = &rmsgMetaData;
	// do publish.
	if ( pProductMgr->doPublishProduct( paramPublishProduct, nErrCode ) ) {
	    _sendSuccessAck( paramPublishProduct );
	} else {
	    _sendFailedAck( paramPublishProduct, nErrCode );
	}

}

void CRRMsgHandler4ProductPublish::_sendSuccessAck( const CRProductPublishParam& param ) {
	Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;

	valParams[ "result" ] = 1;
	valParams[ "product_uuid" ] = T2A( param.m_product.m_tstrUUID.c_str() );
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_PRODUCT_PUBLISH, strRMsg );
    //
	g_CRSrvRoot.m_pNWPServer->send( param.m_pRMsgMetaData->m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );

}

void CRRMsgHandler4ProductPublish::_sendFailedAck( const CRProductPublishParam& param, int nErrCode ) {
    Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;

	valParams[ "result" ] = 0;
	valParams[ "reason" ] = nErrCode;
	valParams[ "product_uuid" ] = T2A( param.m_product.m_tstrUUID.c_str() );
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_PRODUCT_PUBLISH, strRMsg );
	//
	g_CRSrvRoot.m_pNWPServer->send( param.m_pRMsgMetaData->m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );

}

void CRRMsgHandler4ProductPublish::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}

bool CRRMsgHandler4ProductPublish::_parseParams( const Json::Value& jsonRoot, CRProductPublishParam& paramPublishProduct ) {
	USES_CONVERSION;
	std::string strUtf8Tmp;
	tstring_type tstrTmp;
	CRProduct& product = paramPublishProduct.m_product;
	
	const Json::Value& valParams = jsonRoot[ "params" ];
	if ( !valParams.isObject() )
		return false;
	// get tstrUserName
	const Json::Value& valUserName = valParams[ "username" ];
	if ( !valUserName.isString() )
		return false;
	strUtf8Tmp = valUserName.asString();
	if ( !UTF8ToTCHAR( (const unsigned char*)strUtf8Tmp.c_str(), strUtf8Tmp.length(), paramPublishProduct.m_tstrUserName ) )
	    return false;
	// 
	const Json::Value& valProduct = valParams[ "product" ];
	if ( !valProduct.isObject() )
		return false;
	// uuid.
	const Json::Value& valUUID = valProduct[ "uuid" ];
	if ( !valUUID.isString() )
		return false;
	strUtf8Tmp = valUUID.asString();
	if ( !UTF8ToTCHAR( (const unsigned char*)strUtf8Tmp.c_str(), strUtf8Tmp.length(), product.m_tstrUUID ) )
		return false;
	// title.
	const Json::Value& valTitle = valProduct[ "title" ];
	if ( !valTitle.isString() )
		return false;
	strUtf8Tmp = valTitle.asString();
	if ( !UTF8ToTCHAR( (const unsigned char*)strUtf8Tmp.c_str(), strUtf8Tmp.length(), product.m_tstrTitle ) )
	    return false;
	// price.
	const Json::Value& valPrice = valProduct[ "price" ];
	if ( !valTitle.isString() )
		return false;
	strUtf8Tmp = valPrice.asString();
	if ( !UTF8ToTCHAR( (const unsigned char*)strUtf8Tmp.c_str(), strUtf8Tmp.length(), product.m_tstrPrice ) )
	    return false;
	// describe.
	const Json::Value& valDescribe = valProduct[ "describe" ];
	if ( !valDescribe.isString() )
		return false;
	strUtf8Tmp = valDescribe.asString();
    if ( !UTF8ToTCHAR( (const unsigned char*)strUtf8Tmp.c_str(), strUtf8Tmp.length(), product.m_tstrDescribe ) )
	    return false;
	// images.
	const Json::Value& valImages = valProduct[ "images" ];
	if ( !valImages.isArray() )
		return false;
	for ( unsigned int i = 0; i<valImages.size(); ++i ) {
		const Json::Value& valImage = valImages[ i ];
		if ( !valImage.isString() )
			return false;
		product.m_containerImages.push_back( A2T( valImage.asString().c_str() ) );
	}
	// keywords.
	const Json::Value& valKeywords = valProduct[ "keywords" ];
	if ( !valKeywords.isArray() )
		return false;
	for ( unsigned int i = 0; i<valKeywords.size(); ++i ) {
	    const Json::Value& valKeyword = valKeywords[ i ];
		if ( !valKeyword.isString() )
			return false;
	    strUtf8Tmp = valDescribe.asString();
		if ( !UTF8ToTCHAR( (const unsigned char*)strUtf8Tmp.c_str(), strUtf8Tmp.length(), tstrTmp ) )
	        return false;
		product.m_containerKeywords.push_back( tstrTmp );
	}

	return true;
}