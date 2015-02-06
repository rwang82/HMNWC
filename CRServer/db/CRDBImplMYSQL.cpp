#include "stdafx.h"
#include "CRDBImplMYSQL.h"
#include "CRAccountUser.h"
#include "CRAccountAdmin.h"
#include "CRProduct.h"
#include "CRAddAttetion.h"
#include "CRAccountList.h"
#include "CRMisc.h"
#include "CRErrCode.h"
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
    return m_uFlag & CRDBMYSQL_FLAG_CONNECTED2DB;
}

bool CRDBImplMYSQL::_connect2DB() {
    const char szUser[] = "root"; //username
    const char szPswd[] = ""; //password
    const char szHost[] = "localhost"; //or"127.0.0.1"
    const char szDBName[] = "CRDB"; //database
    unsigned int port = 3396; //server port

    if( !mysql_real_connect(&m_inst,szHost,szUser,szPswd,szDBName,port,NULL,0) ) {
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
	strSQLMsg += T2A( pAccount->m_data.m_tstrUserName.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_data.m_tstrPassword.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_data.m_tstrPhoneNum.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_data.m_tstrEMail.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_data.m_tstrNickName.c_str() );
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
	strSQLMsg += ")";
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
	strSQLMsg += T2A( pAccount->m_data.m_tstrUserName.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_data.m_tstrPassword.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_data.m_tstrPhoneNum.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_data.m_tstrEMail.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_data.m_tstrNickName.c_str() );
	strSQLMsg += "\",";
	_itoa_s( (int)pAccount->m_data.m_eSortType, szBufTmp, 10 );
	strSQLMsg += szBufTmp;
	strSQLMsg +=",0,0)";
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

	// add product record.
	strSQLMsg = "insert into products values(";
	strSQLMsg += "\"";
	strSQLMsg += T2A( pProduct->m_tstrPublisher.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pProduct->m_tstrUUID.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pProduct->m_tstrTitle.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pProduct->m_tstrPrice.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pProduct->m_tstrDescribe.c_str() );
	strSQLMsg += "\",\"";
	strContainer2JsonStrWithQuotes( pProduct->m_containerImages, strTmp );
	strSQLMsg += strTmp.c_str();
	strSQLMsg += "\",\"";
	strContainer2JsonStrWithQuotes( pProduct->m_containerKeywords, strTmp );
	strSQLMsg += strTmp.c_str();
	strSQLMsg += "\",";
	_itoa_s( (int)CRPRODUCT_STATUS_PENDING, szBufTmp, 10 );
	strSQLMsg += szBufTmp;
	strSQLMsg +=")";
	if ( 0 != mysql_query( &m_inst, strSQLMsg.c_str() ) )
		return false;
	
	// update published count
	strSQLMsg = "update accountuser set published=published+1 where username in('";
	strSQLMsg += T2A(pProduct->m_tstrPublisher.c_str());
	strSQLMsg += "')";

	return 0 == mysql_query( &m_inst, strSQLMsg.c_str() );
}

bool CRDBImplMYSQL::doLoad( void* pParamKey, CRAccountUser& destObj, int& nErrCode ) {
	//  select * from accountuser where username='wyf'
	if ( !_isReady() )
		return false;
	tstring_type* ptstrAccountName = (tstring_type*)pParamKey;
	if ( !ptstrAccountName ) {
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
	strCmd += T2A( ptstrAccountName->c_str() );
	strCmd += "'";
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
	destObj.m_data.m_tstrUserName = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_PASSWORD ];
	destObj.m_data.m_tstrPassword = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_PHONENUM ];
	destObj.m_data.m_tstrPhoneNum = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_EMAIL ];
	destObj.m_data.m_tstrEMail = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_NICKNAME ];
	destObj.m_data.m_tstrNickName = pFieldData ? A2T( pFieldData ) : _T("");
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
	tstring_type* ptstrAccountName = (tstring_type*)pParamKey;
	if ( !ptstrAccountName ) {
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
	strCmd += T2A( ptstrAccountName->c_str() );
	strCmd += "'";
	if ( 0 != mysql_query( &m_inst, strCmd.c_str() ) ) {
	    return false;
	}
	pMYSQLRes = mysql_store_result( &m_inst );
	if ( !pMYSQLRes ) {
	    return false;
	}
	uNumFields = mysql_num_fields( pMYSQLRes );
    if ( uNumFields != CRDBMYSQL_ACCOUNTADMIN_FIELD_COUNT ) {
	    assert( false );
		return false;
	}
	mysqlRow = mysql_fetch_row( pMYSQLRes );
	if ( mysqlRow == 0 )
		return false;

	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_USERNAME ];
	destObj.m_data.m_tstrUserName = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_PASSWORD ];
	destObj.m_data.m_tstrPassword = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_PHONENUM ];
	destObj.m_data.m_tstrPhoneNum = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_EMAIL ];
	destObj.m_data.m_tstrEMail = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_NICKNAME ];
	destObj.m_data.m_tstrNickName = pFieldData ? A2T( pFieldData ) : _T("");
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

bool CRDBImplMYSQL::doLoad( void* pParamKey, CRProduct& destObj, int& nErrCode ) {


	return false;
}

bool CRDBImplMYSQL::doLoad( void* pParamKey, CRAccountList& destObj, int& nErrCode ) {
	//  select * from accountuser where username = 'wyf'
	if ( !_isReady() )
		return false;
	tstr_container_type* pAccountNames = (tstr_container_type*)pParamKey;
	if ( !pAccountNames ) {
	    nErrCode = CRERR_SRV_PARAM_INVALID;
		return false;
	}
	USES_CONVERSION;
	std::string strCmd;
	MYSQL_RES* pMYSQLRes = NULL;
    MYSQL_ROW mysqlRow;
	unsigned int uNumFields;
	char* pFieldData = NULL; 
	unsigned int uCountAccountName;

	uCountAccountName = pAccountNames->size();
	strCmd = "select * from accountuser where username in('";
	for ( unsigned int uIndex = 0; uIndex<uCountAccountName; ++uIndex ) {
	    strCmd += T2A( pAccountNames->at( uIndex ).c_str() );
		if ( (uIndex + 1) != uCountAccountName ) {
            strCmd += "','";
		}
	}
	strCmd += "')";
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

	while ( mysqlRow = mysql_fetch_row( pMYSQLRes ) ) {
		CRAccountUser* pAccountNew = new CRAccountUser();
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_USERNAME ];
		pAccountNew->m_data.m_tstrUserName = pFieldData ? A2T( pFieldData ) : _T("");
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_PASSWORD ];
		pAccountNew->m_data.m_tstrPassword = pFieldData ? A2T( pFieldData ) : _T("");
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_PHONENUM ];
		pAccountNew->m_data.m_tstrPhoneNum = pFieldData ? A2T( pFieldData ) : _T("");
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_EMAIL ];
		pAccountNew->m_data.m_tstrEMail = pFieldData ? A2T( pFieldData ) : _T("");
		pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_NICKNAME ];
		pAccountNew->m_data.m_tstrNickName = pFieldData ? A2T( pFieldData ) : _T("");
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

bool CRDBImplMYSQL::doSave( const CRAddAttetion* pAddAttetion, int& nErrCode ) {
	if ( !_isReady() )
        return false;
	std::string strSQLMsg;
	USES_CONVERSION;

	strSQLMsg = "insert into attetioninfo values(";
	strSQLMsg += "\"";
	strSQLMsg += T2A( pAddAttetion->m_tstrUserName.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAddAttetion->m_tstrDestUserName.c_str() );
	strSQLMsg += "\")";
	
	//
	if ( 0 != mysql_query( &m_inst, strSQLMsg.c_str() ) )
		return false;

	// update attetion count
	strSQLMsg = "update accountuser set attetion=attetion+1 where username in('";
	strSQLMsg += T2A(pAddAttetion->m_tstrUserName.c_str());
	strSQLMsg += "')";
	if ( 0 != mysql_query( &m_inst, strSQLMsg.c_str() ) )
		return false;

	// update attetioned count
	strSQLMsg = "update accountuser set attetioned=attetioned+1 where username in('";
	strSQLMsg += T2A(pAddAttetion->m_tstrDestUserName.c_str());
	strSQLMsg += "')";

	return 0 == mysql_query( &m_inst, strSQLMsg.c_str() );
}












