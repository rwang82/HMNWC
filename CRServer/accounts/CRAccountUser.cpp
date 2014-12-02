#include "stdafx.h"
#include "CRAccountUser.h"

CRAccountUser::CRAccountUser(const tstring_type& tstrAccountName, 
		const tstring_type& tstrPassword, 
		const tstring_type& tstrPhoneNum, 
		const tstring_type& tstrEMail)
: CRAccountBase( tstrAccountName, tstrPassword, tstrPhoneNum, tstrEMail ) {

}

CRAccountUser::~CRAccountUser() {

}

int CRAccountUser::getSortType() {
    return 1;
}