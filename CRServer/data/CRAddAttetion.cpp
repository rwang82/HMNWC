#include "stdafx.h"
#include "CRAddAttetion.h"
#include "CRDBImplBase.h"

CRAddAttetion::CRAddAttetion() {

}

CRAddAttetion::~CRAddAttetion() {

}
	
bool CRAddAttetion::save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const {
	return pDBImpl->doSave( this, nErrCode );
}

bool CRAddAttetion::loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode ) {

	return false;
}