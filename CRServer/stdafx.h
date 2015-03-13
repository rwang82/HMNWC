#pragma once

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

// TODO:  在此处引用程序需要的其他头文件
#include "winsock2.h"
#include <windows.h>

#include "CRTypes.h"

#pragma  comment( lib, "ws2_32.lib" )
//#pragma  comment( lib, "HMNWE.lib" )
#pragma  comment( lib, "HMNWP.lib" )

#ifdef _DEBUG
#pragma comment (lib, "json_vc71_libmtd.lib")
#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "log4cpp.lib")
#else
#pragma comment (lib, "json_vc71_libmt.lib")
#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "log4cpp.lib")
#endif //
