#include "stdafx.h"
#include "CRProduct.h"
#include "CRDBImplBase.h"

CRProduct::CRProduct() {
	m_tstrUUID = _T("");
    m_tstrTitle = _T("");
	m_tstrPrice = _T("");
	m_tstrDescribe = _T("");
	m_nSortType = -1;
	m_tstrUDSort = _T("");
	m_nPassStatus = 0;
}

CRProduct::CRProduct( const CRProduct& val ) {
	tstr_container_type::const_iterator citStr, ciendStr;

	//
	m_tstrUUID = val.m_tstrUUID;
	m_tstrTitle = val.m_tstrTitle;
	m_tstrPrice = val.m_tstrPrice;
	m_tstrDescribe = val.m_tstrDescribe;
	m_nSortType = val.m_nSortType;
	m_tstrUDSort = val.m_tstrUDSort;
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


