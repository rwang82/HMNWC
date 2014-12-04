#include "stdafx.h"
#include "CRAccountAdmin.h"
#include "CRErrCode.h"
#include "CRTypes.h"

CRAccountAdmin::CRAccountAdmin(const CRAccountRegParam& paramAccountReg)
: CRAccountBase( paramAccountReg ) {

}

CRAccountAdmin::~CRAccountAdmin() {

}

int CRAccountAdmin::getSortType() {
    return EACCOUNT_SORT_ADMIN;
} 
