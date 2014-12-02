
// HMNWPDemoClientDlg.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "HMNWPHandler4ClientDemo.h"

// CHMNWPDemoClientDlgApp: 
// 有关此类的实现，请参阅 HMNWPDemoClientDlg.cpp
//

enum ENUMCONNECTSTATE {
	ECONN_STATE_UNKNOWN = -1,
	ECONN_STATE_DISCONNECT = 0,
	ECONN_STATE_DISCONNECTING,
	ECONN_STATE_CONNECTED,
	ECONN_STATE_CONNECTING,
};

class CHMNWPDemoClientDlgApp : public CWinApp
{
public:
	CHMNWPDemoClientDlgApp();
	~CHMNWPDemoClientDlgApp();
	
// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

public:
	void setConnState( ENUMCONNECTSTATE eConnState );
	ENUMCONNECTSTATE getConnState() const;

public:
	HMNWPHandler4ClientDemo m_handler4NWP;

private:
	ENUMCONNECTSTATE m_eConnState;
};

extern CHMNWPDemoClientDlgApp theApp;
