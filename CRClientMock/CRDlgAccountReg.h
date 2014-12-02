#pragma once
#include "afxwin.h"


// CRDlgAccountReg dialog

class CRDlgAccountReg : public CDialogEx
{
	DECLARE_DYNAMIC(CRDlgAccountReg)

public:
	CRDlgAccountReg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRDlgAccountReg();

// Dialog Data
	enum { IDD = IDD_ACCOUNT_REG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editUserName;
	CEdit m_editPassword;
	CEdit m_editSort;
	afx_msg void OnBnClickedAccountReg();
	afx_msg void OnBnClickedAccountUnReg();
	CListBox m_listShowMsg;
};
