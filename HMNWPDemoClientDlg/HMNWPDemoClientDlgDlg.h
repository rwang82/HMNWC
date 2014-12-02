
// HMNWPDemoClientDlgDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"


// CHMNWPDemoClientDlgDlg 对话框
class CHMNWPDemoClientDlgDlg : public CDialogEx
{
// 构造
public:
	CHMNWPDemoClientDlgDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HMNWPDEMOCLIENTDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void setConectStatus( const CString& strConectStatus );
	afx_msg void updateConectStatus();
	afx_msg void insertItem( const CString& strItem );

private:
	afx_msg void loadFont();
	afx_msg void getHostIPAddr();
	afx_msg void onDrawIPAddrTxt( HDC hDC );
	afx_msg void onDrawConectInfo( HDC hDC );
	afx_msg bool getIPAddrRect( RECT& rcIPAddr ) const;
	afx_msg bool getConectInfoRect( RECT& rcConectInfo ) const;
	afx_msg void getIPAddr( CString& strIPAddr );
	afx_msg void getServerPort( unsigned short& uPort );
	afx_msg void getSendMsg( CString& strMsg );
	
private:
	CString m_strIPAddr;
	CString m_strConectInfo;
	HFONT m_hFontTxt;
	CIPAddressCtrl m_IPAddrCtrl4Dst;
	CEdit m_edit4Port;
	CEdit m_edit4SendMsg;
	CListBox m_lbServerMsg;
public:
	CButton m_btnConnect;
};
