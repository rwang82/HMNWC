#include "stdafx.h"
#include "CRModuleAttetionRecord.h"

CRModuleAttetionRecord::CRModuleAttetionRecord() {

}

CRModuleAttetionRecord::~CRModuleAttetionRecord() {

}

bool CRModuleAttetionRecord::doFetchRecords( const CRFetchAttetionRecordListParam& param, CRAttetionRecordList& listRecords, int& nErrCode ) {
    return m_depotAttetionRecord.getRecords( param, listRecords, nErrCode );
}