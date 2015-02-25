#ifndef __CRERRCODE_H__
#define __CRERRCODE_H__
#include "tchar.h"
#include <string>

extern const int CRERR_CLI_NONE;


extern const int CRERR_SRV_NONE;
extern const int CRERR_SRV_PARAM_INVALID;
extern const int CRERR_SRV_ACCOUNTNAME_EXIST;
extern const int CRERR_SRV_ACCOUNTNAME_ISNOT_EXIST;
extern const int CRERR_SRV_ACCOUNT_INVALID;
extern const int CRERR_SRV_ACCOUNT_PASSWORD_INCORRECT;
extern const int CRERR_SRV_ACCOUNT_LOGINED_INSAMEOS;
extern const int CRERR_SRV_ACCOUNT_NOLOGINRECORD;
extern const int CRERR_SRV_ACCOUNT_LOGOFF_NOTSAMESESSION;
extern const int CRERR_SRV_DB_NOTREADY;
extern const int CRERR_SRV_DB_NODATA;
extern const int CRERR_SRV_DB_DATA_FORMAT_ERROR;


bool gfnGetErrDescribe( int nErrCode, std::basic_string< TCHAR >& tstrErrDescribe );
#endif //__CRERRCODE_H__