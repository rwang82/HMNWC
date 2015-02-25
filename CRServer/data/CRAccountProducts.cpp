#include "stdafx.h"
#include "CRAccountProducts.h"
#include "CRDBImplBase.h"

CRAccountProducts::CRAccountProducts() {

}

CRAccountProducts::~CRAccountProducts() {
	m_listProduct.clear();
}

bool CRAccountProducts::loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode ) {
    return pDBImpl->doLoad( pParamKey, *this, nErrCode );
}


