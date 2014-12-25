#include "stdafx.h"
#include "HMNWEServer.h"
#include "HMNWEDemoServerEventHandler.h"

HMNWEDemoServerEventHandler g_srvEvtHandler;
HMNWEServer g_nweServer( &g_srvEvtHandler );

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow) {

	g_nweServer.listen( 7654 );	

	while ( 1 ) {
		::Sleep(1000);
	}
	//g_CRSrvApp.run();
}