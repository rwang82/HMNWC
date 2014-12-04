#include "stdafx.h"
#include "CRAccountUser.h"
#include "CRTypes.h"

CRAccountUser::CRAccountUser(const CRAccountRegParam& paramAccountReg)
: CRAccountBase( paramAccountReg ) {

}

CRAccountUser::~CRAccountUser() {

}

int CRAccountUser::getSortType() {
    return EACCOUNT_SORT_USER;
}
