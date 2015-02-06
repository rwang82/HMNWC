#include "stdafx.h"
#include "CRAccountUser.h"
#include "CRTypes.h"
#include "CRDBImplBase.h"

CRAccountUser::CRAccountUser(const CRAccountData& paramAccountReg)
: CRAccountBase( paramAccountReg ) {

}

CRAccountUser::~CRAccountUser() {

}

int CRAccountUser::getSortType() {
    return EACCOUNT_SORT_USER;
}

bool CRAccountUser::save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const{
	return pDBImpl->doSave( this, nErrCode );
}

bool CRAccountUser::loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode ) {
	return pDBImpl->doLoad( pParamKey, *this, nErrCode );
}
