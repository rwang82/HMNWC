#include "stdafx.h"
#include "CRAccountAdmin.h"

CRAccountAdmin::CRAccountAdmin(const tstring_type& tstrAccountName, 
		const tstring_type& tstrPassword, 
		const tstring_type& tstrPhoneNum, 
		const tstring_type& tstrEMail)
: CRAccountBase( tstrAccountName, tstrPassword, tstrPhoneNum, tstrEMail ) {

}

CRAccountAdmin::~CRAccountAdmin() {

}

int CRAccountAdmin::getSortType() {
    return 2;
} 