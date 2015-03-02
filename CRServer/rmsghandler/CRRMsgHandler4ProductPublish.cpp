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
	    _sendSuccessAck( pRMsgJson->m_nCmdSN, paramPublishProduct );
	} else {
	    _sendFailedAck( pRMsgJson->m_nCmdSN, paramPublishProduct, nErrCode );
	}

}

void CRRMsgHandler4ProductPublish::_sendSuccessAck( int nCmdSN, const CRProductPublishParam& param ) {
	Json::Value valParams;
	std::string strRMsg;

	valParams[ "result" ] = 1;
	valParams[ "product_uuid" ] = param.m_product.m_strUUID;
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_PRODUCT_PUBLISH, nCmdSN, strRMsg );
    //
	g_CRSrvRoot.m_pNWPServer->send( param.m_pRMsgMetaData->m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );

}

void CRRMsgHandler4ProductPublish::_sendFailedAck( int nCmdSN, const CRProductPublishParam& param, int nErrCode ) {
    Json::Value valParams;
	USES_CONVERSION;
	std::string strRMsg;

	valParams[ "result" ] = 0;
	valParams[ "reason" ] = nErrCode;
	valParams[ "product_uuid" ] = param.m_product.m_strUUID;
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_PRODUCT_PUBLISH, nCmdSN, strRMsg );
	//
	g_CRSrvRoot.m_pNWPServer->send( param.m_pRMsgMetaData->m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );

}

void CRRMsgHandler4ProductPublish::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}

bool CRRMsgHandler4ProductPublish::_parseParams( const Json::Value& jsonRoot, CRProductPublishParam& paramPublishProduct ) {
	USES_CONVERSION;
	std::string strUtf8Tmp;
	utf8_type strTmp;
	CRProduct& product = paramPublishProduct.m_product;
	
	const Json::Value& valParams = jsonRoot[ "params" ];
	if ( !valParams.isObject() )
		return false;
	// get strUserName
	const Json::Value& valUserName = valParams[ "username" ];
	if ( !valUserName.isString() )
		return false;
	product.m_strPublisher = valUserName.asString();
	// 
	const Json::Value& valProduct = valParams[ "product" ];
	if ( !valProduct.isObject() )
		return false;
	// uuid.
	const Json::Value& valUUID = valProduct[ "uuid" ];
	if ( !valUUID.isString() )
		return false;
	product.m_strUUID = valUUID.asString();
	// title.
	const Json::Value& valTitle = valProduct[ "title" ];
	if ( !valTitle.isString() )
		return false;
	product.m_strTitle = valTitle.asString();
	// price.
	const Json::Value& valPrice = valProduct[ "price" ];
	if ( !valPrice.isString() )
		return false;
	product.m_strPrice = valPrice.asString();
	// describe.
	const Json::Value& valDescribe = valProduct[ "describe" ];
	if ( !valDescribe.isString() )
		return false;
	product.m_strDescribe = valDescribe.asString();
	// sort.
	const Json::Value& valSort = valProduct[ "sort" ];
	if ( !valSort.isInt() )
		return false;
	product.m_nSortType = valSort.asInt();
	// user define sort.
	if ( product.m_nSortType == -1 ) {
	    const Json::Value& valUDSort = valProduct["udsort"];
		if ( !valUDSort.isString() )
			return false;
		product.m_strUDSort = valUDSort.asString();
	}
	// images.
	const Json::Value& valImages = valProduct[ "images" ];
	if ( !valImages.isArray() )
		return false;
	for ( unsigned int i = 0; i<valImages.size(); ++i ) {
		const Json::Value& valImage = valImages[ i ];
		if ( !valImage.isString() )
			return false;
		product.m_containerImages.push_back( valImage.asString() );
	}
	// keywords.
	const Json::Value& valKeywords = valProduct[ "keywords" ];
	if ( !valKeywords.isArray() )
		return false;
	for ( unsigned int i = 0; i<valKeywords.size(); ++i ) {
	    const Json::Value& valKeyword = valKeywords[ i ];
		if ( !valKeyword.isString() )
			return false;
		product.m_containerKeywords.push_back( valDescribe.asString() );
	}

	return true;
}