#include "stdafx.h"
#include "CRDBImplMYSQL.h"
#include "CRAccountUser.h"
#include "CRAccountAdmin.h"
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
    CRDBMYSQL_ACCOUNTUSER_FIELD_COUNT
};
enum ENUMCRDBMYSQLACCOUNTADMINFIELD {
	CRDBMYSQL_ACCOUNTADMIN_FIELD_USERNAME = 0,
	CRDBMYSQL_ACCOUNTADMIN_FIELD_PASSWORD,
    CRDBMYSQL_ACCOUNTADMIN_FIELD_PHONENUM,
    CRDBMYSQL_ACCOUNTADMIN_FIELD_EMAIL,
    CRDBMYSQL_ACCOUNTADMIN_FIELD_NICKNAME,
    CRDBMYSQL_ACCOUNTADMIN_FIELD_SORTTYPE,
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
	strSQLMsg += T2A( pAccount->m_regInfo.m_tstrUserName.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_regInfo.m_tstrPassword.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_regInfo.m_tstrPhoneNum.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_regInfo.m_tstrEMail.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_regInfo.m_tstrNickName.c_str() );
	strSQLMsg += "\",";
	_itoa_s( (int)pAccount->m_regInfo.m_eSortType, szBufTmp, 10 );
	strSQLMsg += szBufTmp;
	strSQLMsg +=")";
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
	strSQLMsg += T2A( pAccount->m_regInfo.m_tstrUserName.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_regInfo.m_tstrPassword.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_regInfo.m_tstrPhoneNum.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_regInfo.m_tstrEMail.c_str() );
	strSQLMsg += "\",\"";
	strSQLMsg += T2A( pAccount->m_regInfo.m_tstrNickName.c_str() );
	strSQLMsg += "\",";
	_itoa_s( (int)pAccount->m_regInfo.m_eSortType, szBufTmp, 10 );
	strSQLMsg += szBufTmp;
	strSQLMsg +=")";
	//
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
	destObj.m_regInfo.m_tstrUserName = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_PASSWORD ];
	destObj.m_regInfo.m_tstrPassword = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_PHONENUM ];
	destObj.m_regInfo.m_tstrPhoneNum = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_EMAIL ];
	destObj.m_regInfo.m_tstrEMail = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_NICKNAME ];
	destObj.m_regInfo.m_tstrNickName = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTUSER_FIELD_SORTTYPE ];
	destObj.m_regInfo.m_eSortType = (ENUMACCOUNTSORT)atoi( pFieldData );

	return true;
}

bool CRDBImplMYSQL::doLoad( void* pParamKey, CRAccountAdmin& destObj, int& nErrCode ) {
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
	destObj.m_regInfo.m_tstrUserName = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_PASSWORD ];
	destObj.m_regInfo.m_tstrPassword = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_PHONENUM ];
	destObj.m_regInfo.m_tstrPhoneNum = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_EMAIL ];
	destObj.m_regInfo.m_tstrEMail = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_NICKNAME ];
	destObj.m_regInfo.m_tstrNickName = pFieldData ? A2T( pFieldData ) : _T("");
	pFieldData = mysqlRow[ CRDBMYSQL_ACCOUNTADMIN_FIELD_SORTTYPE ];
	destObj.m_regInfo.m_eSortType = (ENUMACCOUNTSORT)atoi( pFieldData );

	return true;
}














