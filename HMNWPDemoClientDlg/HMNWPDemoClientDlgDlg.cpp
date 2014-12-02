
// HMNWPDemoClientDlgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HMNWPDemoClientDlg.h"
#include "HMNWPDemoClientDlgDlg.h"
#include "afxdialogex.h"
#include "HMNWPClient.h"
#include "hm_nwc_types.h"
#include "atlconv.h"

extern hmnwp::HMNWPClient g_nwpClient;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CHMNWPDemoClientDlgDlg �Ի���



CHMNWPDemoClientDlgDlg::CHMNWPDemoClientDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHMNWPDemoClientDlgDlg::IDD, pParent)
	, m_strIPAddr( _T( "" ) )
	, m_strConectInfo( _T( "" ) )
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	loadFont();
}

void CHMNWPDemoClientDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_IPADDRESS1, m_IPAddrCtrl4Dst );
	DDX_Control( pDX, IDC_EDIT1, m_edit4Port );
	DDX_Control( pDX, IDC_EDIT2, m_edit4SendMsg );
	DDX_Control( pDX, IDC_LIST2, m_lbServerMsg );
	DDX_Control( pDX, IDC_BTN_CONNECT, m_btnConnect );
}

BEGIN_MESSAGE_MAP(CHMNWPDemoClientDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED( IDC_BTN_CONNECT, &CHMNWPDemoClientDlgDlg::OnBnClickedBtnConnect )
	ON_BN_CLICKED( IDC_BTN_SEND, &CHMNWPDemoClientDlgDlg::OnBnClickedBtnSend )
END_MESSAGE_MAP()


// CHMNWPDemoClientDlgDlg ��Ϣ�������

BOOL CHMNWPDemoClientDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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
	//
	getHostIPAddr();
	m_IPAddrCtrl4Dst.SetAddress( 127, 0, 0, 1 );
	m_edit4Port.SetWindowText( _T( "4321" ) );
	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHMNWPDemoClientDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHMNWPDemoClientDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc( this ); // ���ڻ��Ƶ��豸������
		onDrawIPAddrTxt( dc );
		onDrawConectInfo( dc );
		//
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHMNWPDemoClientDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHMNWPDemoClientDlgDlg::OnBnClickedBtnConnect()
{
	USES_CONVERSION;
	unsigned short uPort;
	CString strIPAddr;
	sockaddr_in sAddrRemote;

	switch (g_nwpClient.getConnectState( ))
	{
	case EHMNWC_CONNSTATE_DISCONNECTED:
	{
		getServerPort( uPort );
		getIPAddr( strIPAddr );
		if (strIPAddr.IsEmpty( ) || uPort == 0) {
			::MessageBox( NULL, _T( "IP��ַ��˿ں���Ч������������..." ), _T( "��ܰ��ʾ" ), MB_OK | MB_ICONWARNING );
			return;
		}
		//
		theApp.setConnState( ECONN_STATE_CONNECTING );
		this->setConectStatus( _T("����������...") );
		this->updateConectStatus();
		//
		sAddrRemote.sin_family = AF_INET;
		sAddrRemote.sin_port = ::ntohs( uPort );
		sAddrRemote.sin_addr.S_un.S_addr = ::inet_addr( T2A( strIPAddr ) );
		g_nwpClient.connect( sAddrRemote );

		
	}
		break;
	case EHMNWC_CONNSTATE_CONNECTED:
	{
		theApp.setConnState( ECONN_STATE_DISCONNECTING );
		this->setConectStatus( _T("���ڶϿ�����") );
		this->updateConectStatus();
		g_nwpClient.close();
	}
		break;
	case EHMNWC_CONNSTATE_CONNECTING:
	case EHMNWC_CONNSTATE_DISCONNECTING:
	{}
		break;
	default:
		break;
	}
}


void CHMNWPDemoClientDlgDlg::OnBnClickedBtnSend()
{
	//char szData[] = "rom.wang here.";
	//g_nwpClient.send( ( const unsigned char* )szData, strlen( szData ) + 1 );
	USES_CONVERSION;
	char* pMsg = NULL;
	CString strMsg;
	getSendMsg( strMsg );
	pMsg = T2A( ( const TCHAR* )strMsg );
	g_nwpClient.send( ( const unsigned char* )pMsg, ( strlen( pMsg ) + 1 ) );
	//
	m_edit4SendMsg.SetWindowText( _T( "" ) );
}

void CHMNWPDemoClientDlgDlg::getHostIPAddr() {
	char szHost[256];
	CString strIPAddr;
	in_addr addr;

	::gethostname( szHost, 256 );
	hostent* pHost = ::gethostbyname( szHost );
	for ( int i = 0; ; i++ ) {
		char* p = pHost->h_addr_list[i];
		if ( p == NULL )
			break;
		memcpy( &addr.S_un.S_addr, p, pHost->h_length );
		strIPAddr = ::inet_ntoa( addr );
		m_strIPAddr += ( strIPAddr + _T( "   " ) );
	}
}

bool CHMNWPDemoClientDlgDlg::getIPAddrRect( RECT& rcIPAddr ) const {
	RECT rcClient;

	::GetClientRect( m_hWnd, &rcClient );
	rcIPAddr.left = rcClient.left + 165;
	rcIPAddr.right = rcClient.right;
	rcIPAddr.top = rcClient.top + 19;
	rcIPAddr.bottom = rcIPAddr.top + 20;

	return ( ( rcIPAddr.right > rcIPAddr.left ) && ( rcIPAddr.bottom > rcIPAddr.top ) );
}

void CHMNWPDemoClientDlgDlg::loadFont() {
	LOGFONT lFont;

	memset( &lFont, 0, sizeof(LOGFONT) );
	_tcscpy_s( lFont.lfFaceName, _T( "΢���ź�" ) );
	lFont.lfHeight = 18;

	m_hFontTxt = ::CreateFontIndirect( &lFont );
}

void CHMNWPDemoClientDlgDlg::onDrawIPAddrTxt( HDC hDC ) {
	HFONT hFontOld = NULL;
	RECT rcIPAddr;
	int iBkModeOld;
	
	if ( getIPAddrRect( rcIPAddr ) ) {
		hFontOld = (HFONT)::SelectObject( hDC, m_hFontTxt );
		iBkModeOld = ::SetBkMode( hDC, TRANSPARENT );
		::DrawText( hDC, m_strIPAddr, m_strIPAddr.GetLength(), &rcIPAddr, DT_LEFT|DT_SINGLELINE|DT_END_ELLIPSIS|DT_VCENTER );
		::SetBkMode( hDC, iBkModeOld );
		::SelectObject( hDC, hFontOld );
	}
}

void CHMNWPDemoClientDlgDlg::onDrawConectInfo( HDC hDC ) {
	HFONT hFontOld = NULL;
	RECT rcConectInfo;
	int iBkModeOld;

	if ( getConectInfoRect( rcConectInfo ) ) {
		hFontOld = ( HFONT )::SelectObject( hDC, m_hFontTxt );
		iBkModeOld = ::SetBkMode( hDC, TRANSPARENT );
		::DrawText( hDC, m_strConectInfo, m_strConectInfo.GetLength(), &rcConectInfo, DT_LEFT|DT_SINGLELINE|DT_END_ELLIPSIS|DT_VCENTER );
		::SetBkMode( hDC, iBkModeOld );
		::SelectObject( hDC, hFontOld );
	}
}

bool CHMNWPDemoClientDlgDlg::getConectInfoRect( RECT& rcConectInfo ) const {
	RECT rcClient;

	::GetClientRect( m_hWnd, &rcClient );
	rcConectInfo.left = rcClient.left + 95;
	rcConectInfo.right = rcClient.right;
	rcConectInfo.top = rcClient.top + 53;
	rcConectInfo.bottom = rcConectInfo.top + 20;

	return ( ( rcConectInfo.right > rcConectInfo.left ) && ( rcConectInfo.bottom > rcConectInfo.top ) );
}

void CHMNWPDemoClientDlgDlg::setConectStatus( const CString& strConectStatus ) {
	m_strConectInfo = strConectStatus;
}

void CHMNWPDemoClientDlgDlg::updateConectStatus() {
	if ( !::IsWindow( m_hWnd ) || !::IsWindowVisible( m_hWnd ) )
		return;
	RECT rcConectInfo;

	if ( getConectInfoRect( rcConectInfo ) ) {
		::InvalidateRect( m_hWnd, &rcConectInfo, TRUE );
	}
}

void CHMNWPDemoClientDlgDlg::getIPAddr( CString& strIPAddr ) {
	BYTE byte1;
	BYTE byte2;
	BYTE byte3;
	BYTE byte4;

	m_IPAddrCtrl4Dst.GetAddress( byte1, byte2, byte3, byte4 );
	strIPAddr.Format( _T("%d.%d.%d.%d"), byte1, byte2, byte3, byte4 );
}

void CHMNWPDemoClientDlgDlg::getServerPort( unsigned short& uPort ) {
	if ( !m_edit4Port.GetSafeHwnd() )
		return;
	TCHAR szData[512];

	::GetWindowText( m_edit4Port.GetSafeHwnd(), szData, _MAX_FNAME );
	uPort = _wtoi( szData );
}

void CHMNWPDemoClientDlgDlg::getSendMsg( CString& strMsg ) {
	if ( !m_edit4SendMsg.GetSafeHwnd() )
		return;

	m_edit4SendMsg.GetWindowText( strMsg );
}

void CHMNWPDemoClientDlgDlg::insertItem( const CString& strItem ) {
	if ( !m_lbServerMsg.GetSafeHwnd() )
		return;
	//m_lbServerMsg.AddString( strItem );
	m_lbServerMsg.InsertString( 0, strItem );
}