#include "stdafx.h"
#include "CRAccountList.h"
#include "CRDBImplBase.h"

CRAccountList::CRAccountList() {

}

CRAccountList::~CRAccountList() {
    m_containerAccount.clear();
}

bool CRAccountList::loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode ) {
	return pDBImpl->doLoad( pParamKey, *this, nErrCode );
}