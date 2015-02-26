#include "stdafx.h"
#include "CRProduct.h"
#include "CRDBImplBase.h"

CRProduct::CRProduct() {
	m_strUUID = "";
    m_strTitle = "";
	m_strPrice = "";
	m_strDescribe = "";
	m_nSortType = -1;
	m_strUDSort = "";
	m_nPassStatus = 0;
}

CRProduct::CRProduct( const CRProduct& val ) {
	utf8_container_type::const_iterator citStr, ciendStr;

	//
	m_strUUID = val.m_strUUID;
	m_strTitle = val.m_strTitle;
	m_strPrice = val.m_strPrice;
	m_strDescribe = val.m_strDescribe;
	m_nSortType = val.m_nSortType;
	m_strUDSort = val.m_strUDSort;
	//
	ciendStr = val.m_containerImages.end();
	for ( citStr = val.m_containerImages.begin(); citStr!=ciendStr; ++citStr ) {
	    m_containerImages.push_back( citStr->c_str() );
	}
	//
	ciendStr = val.m_containerKeywords.end();
	for ( citStr = val.m_containerKeywords.begin(); citStr!=ciendStr; ++citStr ) {
	    m_containerKeywords.push_back( citStr->c_str() );
	}
}

bool CRProduct::save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const {
	return pDBImpl->doSave( this, nErrCode );
}

bool CRProduct::loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode ) {
    return pDBImpl->doLoad( pParamKey, *this, nErrCode );
}


