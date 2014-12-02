#include "stdafx.h"
#include "CRServerRoot.h"
#include "CRServerApp.h"
//
CRServerRoot g_CRSrvRoot;
CRServerApp g_CRSrvApp;
//
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow) {

	g_CRSrvApp.run();
}