#ifndef __CRERRCODE_H__
#define __CRERRCODE_H__
#include "tchar.h"
#include <string>

extern const int CRERR_CLI_NONE;


extern const int CRERR_SRV_NONE;
extern const int CRERR_SRV_ACCOUNTNAME_EXIST;


bool gfnGetErrDescribe( int nErrCode, std::basic_string< TCHAR >& tstrErrDescribe );
#endif //__CRERRCODE_H__