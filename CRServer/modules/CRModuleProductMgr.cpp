#include "stdafx.h"
#include "CRModuleProductMgr.h"

CRModuleProductMgr::CRModuleProductMgr() {

}

CRModuleProductMgr::~CRModuleProductMgr() {

}

bool CRModuleProductMgr::doPublishProduct( const CRProductPublishParam& paramPublishProduct, int& nErrCode ) {

	return m_productDepot.addProduct2Pend( &paramPublishProduct.m_product, nErrCode );
}
//

bool CRModuleProductMgr::fillAccountProducts2Json( const CRFetchAccountProducts& fapParam, Json::Value& valProducts, int& nErrCode ) {
	return m_productDepot.fillAccountProducts2Json( fapParam, valProducts, nErrCode );
}