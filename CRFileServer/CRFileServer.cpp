// CRFileServer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CRFileServer.h"
#include "CRSrvRoot.h"
#include "CRFileSrvApp.h"
#include "CRFSRMsgListener.h"

//
CRFSRMsgListener g_fsrmsgListener;
CRSrvRoot g_srvRoot( &g_fsrmsgListener );
CRFileSrvApp g_srvApp;
//
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	g_srvRoot.m_nwpServer.listen( 7890 );

	g_srvApp.run();
}

