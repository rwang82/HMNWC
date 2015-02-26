#include "stdafx.h"
#include "CRRMsgHandler4FetchAccountProduct.h"
#include "CRRCmdDefs.h"
#include "CRErrCode.h"
#include "CRSrvMisc.h"
#include "CRServerRoot.h"
#include "CRModuleDepot.h"
#include "CRModuleIdDefs.h"
#include "CRModuleProductMgr.h"
#include "CRMOduleAccountMgr.h"
#include "CRRMsgMaker.h"
#include "HMNWPServer.h"
#include "HMCharConv.h"
#include <string>

CRRMsgHandler4FetchAccountProduct::CRFetchAccountProductResult::CRFetchAccountProductResult() {

}

CRRMsgHandler4FetchAccountProduct::CRFetchAccountProductResult::~CRFetchAccountProductResult() {

}

void CRRMsgHandler4FetchAccountProduct::CRFetchAccountProductResult::_clearAll() {
	name2pl_map_type::iterator itName2PL, iendName2PL;
	product_list_type* pProductList = NULL;
	product_list_type::iterator itProduct, iendProduct;
	CRProduct* pProduct = NULL;

	iendName2PL = m_mapName2ProductList.end();
	for ( itName2PL = m_mapName2ProductList.begin(); itName2PL!=iendName2PL; ++itName2PL ) {
	    pProductList = itName2PL->second;
	    if ( !pProductList )
			continue;
		iendProduct = pProductList->end();
		for ( itProduct = pProductList->begin(); itProduct!=iendProduct; ++itProduct ) {
		    pProduct = *itProduct;
			if ( !pProduct )
				continue;
			delete pProduct;
			pProduct = NULL;
		}
		delete pProduct;
		pProduct = NULL;
	}
	m_mapName2ProductList.clear();
}

CRRMsgHandler4FetchAccountProduct::CRRMsgHandler4FetchAccountProduct() {

}

CRRMsgHandler4FetchAccountProduct::~CRRMsgHandler4FetchAccountProduct() {

}


bool CRRMsgHandler4FetchAccountProduct::_parseParams( const Json::Value& jsonRoot, CRFetchAccountProductParam& fapParam ) {
	const Json::Value& valParams = jsonRoot[ "params" ];
	if ( !valParams.isObject() )
		return false;
	const Json::Value& valUserNameList = valParams[ "username_list" ];
	if ( !valUserNameList.isArray() )
		return false;
	std::string strUTF8;
	utf8_type strTmp;
	//
	int nCount = valUserNameList.size();
	for ( int nIndex = 0; nIndex<nCount; ++nIndex ) {
	    const Json::Value& valItem = valUserNameList[ nIndex ];
		if ( !valItem.isString() )
			continue;
		fapParam.m_containerAccountName.push_back( valItem.asString() );
	}

	return true;
}

void CRRMsgHandler4FetchAccountProduct::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
	CRFetchAccountProductParam fapParam;
	int nErrCode = CRERR_SRV_NONE;
	Json::Value valAccountProductList;
	//
	if ( !_parseParams( pRMsgJson->m_jsonRoot, fapParam ) ) {
	    _sendFailedAck( rmsgMetaData, CRERR_SRV_PARAM_INVALID );
		return;
	}
	//
    if ( !_execute( fapParam, valAccountProductList, nErrCode ) ) {
	    _sendFailedAck( rmsgMetaData, nErrCode );
	}
	//
	_sendSuccessAck( rmsgMetaData, valAccountProductList );
}

bool CRRMsgHandler4FetchAccountProduct::_execute( const CRFetchAccountProductParam& fapParam, Json::Value& valAccountProductList, int& nErrCode ) {
	utf8_container_type::const_iterator citAccountName, ciendAccountName;
	CRModuleProductMgr* pProductMgr = (CRModuleProductMgr*)g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_PRODUCTMGR );
	CRModuleAccountMgr* pAccountMgr = (CRModuleAccountMgr*)g_CRSrvRoot.m_pModuleDepot->getModule( ECRMODULE_ID_ACCOUNTMGR );
	const CRAccountBase* pAccount = NULL;
	const CRAccountData* pAccountData = NULL;
	std::string strUTF8;

	ciendAccountName = fapParam.m_containerAccountName.end();
	for ( citAccountName = fapParam.m_containerAccountName.begin(); citAccountName!=ciendAccountName; ++citAccountName ) {
		pAccount = pAccountMgr->getAccount( *citAccountName, nErrCode );
		if ( !pAccount )
			return false;
		pAccountData = &pAccount->m_data;
		CRFetchAccountProducts fapItem( pAccountData->m_strUserName, 0, pAccountData->m_nCountPublished );

		Json::Value& valProducts = valAccountProductList[ pAccountData->m_strUserName ];
		if ( !pProductMgr->fillAccountProducts2Json( fapItem, valProducts, nErrCode ) )
			return false;
	}

	return true;
}

void CRRMsgHandler4FetchAccountProduct::_sendFailedAck( const CRRMsgMetaData& rmsgMetaData, int nErrCode ) {
	gfnSendFailedAck( rmsgMetaData, CRCMDTYPE_ACK_FETCH_ACCOUNT_PRODUCTS, nErrCode );
}

void CRRMsgHandler4FetchAccountProduct::_sendSuccessAck( const CRRMsgMetaData& rmsgMetaData, Json::Value& valAccountProductList ) {
	Json::Value valParams;
	std::string strRMsg;

	valParams[ "result" ] = 1;
	valParams[ "account_products_list" ] = valAccountProductList;
	
	CRRMsgMaker::createRMsg( valParams, CRCMDTYPE_ACK_FETCH_ACCOUNT_PRODUCTS, strRMsg );

	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}

void CRRMsgHandler4FetchAccountProduct::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}
