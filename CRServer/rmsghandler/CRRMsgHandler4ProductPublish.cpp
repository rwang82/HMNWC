#include "stdafx.h"
#include "CRRMsgHandler4ProductPublish.h"
#include <atlconv.h>

CRRMsgHandler4ProductPublish::CRRMsgHandler4ProductPublish() {

}

CRRMsgHandler4ProductPublish::~CRRMsgHandler4ProductPublish() {

}

void CRRMsgHandler4ProductPublish::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
	CRProduct product;
	int nReqCode;

	if ( !_parseParams( pRMsgJson->m_jsonRoot, product, nReqCode ) ) {
		return;
	}

	int a = 0;
}

void CRRMsgHandler4ProductPublish::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}

bool CRRMsgHandler4ProductPublish::_parseParams( const Json::Value& jsonRoot, CRProduct& paramProduct, int& nReqestCode ) {
	USES_CONVERSION;
	tstring_type tstrUserName;
	
	const Json::Value& valParams = jsonRoot[ "params" ];
	if ( !valParams.isObject() )
		return false;
	// get tstrUserName
	const Json::Value& valUserName = valParams[ "username" ];
	if ( !valUserName.isString() )
		return false;
	tstrUserName = A2T( valUserName.asString().c_str() );
	// 
	const Json::Value& valProduct = valParams[ "product" ];
	if ( !valProduct.isObject() )
		return false;
	// title.
	const Json::Value& valTitle = valProduct[ "title" ];
	if ( !valTitle.isString() )
		return false;
	paramProduct.m_tstrTitle = A2T( valTitle.asString().c_str() );
	// price.
	const Json::Value& valPrice = valProduct[ "price" ];
	if ( !valTitle.isString() )
		return false;
	paramProduct.m_tstrPrice = A2T( valPrice.asString().c_str() );
	// describe.
	const Json::Value& valDescribe = valProduct[ "describe" ];
	if ( !valDescribe.isString() )
		return false;
	paramProduct.m_tstrDescribe = A2T( valDescribe.asString().c_str() );
	// images.
	const Json::Value& valImages = valProduct[ "images" ];
	if ( !valImages.isArray() )
		return false;
	for ( unsigned int i = 0; i<valImages.size(); ++i ) {
		const Json::Value& valImage = valImages[ i ];
		if ( !valImage.isString() )
			return false;
		paramProduct.m_containerImages.push_back( A2T( valImage.asString().c_str() ) );
	}
	// keywords.
	const Json::Value& valKeywords = valProduct[ "keywords" ];
	if ( !valKeywords.isArray() )
		return false;
	for ( unsigned int i = 0; i<valKeywords.size(); ++i ) {
	    const Json::Value& valKeyword = valKeywords[ i ];
		if ( !valKeyword.isString() )
			return false;
		paramProduct.m_containerKeywords.push_back( A2T( valKeyword.asString().c_str() ) );
	}

	//request_code
	const Json::Value& valReqCode = valParams[ "request_code" ];
	if ( !valReqCode.isInt() )
		return false;
	nReqestCode = valReqCode.asInt();

	return true;
}