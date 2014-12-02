#include "stdafx.h"
#include "CRTaskLogoff.h"
#include "CRClientMock.h"
#include "CRCCommDefs.h"
#include "CRRCmdDefs.h"
#include "CRClientMockDlg.h"
#include <atlconv.h>

CRTaskLogoff::CRTaskLogoff() {

}

CRTaskLogoff::~CRTaskLogoff() {

}

bool CRTaskLogoff::_fillParams( Json::Value& valParams ) {
	CCRClientMockDlg* pLoginDlg = (CCRClientMockDlg*)theApp.GetMainWnd();
	CString strUserName;
	USES_CONVERSION;

	pLoginDlg->m_editUserName.GetWindowText( strUserName );
	valParams[ "username" ] = T2A( (const TCHAR*)strUserName );
	return true;
}

int CRTaskLogoff::_getCmdType() const {
	return CRCMDTYPE_REQ_LOGOFF;
}















