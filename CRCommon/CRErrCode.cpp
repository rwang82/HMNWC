#include "stdafx.h"
#include "CRErrCode.h"
#include "CRErrCodeDepot.h"
#include "MemFuncPack.h"
#include "HMTSHelper.h"
#include "tchar.h"
#include <assert.h>
#include <map>
#include <string>
//
class CRErrCodeDepot {
	typedef int errcode_type;
	typedef std::basic_string< TCHAR > tstring_type;
	typedef std::map< errcode_type, tstring_type > errcode2decribe_map_type;
public:
	CRErrCodeDepot(){};
	~CRErrCodeDepot(){};
	static CRErrCodeDepot* getInstance();

public:
	bool regErrCode( int nErrCode, const tstring_type& tstrErrDescribe );
	bool getErrDescribe( int nErrCode, tstring_type& tstrErrDescribe ) const;

private:
	bool _hasErrCode( int nErrCode );

private:
	HMTSHelper m_tsAccess;
	errcode2decribe_map_type m_mapErrCode2Describe;
};

CRErrCodeDepot* CRErrCodeDepot::getInstance() {
	static CRErrCodeDepot s_instance;
	return &s_instance;
};

bool CRErrCodeDepot::regErrCode( int nErrCode, const tstring_type& tstrErrDescribe ) {
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );
	
	if ( _hasErrCode( nErrCode ) ) {
	    assert( false );
		return false;
	}

	m_mapErrCode2Describe[ nErrCode ] = tstrErrDescribe;
	return true;
}

bool CRErrCodeDepot::getErrDescribe( int nErrCode, tstring_type& tstrErrDescribe ) const {
	if ( !m_tsAccess.safeEnterFunc() )
		return false;
	CMemFuncPack mfpkSafeExit( &m_tsAccess, &HMTSHelper::safeExitFunc );

	errcode2decribe_map_type::const_iterator citErrItem;

	citErrItem = m_mapErrCode2Describe.find( nErrCode );
	if ( citErrItem != m_mapErrCode2Describe.end() )
		return false;

	tstrErrDescribe = citErrItem->second;
	return true;
}

bool CRErrCodeDepot::_hasErrCode( int nErrCode ) {
    return m_mapErrCode2Describe.find( nErrCode ) != m_mapErrCode2Describe.end();
}

/////////////////////////////////////////////////////////////////////////////////////
static const int CRERR_CLI_BEGIN = 10000;
static const int CRERR_SRV_BEGIN = 60000;
/////////////////////////////////////////////////////////////////////////////////////
// client error code.
const int CRERR_CLI_NONE = CRERR_CLI_BEGIN + 0;

//CRErrCodeDepot::getInstance()->regErrCode( 1, _T("dafsfda") );


/////////////////////////////////////////////////////////////////////////////////////
// server error code.
const int CRERR_SRV_NONE = CRERR_SRV_BEGIN + 0;
const int CRERR_SRV_ACCOUNTNAME_EXIST = CRERR_SRV_BEGIN + 1;
const int CRERR_SRV_ACCOUNTNAME_ISNOT_EXIST = CRERR_SRV_BEGIN + 2;
const int CRERR_SRV_ACCOUNT_INVALID = CRERR_SRV_BEGIN + 3;
const int CRERR_SRV_ACCOUNT_PASSWORD_INCORRECT = CRERR_SRV_BEGIN + 4;
const int CRERR_SRV_ACCOUNT_LOGINED_INSAMEOS = CRERR_SRV_BEGIN + 5;
const int CRERR_SRV_ACCOUNT_NOLOGINRECORD = CRERR_SRV_BEGIN + 6;
const int CRERR_SRV_ACCOUNT_LOGOFF_NOTSAMESESSION = CRERR_SRV_BEGIN + 7;
const int CRERR_SRV_DB_NOTREADY = CRERR_SRV_BEGIN + 30;
const int CRERR_SRV_PARAM_INVALID = CRERR_SRV_BEGIN + 50;


























