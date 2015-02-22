#include "stdafx.h"
#include "CRAttetionRecord.h"
#include "CRDBImplBase.h"

CRAttetionRecord::CRAttetionRecord() {

}

CRAttetionRecord::~CRAttetionRecord() {

}
	
bool CRAttetionRecord::save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const {
	return pDBImpl->doSave( this, nErrCode );
}
