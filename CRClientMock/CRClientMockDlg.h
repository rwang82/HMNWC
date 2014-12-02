
// CRClientMockDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "tchar.h"
#include <string>
#include "CRDlgAccountReg.h"

// CCRClientMockDlg dialog
class CCRClientMockDlg : public CDialogEx
{
// Construction
public:
	CCRClientMockDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CRCLIENTMOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	void getIPAddress( std::basic_string< TCHAR >& tstrIPAddr );
	void getPort( int& nPort );

// Implementation
protected:
	HICON m_hIcon;
	CRDlgAccountReg m_dlgAccountReg;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLogin();
	CIPAddressCtrl m_ipaddrCtrlDest;
	CEdit m_editPort;
	CStatic m_staticConnState;
	CButton m_btnLogin;
	afx_msg void OnBnClickedAccountReg();
	CEdit m_editUserName;
	CEdit m_editPassword;
};
