#include "stdafx.h"
#include "CRAttetionRecordDepot.h"
#include "CRServerRoot.h"
#include "CRSrvDBProxy.h"

CRAttetionRecordDepot::CRAttetionRecordDepot() {

}

CRAttetionRecordDepot::~CRAttetionRecordDepot() {

}

bool CRAttetionRecordDepot::getRecords( const CRFetchAttetionRecordListParam& param, CRAttetionRecordList& listRecords, int& nErrCode ) {
    
	return g_CRSrvRoot.m_pSrvDBProxy->loadFromDB( (void*)&param, &listRecords, nErrCode );
}


