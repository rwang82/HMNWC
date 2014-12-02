#include "stdafx.h"
#include "CRModuleLogin.h"
#include "CRClientMock.h"
#include "CRClientEvtDefs.h"
#include "CRClientMockDlg.h"
#include "CRClientTypes.h"
#include "CRCCommDefs.h"
#include "CRCCommProxyBase.h"
#include "CRTaskLogin.h"
#include "CRTaskLogoff.h"
#include "hm_nwc_types.h"
#include "atlconv.h"
#include <assert.h>
//
using namespace std::placeholders;
//
CRModuleLogin::CRModuleLogin()
: m_eLoginState( ELOGIN_STATE_LOGOFF )
, m_pfobj4OnLoginBtnClick( new hmcmn::hmcmn_event_depot::arg0event_handler_type( std::bind( &CRModuleLogin::_onLoginBtnClick, this ) ) )
, m_pfobj4OnConnected( new CRCCommProxyBase::arg0_funcobj_type( std::bind( &CRModuleLogin::_onConnected, this ) ) )
, m_pfobj4OnDisConnected( new CRCCommProxyBase::arg0_funcobj_type( std::bind( &CRModuleLogin::_onDisConnected, this ) ) )
, m_pfobj4LoginAck( new hmcmn::hmcmn_event_depot::arg2event_handler_type( std::bind( &CRModuleLogin::_onLoginAck, this, _1, _2 ) ) )
, m_pfobj4LogoffAck( new hmcmn::hmcmn_event_depot::arg2event_handler_type( std::bind( &CRModuleLogin::_onLogoffAck, this, _1, _2 ) ) )
{
	CRCCommProxyBase* pCommProxy4RMsg = NULL;

	pCommProxy4RMsg = theApp.m_commDepot.getCommProxy( ECRCCOMMPROXY_ID_RMSG );
	if ( !pCommProxy4RMsg ) {
	    assert( false );
		return;
	}
	//
	theApp.m_eventDepot.bind( ECRCE_ID_LOGIN_BTNCLICK, m_pfobj4OnLoginBtnClick );
	theApp.m_eventDepot.bind( ECRCE_ID_LOGIN_ACK, m_pfobj4LoginAck );
	theApp.m_eventDepot.bind( ECRCE_ID_LOGOFF_ACK, m_pfobj4LogoffAck );
	pCommProxy4RMsg->bindConnectedEvent( m_pfobj4OnConnected );
	pCommProxy4RMsg->bindDisConnectedEvent( m_pfobj4OnDisConnected );

}

CRModuleLogin::~CRModuleLogin() {
	CRCCommProxyBase* pCommProxy4RMsg = NULL;

	pCommProxy4RMsg = theApp.m_commDepot.getCommProxy( ECRCCOMMPROXY_ID_RMSG );
	if ( !pCommProxy4RMsg ) {
	    assert( false );
		return;
	}
	//
	if ( m_pfobj4OnLoginBtnClick ) {
	    theApp.m_eventDepot.unbind( ECRCE_ID_LOGIN_BTNCLICK, m_pfobj4OnLoginBtnClick );
	    delete m_pfobj4OnLoginBtnClick;
		m_pfobj4OnLoginBtnClick = NULL;
	}
	if ( m_pfobj4OnConnected ) {
	    pCommProxy4RMsg->unBindConnectedEvent( m_pfobj4OnConnected );
	    delete m_pfobj4OnConnected;
		m_pfobj4OnConnected = NULL;
	}
	if ( m_pfobj4OnDisConnected ) {
	    pCommProxy4RMsg->unBindDisConnectedEvent( m_pfobj4OnDisConnected );
	    delete m_pfobj4OnDisConnected;
		m_pfobj4OnDisConnected = NULL;
	}
	//
	if ( m_pfobj4LoginAck ) {
	    theApp.m_eventDepot.unbind( ECRCE_ID_LOGIN_ACK, m_pfobj4LoginAck );
		delete m_pfobj4LoginAck;
		m_pfobj4LoginAck = NULL;
	}
	//
	if ( m_pfobj4LogoffAck ) {
	    theApp.m_eventDepot.unbind( ECRCE_ID_LOGOFF_ACK, m_pfobj4LogoffAck );
		delete m_pfobj4LogoffAck;
		m_pfobj4LogoffAck = NULL;
	}
}

void CRModuleLogin::_onLoginAck( void* pParam1, void* pParam2 ) {
	_setLoginState( (1 == (int)pParam1) ? ELOGIN_STATE_LOGIN : ELOGIN_STATE_LOGOFF );
	
	CCRClientMockDlg* pMainDlg = (CCRClientMockDlg*)theApp.GetMainWnd();
	if ( pMainDlg ) {
	    if ( m_eLoginState == ELOGIN_STATE_LOGIN ) {		
		    pMainDlg->m_staticConnState.SetWindowText( STR_LOGIN_SUCCESS );
			pMainDlg->m_btnLogin.SetWindowText( _T("Logoff") );
		} else {
		    pMainDlg->m_staticConnState.SetWindowText( STR_LOGIN_FAILED );
		}
	}
}

void CRModuleLogin::_onConnected() {
	CCRClientMockDlg* pMainDlg = (CCRClientMockDlg*)theApp.GetMainWnd();
	if ( pMainDlg ) {
	    pMainDlg->m_staticConnState.SetWindowText( STR_CONNSTATE_CONNECTED );
	}
}

void CRModuleLogin::_onDisConnected() {
	CCRClientMockDlg* pMainDlg = (CCRClientMockDlg*)theApp.GetMainWnd();
	
	_setLoginState( ELOGIN_STATE_LOGOFF );
	if ( pMainDlg ) {
	    pMainDlg->m_staticConnState.SetWindowText( STR_CONNSTATE_DISCONNECTED );
			pMainDlg->m_btnLogin.SetWindowText( _T("Login") );
	}
}

void CRModuleLogin::_onLoginBtnClick() {
	switch ( getLoginState() )
	{
	case ELOGIN_STATE_LOGOFF:
	{
		_doLogin();
	}
		break;
	case ELOGIN_STATE_LOGIN:
	{
		_doLogoff();
	}
		break;
	case ELOGIN_STATE_LOGGING:
	case ELOGIN_STATE_LOGGINGOFF:
	{}
		break;
	default:
		break;
	}
}

void CRModuleLogin::_doLogin() {
	HMTaskEngine::task_id_type taskId;

	// if connected, just do nothing.
	// if disconnected, just connect to server.
	_enableConnect();
	//
	if ( !theApp.m_taskEngineMain.pushbackTask( new CRTaskLogin(), taskId ) ) {
	    assert( false ); 
	}
}

void CRModuleLogin::_enableConnect() {
	USES_CONVERSION;
	CCRClientMockDlg* pMainDlg = (CCRClientMockDlg*)theApp.GetMainWnd();
	tstring_type tstrIPAddrDest;
	int nPortDest;
	sockaddr_in sAddrRemote;
	CRCCommProxyBase* pCommProxy = NULL;
	
	pCommProxy = theApp.m_commDepot.getCommProxy( ECRCCOMMPROXY_ID_RMSG );
	if ( !pMainDlg || !pCommProxy || !pCommProxy->isDisConnected() ) {
		return;
	}

	//
	pMainDlg->getIPAddress( tstrIPAddrDest );
	pMainDlg->getPort( nPortDest );
	if ( tstrIPAddrDest.empty() || nPortDest == 0 ) {
		::MessageBox( NULL, _T( "IP地址或端口号无效！请重新输入..." ), _T( "温馨提示" ), MB_OK | MB_ICONWARNING );
		return;
	}
	//
	pMainDlg->m_staticConnState.SetWindowText( STR_CONNSTATE_CONNECTING );
	//
	sAddrRemote.sin_family = AF_INET;
	sAddrRemote.sin_port = ::ntohs( nPortDest );
	sAddrRemote.sin_addr.S_un.S_addr = ::inet_addr( T2A( tstrIPAddrDest.c_str() ) );
	pCommProxy->connect( sAddrRemote );
}

void CRModuleLogin::_doLogoff() {
	USES_CONVERSION;
	CCRClientMockDlg* pMainDlg = (CCRClientMockDlg*)theApp.GetMainWnd();
	CRCCommProxyBase* pCommProxy = NULL;
	HMTaskEngine::task_id_type taskId;
	
	pCommProxy = theApp.m_commDepot.getCommProxy( ECRCCOMMPROXY_ID_RMSG );
	
	if ( !pMainDlg || !pCommProxy || !pCommProxy->isConnected()) {
		assert( false );
		return;
	}
	
	_enableConnect();
	//
	if ( !theApp.m_taskEngineMain.pushbackTask( new CRTaskLogoff(), taskId ) ) {
	    assert( false ); 
	}

	//
	//pMainDlg->m_staticConnState.SetWindowText( STR_CONNSTATE_DISCONNECTING );
	//
	//pCommProxy->close();
}

ENUMLOGINSTATETYPE CRModuleLogin::getLoginState() const {
	return m_eLoginState;
}
	
void CRModuleLogin::_setLoginState( ENUMLOGINSTATETYPE eLoginState ) {
	m_eLoginState = eLoginState;
}

void CRModuleLogin::_onLogoffAck( void* pParam1, void* pParam2 ) {
	if ( (1 == (int)pParam1) ) {
	    _setLoginState( ELOGIN_STATE_LOGOFF );
	}

	CCRClientMockDlg* pMainDlg = (CCRClientMockDlg*)theApp.GetMainWnd();
	if ( pMainDlg ) {
	    if ( m_eLoginState == ELOGIN_STATE_LOGOFF ) {		
		    pMainDlg->m_staticConnState.SetWindowText( STR_LOGOFF_SUCCESS );
			pMainDlg->m_btnLogin.SetWindowText( _T("Login") );
		} else {
		    pMainDlg->m_staticConnState.SetWindowText( STR_LOGOFF_FAILED );
		}
	}
}