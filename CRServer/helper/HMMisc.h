#ifndef __HMMISC_H__
#define __HMMISC_H__
#include "tchar.h"
#include <string>

bool getProcessFilePath( std::basic_string< TCHAR >& tstrProcessFilePath );
bool getProcessDirPath( std::basic_string< TCHAR >& tstrProcessDirPath );


#endif //__HMMISC_H__