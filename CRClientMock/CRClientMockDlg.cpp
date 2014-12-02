
// CRClientMockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CRClientMock.h"
#include "CRClientMockDlg.h"
#include "CRModuleIDDefs.h"
#include "CRModuleLogin.h"
#include "CRClientEvtDefs.h"
//#include "hm_nwc_types.h"
#include "afxdialogex.h"
#include <functional>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std::placeholders;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCRClientMockDlg dialog



CCRClientMockDlg::CCRClientMockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCRClientMockDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CCRClientMockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_IPADDRESS_DEST, m_ipaddrCtrlDest );
	DDX_Control( pDX, IDC_EDIT_PORT, m_editPort );
	DDX_Control( pDX, IDC_STATIC_CONNSTATE, m_staticConnState );
	DDX_Control( pDX, IDC_BTN_LOGIN, m_btnLogin );
	DDX_Control( pDX, IDC_EDIT1, m_editUserName );
	DDX_Control( pDX, IDC_EDIT2, m_editPassword );
}

BEGIN_MESSAGE_MAP(CCRClientMockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED( IDC_BTN_LOGIN, &CCRClientMockDlg::OnBnClickedBtnLogin )
	ON_BN_CLICKED( IDC_BTN_ACCOUNTREG, &CCRClientMockDlg::OnBnClickedAccountReg )
END_MESSAGE_MAP()


// CCRClientMockDlg message handlers

BOOL CCRClientMockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_ipaddrCtrlDest.SetWindowText(_T("127.0.0.1"));
	m_editPort.SetWindowText(_T("7654"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCRClientMockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCRClientMockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCRClientMockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCRClientMockDlg::OnBnClickedBtnLogin()
{
	theApp.m_eventDepot.fire( ECRCE_ID_LOGIN_BTNCLICK );
}

void CCRClientMockDlg::getIPAddress( std::basic_string< TCHAR >& tstrIPAddr ) {
	BYTE byte1;
	BYTE byte2;
	BYTE byte3;
	BYTE byte4;
	TCHAR szIPAddr[200];

	m_ipaddrCtrlDest.GetAddress( byte1, byte2, byte3, byte4 );
	_stprintf_s( szIPAddr, _T( "%d.%d.%d.%d" ), byte1, byte2, byte3, byte4 );
	tstrIPAddr = szIPAddr;
}

void CCRClientMockDlg::getPort( int& nPort ) {
	TCHAR szPort[100];
	
	m_editPort.GetWindowText( szPort, 100 );
	nPort = _ttoi(szPort);
}








void CCRClientMockDlg::OnBnClickedAccountReg()
{
	// TODO: Add your control notification handler code here
	m_dlgAccountReg.DoModal();
}
