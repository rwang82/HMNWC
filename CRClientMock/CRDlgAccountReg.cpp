// DlgAccountReg.cpp : implementation file
//

#include "stdafx.h"
#include "CRClientMock.h"
#include "CRDlgAccountReg.h"
#include "CRModuleAccountReg.h"
#include "CRClientEvtDefs.h"
#include "FuncPack.h"
#include "afxdialogex.h"


// CRDlgAccountReg dialog

IMPLEMENT_DYNAMIC(CRDlgAccountReg, CDialogEx)

CRDlgAccountReg::CRDlgAccountReg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRDlgAccountReg::IDD, pParent)
{

}

CRDlgAccountReg::~CRDlgAccountReg()
{
}

void CRDlgAccountReg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_EDIT1, m_editUserName );
	DDX_Control( pDX, IDC_EDIT2, m_editPassword );
	DDX_Control( pDX, IDC_EDIT3, m_editSort );
	DDX_Control( pDX, IDC_LIST1, m_listShowMsg );
}


BEGIN_MESSAGE_MAP(CRDlgAccountReg, CDialogEx)
	ON_BN_CLICKED( IDC_BUTTON1, &CRDlgAccountReg::OnBnClickedAccountReg )
	ON_BN_CLICKED( IDC_BUTTON2, &CRDlgAccountReg::OnBnClickedAccountUnReg )
END_MESSAGE_MAP()


// CRDlgAccountReg message handlers


void CRDlgAccountReg::OnBnClickedAccountReg()
{
	// TODO: Add your control notification handler code here
	CString strUserName;
	CString strPassword;
	CString strSort;
	AccountRegParam paramAccountReg;
	CFuncPack fpkShowMsg( ::MessageBox, (HWND)0, _T("param error, please try again!"), (LPCTSTR)0, (UINT)0 );

	//
	m_editUserName.GetWindowText( strUserName );
	if ( strUserName.GetLength() == 0 )
		return;
	paramAccountReg.m_tstrUserName = (const TCHAR*)strUserName;
	//
	m_editPassword.GetWindowText( strPassword );
	if ( strPassword.GetLength() == 0 )
		return;
	paramAccountReg.m_tstrPassword = (const TCHAR*)strPassword;
	//
	m_editSort.GetWindowText( strSort );
	if ( strSort.GetLength() == 0 )
		return;
	paramAccountReg.m_nSortType = _ttoi((const TCHAR*)strSort);
	//

	fpkShowMsg.Cancel();
	theApp.m_eventDepot.fire( ECRCE_ID_ACCOUNT_REG_BTNCLICK, &paramAccountReg, 0 );
	
}


void CRDlgAccountReg::OnBnClickedAccountUnReg()
{
	// TODO: Add your control notification handler code here
}
