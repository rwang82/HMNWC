#include "stdafx.h"
#include "CRTaskLogin.h"
#include "CRClientMock.h"
#include "CRCCommDefs.h"
#include "CRRCmdDefs.h"
#include "CRClientMockDlg.h"
#include <atlconv.h>

CRCmdParamsLogin::CRCmdParamsLogin()
: m_tstrAccoutName( _T("") )
, m_tstrPassword(_T("")) {
}

CRCmdParamsLogin::CRCmdParamsLogin( const CRCmdParamsLogin& val )
: m_tstrAccoutName( val.m_tstrAccoutName )
, m_tstrPassword( val.m_tstrPassword ) {
}

CRCmdParamsLogin::~CRCmdParamsLogin(){
}

CRTaskLogin::CRTaskLogin(){

}

CRTaskLogin::~CRTaskLogin() {

}

bool CRTaskLogin::_fillParams( Json::Value& valParams ) {
	CCRClientMockDlg* pLoginDlg = (CCRClientMockDlg*)theApp.GetMainWnd();
	CString strUserName;
	CString strPassword;
	USES_CONVERSION;

	if ( !pLoginDlg )
		return false;
	pLoginDlg->m_editUserName.GetWindowText( strUserName );
	pLoginDlg->m_editPassword.GetWindowText( strPassword );
	valParams[ "username" ] = T2A( (const TCHAR*) strUserName );
	valParams[ "password" ] = T2A( (const TCHAR*) strPassword );

	return true;
}

int CRTaskLogin::_getCmdType() const {
	return CRCMDTYPE_REQ_LOGIN;
}

//void CRTaskLogin::Run() {
//	char szCmd[] = "{ \
//       \"cmd\":{ \
//	       \"title\":\"req_login\", \
//		   \"type\":1, \
//           \"sn\":34252, \
//		   \"os\":100 \
//       }, \
//	   \"ver\":\"0.1\", \
//	   \"params\":{ \
//		  \"username\":\"rom.wang\", \
//		  \"password\":\"123456\" \
//	   } \
//    }";
//	CRCCommProxyBase* pCommProxy4RMsg = NULL;
//	
//	pCommProxy4RMsg = theApp.m_commDepot.getCommProxy( ECRCCOMMPROXY_ID_RMSG );
//	if ( !pCommProxy4RMsg )
//		return;
//	//
//	if ( !_waitConnected( pCommProxy4RMsg ) ) {
//		return;
//	}
//	//
//	pCommProxy4RMsg->send( (const unsigned char*)szCmd, strlen( szCmd )+1 );
//
//}
//
//bool CRTaskLogin::_waitConnected( CRCCommProxyBase* pCommProxy4RMsg ) {
//	if ( !pCommProxy4RMsg )
//		return false;
//	ENUMCRNWCONNECTSTATETYPE eConnState;
//
//	for ( int i = 0; i<5; ++i ) {
//	    eConnState = pCommProxy4RMsg->getConnState();    
//		switch ( eConnState )
//		{
//		case ECRNWCONN_STATE_CONNECTED:
//		{
//			return true;
//		}
//			break;
//		case ECRNWCONN_STATE_DISCONNECTED:
//		{
//		    return false;
//		}
//		    break;
//		default:
//			break;
//		}
//		//
//		Sleep( 500 );
//	}
//
//	return false;
//}