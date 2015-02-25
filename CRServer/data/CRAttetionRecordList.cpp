#include "stdafx.h"
#include "CRAttetionRecordList.h"
#include "CRDBImplBase.h"
#include "CRAttetionRecord.h"
//
CRFetchAttetionRecordListParam::CRFetchAttetionRecordListParam()
: m_eFetchMode( EFM_ATTETION )
, m_tstrAccountName( _T("") )
, m_uIndexStart( 0 )
, m_uCount( 0 ) {
}
//
CRAttetionRecordList::CRAttetionRecordList() {
}

CRAttetionRecordList::~CRAttetionRecordList() {
	_clearAllRecords();
}
	
bool CRAttetionRecordList::loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode ) {
	return pDBImpl->doLoad( pParamKey, *this, nErrCode );
}

void CRAttetionRecordList::_clearAllRecords() {
    attetionrecord_list_type::iterator itRecord, iendRecord;
	CRAttetionRecord* pRecord = NULL;

	iendRecord = m_listAttetionRecords.end();
	for ( itRecord = m_listAttetionRecords.begin(); itRecord!=iendRecord; ++itRecord ) {
	    pRecord = *itRecord;
		delete pRecord;
		pRecord = NULL;
	}
	m_listAttetionRecords.clear();
}

//attetionrecord_list_type m_listAttetionRecords;