#ifndef __HMMISC_H__
#define __HMMISC_H__
#include "tchar.h"
#include <string>

bool getProcessFilePath( std::basic_string< TCHAR >& strProcessFilePath );
bool getProcessDirPath( std::basic_string< TCHAR >& strProcessDirPath );


#endif //__HMMISC_H__