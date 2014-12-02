
// HMNWPDemoClientDlg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "HMNWPHandler4ClientDemo.h"

// CHMNWPDemoClientDlgApp: 
// �йش����ʵ�֣������ HMNWPDemoClientDlg.cpp
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
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

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
