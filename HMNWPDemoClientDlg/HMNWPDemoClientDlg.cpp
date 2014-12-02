
// HMNWPDemoClientDlg.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "HMSocketInit.h"
#include "HMNWPClient.h"
#include "HMNWPDemoClientDlg.h"
#include "HMNWPDemoClientDlgDlg.h"
#include "HMNWPHandler4ClientDemo.h"
//
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHMNWPDemoClientDlgApp

BEGIN_MESSAGE_MAP(CHMNWPDemoClientDlgApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CHMNWPDemoClientDlgApp ����

CHMNWPDemoClientDlgApp::CHMNWPDemoClientDlgApp()
: m_eConnState( ECONN_STATE_DISCONNECT ) {
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��

	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc( 218 );
	//_CrtSetBreakAlloc( 221 );
	//_CrtSetBreakAlloc( 224 );
}

CHMNWPDemoClientDlgApp::~CHMNWPDemoClientDlgApp() {
	int a = 0;
}

// Ψһ��һ�� CHMNWPDemoClientDlgApp ����
CHMNWPDemoClientDlgApp theApp;
HMSocketInit g_NWEInit;
hmnwp::HMNWPClient g_nwpClient( &(theApp.m_handler4NWP) );


// CHMNWPDemoClientDlgApp ��ʼ��

BOOL CHMNWPDemoClientDlgApp::InitInstance()
{

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CHMNWPDemoClientDlgDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

void CHMNWPDemoClientDlgApp::setConnState( ENUMCONNECTSTATE eConnState ) {
	m_eConnState = eConnState;
}

ENUMCONNECTSTATE CHMNWPDemoClientDlgApp::getConnState() const {
	return m_eConnState;
}
