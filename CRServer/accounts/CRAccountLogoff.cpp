#include "stdafx.h"
#include "CRAccountLogoff.h"
#include "CRErrCode.h"
#include "CRTypes.h"

CRAccountLogoff::CRAccountLogoff(const CRAccountRegParam& paramAccountReg)
: CRAccountBase( paramAccountReg ){

}

CRAccountLogoff::~CRAccountLogoff() {

}

int CRAccountLogoff::getSortType() {
    return EACCOUNT_SORT_UNKNOWN;
}

bool CRAccountLogoff::doLogin( const CRLoginParam& loginParam, int& nErrCode ) {
    assert( false );
	nErrCode = CRERR_SRV_ACCOUNT_INVALID;
	return false;
}

void CRAccountLogoff::doLogoff( const CRLogoffParam& logoffParam, int& nErrCode ) {
    assert( false );
	nErrCode = CRERR_SRV_ACCOUNT_INVALID;
	return;
}

