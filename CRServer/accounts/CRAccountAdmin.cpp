#include "stdafx.h"
#include "CRAccountAdmin.h"
#include "CRErrCode.h"
#include "CRTypes.h"
#include "CRDBImplBase.h"

CRAccountAdmin::CRAccountAdmin(const CRAccountData& paramAccountReg)
: CRAccountBase( paramAccountReg ) {

}

CRAccountAdmin::~CRAccountAdmin() {

}

int CRAccountAdmin::getSortType() {
    return EACCOUNT_SORT_ADMIN;
} 

bool CRAccountAdmin::save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const{
	return pDBImpl->doSave( this, nErrCode );
}

bool CRAccountAdmin::loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode ) {
	return pDBImpl->doLoad( pParamKey, *this, nErrCode );
}