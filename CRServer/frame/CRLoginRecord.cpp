#include "stdafx.h"
#include "CRLoginRecord.h"
#include "CRErrCode.h"

CRLoginRecord::CRLoginRecord() {

}

CRLoginRecord::~CRLoginRecord() {
	_clearAllLoginInfo();
}

void CRLoginRecord::_clearAllLoginInfo() {
	os2record_map_type::iterator itRecord, iendRecord;
	CRLoginInfo* pLoginInfoTmp = NULL;

	iendRecord = m_mapOS2Record.end();
	for ( itRecord = m_mapOS2Record.begin(); itRecord!=iendRecord; ++itRecord ) {
	    pLoginInfoTmp = itRecord->second;
        delete pLoginInfoTmp;
		pLoginInfoTmp = NULL;
	}
	m_mapOS2Record.clear();
}

bool CRLoginRecord::addRecord( const CRRMsgMetaData& rmsgMetaData, ENUMOSTYPE eOSType, int& nErrCode ) {
    os2record_map_type::iterator itRecord;
	CRLoginInfo* pLoginInfoNew = NULL;

	itRecord = m_mapOS2Record.find( eOSType );
	if ( itRecord != m_mapOS2Record.end() ) {
	    nErrCode = CRERR_SRV_ACCOUNT_LOGINED_INSAMEOS;
		return false;
	}
	pLoginInfoNew = new CRLoginInfo();
	pLoginInfoNew->m_rmsgMetaData = rmsgMetaData;
    m_mapOS2Record[ eOSType ] = pLoginInfoNew;
	return true;
}

bool CRLoginRecord::eraseRecord( const CRRMsgMetaData& rmsgMetaData, ENUMOSTYPE eOSType, int& nErrCode ) {
    os2record_map_type::iterator itRecord;
	CRLoginInfo* pLoginInfo = NULL;

	itRecord = m_mapOS2Record.find( eOSType );
	if ( itRecord == m_mapOS2Record.end() ) {
		nErrCode = CRERR_SRV_ACCOUNT_NOLOGINRECORD;
		return false;
	}
	pLoginInfo = itRecord->second;
	delete pLoginInfo;
	pLoginInfo = NULL;
	m_mapOS2Record.erase( itRecord );
	return true;
}

bool CRLoginRecord::eraseRecord( SOCKET sConnect ) {
	os2record_map_type::iterator itRecord;
	CRLoginInfo* pLoginInfo = NULL;

	for ( itRecord = m_mapOS2Record.begin(); itRecord != m_mapOS2Record.end(); ++itRecord ) {
	    pLoginInfo = itRecord->second;
		if ( pLoginInfo->m_rmsgMetaData.m_sConnect == sConnect ) {
			delete pLoginInfo;
			pLoginInfo = NULL;
		    m_mapOS2Record.erase( itRecord );
			return true;
		}
	}
	return false;
}

bool CRLoginRecord::hasLogin( ENUMOSTYPE eOSType ) const {
	return m_mapOS2Record.find( eOSType ) != m_mapOS2Record.end();
}

bool CRLoginRecord::getLoginInfo( ENUMOSTYPE eOSType, CRLoginInfo& loginInfo ) const {
    os2record_map_type::const_iterator citRecord;

	citRecord = m_mapOS2Record.find( eOSType );
	if ( citRecord == m_mapOS2Record.end() ) {
	    return false;
	}
	loginInfo = *(citRecord->second);
	return true;
}



