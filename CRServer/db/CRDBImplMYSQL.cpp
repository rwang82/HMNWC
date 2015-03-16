#include "stdafx.h"
#include "CRDBImplMYSQL.h"
#include "CRAccountUser.h"
#include "CRAccountAdmin.h"
#include "CRProduct.h"
#include "CRAttetionRecord.h"
#include "CRAccountList.h"
#include "CRAttetionRecordList.h"
#include "CRAccountProducts.h"
#include "CRMisc.h"
#include "CRErrCode.h"
#include "CRLog.h"
#include "HMCharConv.h"
#include "FuncPack.h"
#include <string>
#include <atlconv.h>
//
#define CRDBMYSQL_FLAG_NONE (0x00000000)
#define CRDBMYSQL_FLAG_CONNECTED2DB (0x00000001)
//
enum ENUMCRDBMYSQLACCOUNTUSERFIELD {
	CRDBMYSQL_ACCOUNTUSER_FIELD_USERNAME = 0,
    CRDBMYSQL_ACCOUNTUSER_FIELD_PASSWORD,
    CRDBMYSQL_ACCOUNTUSER_FIELD_PHONENUM,
    CRDBMYSQL_ACCOUNTUSER_FIELD_EMAIL,
    CRDBMYSQL_ACCOUNTUSER_FIELD_NICKNAME,
    CRDBMYSQL_ACCOUNTUSER_FIELD_SORTTYPE,
	CRDBMYSQL_ACCOUNTUSER_FIELD_ATTETIONED,
    CRDBMYSQL_ACCOUNTUSER_FIELD_ATTETION,
    CRDBMYSQL_ACCOUNTUSER_FIELD_PUBLISHED,
    CRDBMYSQL_ACCOUNTUSER_FIELD_COUNT
};
enum ENUMCRDBMYSQLACCOUNTADMINFIELD {
	CRDBMYSQL_ACCOUNTADMIN_FIELD_USERNAME = 0,
	CRDBMYSQL_ACCOUNTADMIN_FIELD_PASSWORD,
    CRDBMYSQL_ACCOUNTADMIN_FIELD_PHONENUM,
    CRDBMYSQL_ACCOUNTADMIN_FIELD_EMAIL,
    CRDBMYSQL_ACCOUNTADMIN_FIELD_NICKNAME,
    CRDBMYSQL_ACCOUNTADMIN_FIELD_SORTTYPE,
	CRDBMYSQL_ACCOUNTADMIN_FIELD_ATTETIONED,
    CRDBMYSQL_ACCOUNTADMIN_FIELD_ATTETION,
	CRDBMYSQL_ACCOUNTADMIN_FIELD_PUBLISHED,
	CRDBMYSQL_ACCOUNTADMIN_FIELD_COUNT
};
enum ENUMCRDBMYSQLPRODUCTSFIELD {
    CRDBMYSQL_PRODUCTS_FIELD_PUBLISHER = 0,
	CRDBMYSQL_PRODUCTS_FIELD_UUID,
	CRDBMYSQL_PRODUCTS_FIELD_TITLE,
	CRDBMYSQL_PRODUCTS_FIELD_PRICE,
	CRDBMYSQL_PRODUCTS_FIELD_DESCRIPTION,
	CRDBMYSQL_PRODUCTS_FIELD_SORT,
	CRDBMYSQL_PRODUCTS_FIELD_UDSORT,
	CRDBMYSQL_PRODUCTS_FIELD_IMAGES,
	CRDBMYSQL_PRODUCTS_FIELD_KEYWORD,
	CRDBMYSQL_PRODUCTS_FIELD_STATUS,
	CRDBMYSQL_PRODUCTS_FIELD_COUNT
};
enum ENUMCRDBMYSQLATTETIONINFOFIELD {
    CRDBMYSQL_ATTETIONINFO_FIELD_ATTETIONFROM = 0,
	CRDBMYSQL_ATTETIONINFO_FIELD_ATTETIONTO,
	CRDBMYSQL_ATTETIONINFO_FIELD_COUNT
};
//
CRDBImplMYSQL::CRDBImplMYSQL()
: m_uFlag( CRDBMYSQL_FLAG_NONE ){
    //
	mysql_init( &m_inst );
	//
	_connect2DB();
}

CRDBImplMYSQL::~CRDBImplMYSQL() {
	mysql_close( &m_inst );
}

bool CRDBImplMYSQL::_isReady() {
	bool bReady = m_uFlag & CRDBMYSQL_FLAG_CONNECTED2DB;

	if ( !bReady ) {
	    CRLOG_ERROR( "mysql not ready." );
	}
    return bReady;
}

bool CRDBImplMYSQL::_connect2DB() {
    const char szUser[] = "root"; //username
    const char szPswd[] = ""; //password
    const char szHost[] = "localhost"; //or"127.0.0.1"
    const char szDBName[] = "CRDB"; //database
    unsigned int port = 3396; //server port

    if( !mysql_real_connect(&m_inst,szHost,szUser,szPswd,szDBName,port,NULL,0) ) {
		CRLOG_ERROR( "connect mysql failed." );
	    return false;
	}

	m_uFlag |= CRDBMYSQL_FLAG_CONNECTED2DB;
	return true;
}

bool CRDBImplMYSQL::doSave( const CRAccountUser* pAccount, int& nErrCode ) {
	if ( !_isReady() )
		return false;
	USES_CONVERSION;
	std::string strSQLMsg;
	char szBufTmp[ 50 ];

	strSQLMsg = "insert into accountuser values(";
	strSQLMsg += "\"";
	strSQLMsg += pAccount->m_data.m_strUserName;
	strSQLMsg += "\",\"";
	strSQLMsg += pAccount->m_data.m_strPassword;
	strSQLMsg += "\",\"";
	strSQLMsg += pAccount->m_data.m_strPhoneNum;
	strSQLMsg += "\",\"";
	strSQLMsg += pAccount->m_data.m_strEMail;
	strSQLMsg += "\",\"";
	strSQLMsg += pAccount->m_data.m_strNickName;
	strSQLMsg += "\",";
	_itoa_s( (int)pAccount->m_data.m_eSortType, szBufTmp, 10 );
	strSQLMsg += szBufTmp;
	strSQLMsg += ",";
	_itoa_s( (int)pAccount->m_data.m_nCountAttetioned, szBufTmp, 10 );
	strSQLMsg += szBufTmp;
	strSQLMsg += ",";
	_itoa_s( (int)pAccount->m_data.m_nCountAttetion, szBufTmp, 10 );
	strSQLMsg += szBufTmp;
	strSQLMsg += ",";
	_itoa_s( (int)pAccount->m_data.m_nCountPublished, szBufTmp, 10 );
	strSQLMsg += szBufTmp;
	strSQLMsg += ");";
	//
	return 0 == mysql_query( &m_inst, strSQLMsg.c_str() );
}

bool CRDBImplMYSQL::doSave( const CRAccountAdmin* pAccount, int& nErrCode ) {
	if ( !_isReady() )
		return false;
	USES_CONVERSION;
	std::string strSQLMsg;
	char szBufTmp[ 50 ];

	strSQLMsg = "insert into accountadmin values(";
	strSQLMsg += "\"";
	strSQLMsg += pAccount->m_data.m_strUserName;
	strSQLMsg += "\",\"";
	strSQLMsg += pAccount->m_data.m_strPassword;
	strSQLMsg += "\",\"";
	strSQLMsg += pAccount->m_data.m_strPhoneNum;
	strSQLMsg += "\",\"";
	strSQLMsg += pAccount->m_data.m_strEMail;
	strSQLMsg += "\",\"";
	strSQLMsg += pAccount->m_data.m_strNickName;
	strSQLMsg += "\",";
	_itoa_s( (int)pAccount->m_data.m_eSortType, szBufTmp, 10 );
	strSQLMsg += szBufTmp;
	strSQLMsg +=",0,0);";
	//
	return 0 == mysql_query( &m_inst, strSQLMsg.c_str() );
}

bool CRDBImplMYSQL::doSave( const CRProduct* pProduct, int& nErrCode ) {
    if ( !_isReady() )
		return false;
	USES_CONVERSION;
	
	std::string strSQLMsg;
	char szBufTmp[ 50 ];
	std::string strTmp;
	std::string strUtf8;

	// add product record.
	strSQLMsg = "insert into products values(";
	strSQLMsg += "\"";
	strSQLMsg += pProduct->m_strPublisher;
	strSQLMsg += "\",\"";
	strSQLMsg += pProduct->m_strUUID;
	strSQLMsg += "\",\"";
	//strSQLMsg += T2A( pProduct->m_strTitle.c_str() );
	strSQLMsg += pProduct->m_strTitle;
	strSQLMsg += "\",\"";
	strSQLMsg += pProduct->m_strPrice;
	strSQLMsg += "\",\"";
	strSQLMsg += pProduct->m_strDescribe;
	strSQLMsg += "\",\"";
	_itoa_s( pProduct->m_nSortType, szBufTmp, 10 );
	strSQLMsg += szBufTmp;
	strSQLMsg += "\",\"";
	strSQLMsg += pProduct->m_strUDSort;
	strSQLMsg += "\",\"";
	strContainer2JsonStrWithQuotes( pProduct->m_containerImages, strTmp );
	strSQLMsg += strTmp.c_str();
	strSQLMsg += "\",\"";
	strContainer2JsonStrWithQuotes( pProduct->m_containerKeywords, strTmp );
	strSQLMsg += strTmp.c_str();
	strSQLMsg += "\",";
	_itoa_s( (int)CRPRODUCT_STATUS_PENDING, szBufTmp, 10 );
	strSQLMsg += szBufTmp;
	strSQLMsg +=");";
	if ( 0 != mysql_query( &m_inst, strSQLMsg.c_str() ) )
		return false;
	
	// update published count
	strSQLMsg = "update accountuser set published=published+1 where username in('";
	strSQLMsg += pProduct->m_strPublisher;
	strSQLMsg += "');";

	return 0 == mysql_query( &m_inst, strSQLMsg.c_str() );
}

bool CRDBImplMYSQL::doLoad( void* pParamKey, CRAccountUser& destObj, int& nErrCode ) {
	//  select * from accountuser where username='wyf'
	if ( !_isReady() )
		return false;
	utf8_type* pstrAccountName = (utf8_type*)pParamKey;
	if ( !pstrAccountName ) {
	    nErrCode = CRERR_SRV_PARAM_INVALID;
		return false;
	}
	USES_CONVERSION;
	std::string strCmd;
	MYSQL_RES* pMYSQLRes = NULL;
    MYSQL_ROW mysqlRow;
	unsigned int uNumFields;
	char* pFieldData = NULL;

	strCmd = "select * from accountuser where username='";
	strCmd += *pstrAccountName;
	strCmd += "';";
	if ( 0 != mysql_query( &m_inst, strCmd.c_str() ) ) {
	    return false;
	}
	pMYSQLRes = mysql_store_result( &m_inst );
	if ( !pMYSQLRes ) {
	    return false;
	}
	uNumFields = mysql_num_fields( pMYSQLRes );
    if ( uNumFields != CRDBMYSQL_ACCOUNTUSER_FIELD_COUNT ) {
	    assert( false );
		return false;
	}
	mysqlRow = mysql_fetch_row( pMYSQLRes );
	if ( mysqlRow == 0 )
		return false;

	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_USERNAME ];
	destObj.m_data.m_strUserName = pFieldData ? pFieldData : "";
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_PASSWORD ];
	destObj.m_data.m_strPassword = pFieldData ? pFieldData : "";
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_PHONENUM ];
	destObj.m_data.m_strPhoneNum = pFieldData ? pFieldData : "";
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_EMAIL ];
	destObj.m_data.m_strEMail = pFieldData ? pFieldData : "";
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_NICKNAME ];
	destObj.m_data.m_strNickName = pFieldData ? pFieldData : "";
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_SORTTYPE ];
	destObj.m_data.m_eSortType = (ENUMACCOUNTSORT)atoi( pFieldData );
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_ATTETIONED ];
	destObj.m_data.m_nCountAttetioned = atoi( pFieldData );
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_ATTETION ];
	destObj.m_data.m_nCountAttetion = atoi( pFieldData );
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_PUBLISHED ];
	destObj.m_data.m_nCountPublished = atoi( pFieldData );
	return true;
}

bool CRDBImplMYSQL::doLoad( void* pParamKey, CRAccountAdmin& destObj, int& nErrCode ) {
	//  select * from accountuser where username = 'wyf'
	if ( !_isReady() )
		return false;
	utf8_type* pstrAccountName = (utf8_type*)pParamKey;
	if ( !pstrAccountName ) {
	    nErrCode = CRERR_SRV_PARAM_INVALID;
		return false;
	}
	USES_CONVERSION;
	std::string strCmd;
	MYSQL_RES* pMYSQLRes = NULL;
    MYSQL_ROW mysqlRow;
	unsigned int uNumFields;
	char* pFieldData = NULL; 

	strCmd = "select * from accountadmin where username='";
	strCmd += *pstrAccountName;
	strCmd += "';";
	if ( 0 != mysql_query( &m_inst, strCmd.c_str() ) ) {
	    return false;
	}
	pMYSQLRes = mysql_store_result( &m_inst );
	if ( !pMYSQLRes ) {
		CRLOG_INFO( "pMYSQLRes is NULL." );
	    return false;
	}
	uNumFields = mysql_num_fields( pMYSQLRes );
    if ( uNumFields != CRDBMYSQL_ACCOUNTADMIN_FIELD_COUNT ) {
	    assert( false );
		CRLOG_ERROR( "uNumFields != CRDBMYSQL_ACCOUNTADMIN_FIELD_COUNT" );
		return false;
	}
	mysqlRow = mysql_fetch_row( pMYSQLRes );
	if ( mysqlRow == 0 ) {
	    CRLOG_INFO( "mysqlRow == 0" );
		return false;
	}

	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_USERNAME ];
	destObj.m_data.m_strUserName = pFieldData ? pFieldData : "";
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_PASSWORD ];
	destObj.m_data.m_strPassword = pFieldData ? pFieldData : "";
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_PHONENUM ];
	destObj.m_data.m_strPhoneNum = pFieldData ? pFieldData : "";
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_EMAIL ];
	destObj.m_data.m_strEMail = pFieldData ? pFieldData : "";
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_NICKNAME ];
	destObj.m_data.m_strNickName = pFieldData ? pFieldData : "";
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_SORTTYPE ];
	destObj.m_data.m_eSortType = (ENUMACCOUNTSORT)atoi( pFieldData );
    pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_ATTETIONED ];
	destObj.m_data.m_nCountAttetioned = atoi( pFieldData );
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_ATTETION ];
	destObj.m_data.m_nCountAttetion = atoi( pFieldData );
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_PUBLISHED ];
	destObj.m_data.m_nCountPublished = atoi( pFieldData );
	return true;
}

bool CRDBImplMYSQL::doLoad( void* pParamKey, CRAccountList& destObj, int& nErrCode ) {
	//  select * from accountuser where username = 'wyf'
	if ( !_isReady() )
		return false;
	utf8_container_type* pAccountNames = (utf8_container_type*)pParamKey;
	if ( !pAccountNames ) {
	    nErrCode = CRERR_SRV_PARAM_INVALID;
		return false;
	}
	std::string strCmd;
	MYSQL_RES* pMYSQLRes = NULL;
    MYSQL_ROW mysqlRow;
	unsigned int uNumFields;
	char* pFieldData = NULL; 
	unsigned int uCountAccountName;

	uCountAccountName = pAccountNames->size();
	strCmd = "select * from accountuser where username in('";
	for ( unsigned int uIndex = 0; uIndex<uCountAccountName; ++uIndex ) {
	    strCmd += pAccountNames->at( uIndex );
		if ( (uIndex + 1) != uCountAccountName ) {
            strCmd += "','";
		}
	}
	strCmd += "');";
	if ( 0 != mysql_query( &m_inst, strCmd.c_str() ) ) {
		CRLOG_INFO( "mysql_query failed. strCmd:%s", strCmd.c_str() );
	    return false;
	}
	pMYSQLRes = mysql_store_result( &m_inst );
	if ( !pMYSQLRes ) {
		CRLOG_INFO( "mysql_store_result no result. strCmd:%s", strCmd.c_str() );
	    return false;
	}
	
	uNumFields = mysql_num_fields( pMYSQLRes );
    if ( uNumFields != CRDBMYSQL_ACCOUNTUSER_FIELD_COUNT ) {
	    assert( false );
		return false;
	}

	while ( mysqlRow = mysql_fetch_row( pMYSQLRes ) ) {
		CRAccountUser* pAccountNew = new CRAccountUser();
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_USERNAME ];
		pAccountNew->m_data.m_strUserName = pFieldData ? pFieldData : "";
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_PASSWORD ];
		pAccountNew->m_data.m_strPassword = pFieldData ? pFieldData : "";
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_PHONENUM ];
		pAccountNew->m_data.m_strPhoneNum = pFieldData ? pFieldData : "";
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_EMAIL ];
		pAccountNew->m_data.m_strEMail = pFieldData ? pFieldData : "";
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_NICKNAME ];
		pAccountNew->m_data.m_strNickName = pFieldData ? pFieldData : "";
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_SORTTYPE ];
		pAccountNew->m_data.m_eSortType = (ENUMACCOUNTSORT)atoi( pFieldData );
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_ATTETIONED ];
		pAccountNew->m_data.m_nCountAttetioned = atoi( pFieldData );
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_ATTETION ];
		pAccountNew->m_data.m_nCountAttetion = atoi( pFieldData );
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_PUBLISHED ];
		pAccountNew->m_data.m_nCountPublished = atoi( pFieldData );
		//
		destObj.m_containerAccount.push_back( pAccountNew );
	}

	return true;
}

bool CRDBImplMYSQL::doSave( const CRAttetionRecord* pAddAttetion, int& nErrCode ) {
	if ( !_isReady() )
        return false;
	std::string strSQLMsg;

	strSQLMsg = "insert into attetioninfo values(";
	strSQLMsg += "\"";
	strSQLMsg += pAddAttetion->m_strUserNameFrom;
	strSQLMsg += "\",\"";
	strSQLMsg += pAddAttetion->m_strUserNameTo;
	strSQLMsg += "\");";
	
	//
	if ( 0 != mysql_query( &m_inst, strSQLMsg.c_str() ) )
		return false;

	// update attetion count
	strSQLMsg = "update accountuser set attetion=attetion+1 where username in('";
	strSQLMsg += pAddAttetion->m_strUserNameFrom;
	strSQLMsg += "');";
	if ( 0 != mysql_query( &m_inst, strSQLMsg.c_str() ) )
		return false;

	// update attetioned count
	strSQLMsg = "update accountuser set attetioned=attetioned+1 where username in('";
	strSQLMsg += pAddAttetion->m_strUserNameTo;
	strSQLMsg += "');";

	return 0 == mysql_query( &m_inst, strSQLMsg.c_str() );
}

bool CRDBImplMYSQL::doLoad( void* pParamKey, CRAttetionRecordList& destObj, int& nErrCode ) {
	CRFetchAttetionRecordListParam* pFARLParam = (CRFetchAttetionRecordListParam*)pParamKey;

	nErrCode = CRERR_SRV_NONE;
	if ( !pFARLParam ) {
	    nErrCode = CRERR_SRV_PARAM_INVALID;
		return false;
	}
	switch ( pFARLParam->m_eFetchMode )
	{
	case CRFetchAttetionRecordListParam::EFM_ATTETION:
	{
	    return _doLoadAttetions( pFARLParam->m_strAccountName, destObj, nErrCode );
	}
		break;
	case CRFetchAttetionRecordListParam::EFM_ATTETIONED:
	{
	    return _doLoadAttetioneds( pFARLParam->m_strAccountName, destObj, nErrCode );
	}
		break;
	default:
	    nErrCode = CRERR_SRV_PARAM_INVALID;
		break;
	}

	assert( false );
	return false;
}

bool CRDBImplMYSQL::_doLoadAttetionRecord( const std::string& strSQLMsg, CRAttetionRecordList& destObj, int& nErrCode ) {
	MYSQL_RES* pMYSQLRes = NULL;
	unsigned int uNumFields;
	MYSQL_ROW mysqlRow;
	char* pFieldData = NULL;
	utf8_type strTmp;
	
	//
	if ( 0 != mysql_query( &m_inst, strSQLMsg.c_str() ) ) {
	    nErrCode = CRERR_SRV_DB_NOTREADY;
		return false;
	}

	pMYSQLRes = mysql_store_result( &m_inst );
	if ( !pMYSQLRes ) {
		nErrCode = CRERR_SRV_DB_NODATA;
	    return false;
	}
	
	uNumFields = mysql_num_fields( pMYSQLRes );
    if ( uNumFields != CRDBMYSQL_ATTETIONINFO_FIELD_COUNT ) {
	    assert( false );
		nErrCode = CRERR_SRV_DB_DATA_FORMAT_ERROR;
		return false;
	}

	//
	unsigned uIndex = 0;
	while ( mysqlRow = mysql_fetch_row( pMYSQLRes ) ) {
		CRAttetionRecord* pAttetionRecord = new CRAttetionRecord();
		CFuncPack fpkDelRecord( ::gfnDelObj< CRAttetionRecord >, pAttetionRecord );
		//
		pFieldData = mysqlRow[ CRDBMYSQL_ATTETIONINFO_FIELD_ATTETIONFROM ];
		pAttetionRecord->m_strUserNameFrom = pFieldData;
		//
	    pFieldData = mysqlRow[ CRDBMYSQL_ATTETIONINFO_FIELD_ATTETIONTO ];
		pAttetionRecord->m_strUserNameTo = pFieldData;
		//
		destObj.m_listAttetionRecords.push_back( pAttetionRecord );
        fpkDelRecord.Cancel();
	}

	return true;
}

bool CRDBImplMYSQL::_doLoadAttetions( const utf8_type& strAccountName, CRAttetionRecordList& destObj, int& nErrCode ) {
	// select * from attetioninfo where attetionfrom = 'wyf'
	std::string strSQLMsg;
	std::string strUTF8;

	strSQLMsg = "select * from attetioninfo where attetionfrom = '";
	strSQLMsg += strAccountName;
	strSQLMsg += "';";

	return _doLoadAttetionRecord( strSQLMsg, destObj, nErrCode );
}

bool CRDBImplMYSQL::_doLoadAttetioneds( const utf8_type& strAccountName, CRAttetionRecordList& destObj, int& nErrCode ) {
	// select * from attetioninfo where attetionto = 'wyf'
	std::string strSQLMsg;
	std::string strUTF8;

	strSQLMsg = "select * from attetioninfo where attetionto = '";
	strSQLMsg += strAccountName;
	strSQLMsg += "';";

	return _doLoadAttetionRecord( strSQLMsg, destObj, nErrCode );
}

bool CRDBImplMYSQL::doLoad( void* pParamKey, CRAccountProducts& destObj, int& nErrCode ) {
	// select * from products where publisher = 'wyf';
	std::string strSQLMsg;
	std::string strUTF8;
	MYSQL_RES* pMYSQLRes = NULL;
	unsigned int uNumFields;
	MYSQL_ROW mysqlRow;

	const CRFetchAccountProducts* pFAPParam = (const CRFetchAccountProducts*)pParamKey;
	if ( !pParamKey )
		return false;
	
	strSQLMsg = "select * from products where publisher = '";
	strSQLMsg += pFAPParam->m_strAccountName;
	strSQLMsg += "';";
	
	//
	if ( 0 != mysql_query( &m_inst, strSQLMsg.c_str() ) )
		return false;

	pMYSQLRes = mysql_store_result( &m_inst );
	if ( !pMYSQLRes ) {
	    return false;
	}
	
	uNumFields = mysql_num_fields( pMYSQLRes );
    if ( uNumFields != CRDBMYSQL_PRODUCTS_FIELD_COUNT ) {
	    assert( false );
		return false;
	}

	//
	unsigned uIndex = 0;
	while ( mysqlRow = mysql_fetch_row( pMYSQLRes ) ) {
		CRProduct* pProduct = _createProduct( mysqlRow );
		if ( !pProduct )
			continue;
		if ( uIndex >= pFAPParam->m_uIndexStart ) {
			if ( uIndex < ( pFAPParam->m_uIndexStart + pFAPParam->m_uCount ) ) {
		        destObj.m_listProduct.push_back( pProduct );
			} else {
			    break;
			}
		}
		uIndex ++;
	}

	return true;
}

bool CRDBImplMYSQL::doLoad( void* pParamKey, CRProduct& destObj, int& nErrCode ) {
    // select * from products where uuid = 'cbc32a17-d45c-424c-90e3-5e714374c7eb';
	std::string strSQLMsg;
	utf8_type* pstrUUID = (utf8_type*)pParamKey;
	MYSQL_RES* pMYSQLRes = NULL;
	unsigned int uNumFields;
	MYSQL_ROW mysqlRow;
	char* pFieldData = NULL;

	strSQLMsg = "select * from products where uuid = '";
	strSQLMsg += pstrUUID->c_str();
	strSQLMsg += "';";
	
	//
	if ( 0 != mysql_query( &m_inst, strSQLMsg.c_str() ) )
		return false;

	pMYSQLRes = mysql_store_result( &m_inst );
	if ( !pMYSQLRes ) {
	    return false;
	}
	
	uNumFields = mysql_num_fields( pMYSQLRes );
    if ( uNumFields != CRDBMYSQL_PRODUCTS_FIELD_COUNT ) {
	    assert( false );
		return false;
	}

	mysqlRow = mysql_fetch_row( pMYSQLRes );
	if ( !mysqlRow )
		return false;
	// just need 1st result.
	return _fillProduct( mysqlRow, &destObj );
}

CRProduct* CRDBImplMYSQL::_createProduct( MYSQL_ROW mysqlRow ) {
    CRProduct* pProduct = new CRProduct();
	CFuncPack fpkDelProduct( ::gfnDelObj<CRProduct>, pProduct );

	if ( !_fillProduct( mysqlRow, pProduct ) )
		return NULL;
	
	fpkDelProduct.Cancel();
	return pProduct;
}

bool CRDBImplMYSQL::_fillProduct( MYSQL_ROW mysqlRow, CRProduct* pProduct ) {
	char* pFieldData = NULL;
	utf8_type strTmp;

	//
	pFieldData = mysqlRow[ CRDBMYSQL_PRODUCTS_FIELD_PUBLISHER ];
    pProduct->m_strPublisher = pFieldData;
	//
	pFieldData = mysqlRow[ CRDBMYSQL_PRODUCTS_FIELD_UUID ];
	pProduct->m_strUUID = pFieldData;
	//
	pFieldData = mysqlRow[ CRDBMYSQL_PRODUCTS_FIELD_TITLE ];
	pProduct->m_strTitle = pFieldData;
	//
	pFieldData = mysqlRow[ CRDBMYSQL_PRODUCTS_FIELD_PRICE ];
	pProduct->m_strPrice = pFieldData;
	//
	pFieldData = mysqlRow[ CRDBMYSQL_PRODUCTS_FIELD_DESCRIPTION ];
	pProduct->m_strDescribe = pFieldData;
	//
	pFieldData = mysqlRow[ CRDBMYSQL_PRODUCTS_FIELD_SORT ];
	pProduct->m_nSortType = atoi( pFieldData );
	//
	pFieldData = mysqlRow[ CRDBMYSQL_PRODUCTS_FIELD_UDSORT ];
	pProduct->m_strUDSort = pFieldData;
	//
	pFieldData = mysqlRow[ CRDBMYSQL_PRODUCTS_FIELD_IMAGES ];
	if ( !_parseJsonStringArray( pFieldData, pProduct->m_containerImages ) )
		return false;
	//
	pFieldData = mysqlRow[ CRDBMYSQL_PRODUCTS_FIELD_KEYWORD ];
	if ( !_parseJsonStringArray( pFieldData, pProduct->m_containerKeywords ) )
		return false;
	//
	pFieldData = mysqlRow[ CRDBMYSQL_PRODUCTS_FIELD_STATUS ];
	pProduct->m_nPassStatus = atoi( pFieldData );

	return true;
}

bool CRDBImplMYSQL::_parseJsonStringArray( char* pFieldData, utf8_container_type& containerStr ) {
    if ( !pFieldData )
		return false;
	Json::Reader reader;
	Json::Value jsonArray;

	if( !reader.parse( pFieldData, jsonArray ) )
		return false;
	int nCount = jsonArray.size();
	for ( int nIndex = 0; nIndex<nCount; ++nIndex ) {
		Json::Value& valItem = jsonArray[ nIndex ];
	    if ( !valItem.isString() )
			continue;
		containerStr.push_back( valItem.asString() ); 
	}

	return true;
}




