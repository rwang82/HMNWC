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
#include <assert.h>



// TODO: reference additional headers your program requires here
#include "CRSrvEnvCfg.h"

#pragma  comment( lib, "ws2_32.lib" )
//#pragma  comment( lib, "HMNWE.lib" )
#pragma  comment( lib, "HMNWP.lib" )

//#pragma warning( disable : 4251 )
