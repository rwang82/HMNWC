
// CRClientMock.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "hmcmn_event_depot.h"
#include "CRCCommDepot.h"
#include "CRModuleDepot.h"
#include "CRRMsgHandlerDepot.h"
#include "HMTaskEngine.h"
#include "resource.h"		// main symbols
#include "tchar.h"
#include <string>
//
#define STR_CONNSTATE_CONNECTING _T("Connecting...")
#define STR_CONNSTATE_CONNECTED _T("Connected")
#define STR_CONNSTATE_DISCONNECTING _T("DisConnecting...")
#define STR_CONNSTATE_DISCONNECTED _T("DisConnected")
#define STR_LOGIN_SUCCESS _T("Login success!")
#define STR_LOGIN_FAILED _T("Login failed!")
#define STR_LOGOFF_SUCCESS _T("Logoff succes!")
#define STR_LOGOFF_FAILED _T("Logoff failed!")
//
	#define MODULE_GET( id, module_cls, ptrModule ) \
        module_cls* ptrModule = NULL; \
	    do { \
				ptrModule = dynamic_cast<module_cls*>(theApp.m_moduleDepot.getModule( id )); \
	    } while ( 0 )
//
// CCRClientMockApp:
// See CRClientMock.cpp for the implementation of this class
//

class CCRClientMockApp : public CWinApp
{
public:
	CCRClientMockApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

private:
	void _initModules();
	void _initRMsgHandlers();

public:
	hmcmn::hmcmn_event_depot m_eventDepot;
	HMTaskEngine m_taskEngineMain;
	CRCCommDepot m_commDepot;
	CRModuleDepot m_moduleDepot;
	CRRMsgHandlerDepot m_rmsghandlerDepot;

};

extern CCRClientMockApp theApp;