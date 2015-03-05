// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include "winsock2.h"
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#pragma  comment( lib, "ws2_32.lib" )
//#pragma  comment( lib, "HMNWE.lib" )
#pragma  comment( lib, "HMNWP.lib" )
#pragma  comment( lib, "CRSrvBase.lib" )

#ifdef _DEBUG
#pragma comment (lib, "json_vc71_libmtd.lib")
#pragma comment (lib, "libmysql.lib")
#else
#pragma comment (lib, "json_vc71_libmt.lib")
#pragma comment (lib, "libmysql.lib")
#endif //