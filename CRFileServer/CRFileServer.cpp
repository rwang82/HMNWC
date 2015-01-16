// CRFileServer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CRFileServer.h"
#include "CRFileSrvRoot.h"
#include "CRFileSrvApp.h"

//
CRFileSrvRoot g_srvRoot;
CRFileSrvApp g_srvApp;
//
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	g_srvApp.run();
}

