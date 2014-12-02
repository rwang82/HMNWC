#include "stdafx.h"
#include "HMNWPHandler4ClientDemo.h"
#include "HMNWPDemoClientDlgDlg.h"
#include "HMNWPDemoClientDlg.h"
#include "HMNWPClient.h"
//
extern hmnwp::HMNWPClient g_nwpClient;
//
HMNWPHandler4ClientDemo::HMNWPHandler4ClientDemo() {

}

HMNWPHandler4ClientDemo::~HMNWPHandler4ClientDemo() {

}

void HMNWPHandler4ClientDemo::onConnect() const {
	CHMNWPDemoClientDlgDlg* pClientDlg = (CHMNWPDemoClientDlgDlg*)theApp.m_pMainWnd;
	//
	theApp.setConnState( ECONN_STATE_CONNECTED );

	//
	if (pClientDlg) {
		pClientDlg->m_btnConnect.SetWindowText( _T( "DisConnect" ) );
		pClientDlg->setConectStatus( _T( "连接成功！" ) );
		pClientDlg->updateConectStatus();
	}
}

void HMNWPHandler4ClientDemo::onDisConnect() const {
	CHMNWPDemoClientDlgDlg* pClientDlg = ( CHMNWPDemoClientDlgDlg* )theApp.m_pMainWnd;
	//
	theApp.setConnState( ECONN_STATE_DISCONNECT );

	//
	if (pClientDlg) {
		pClientDlg->m_btnConnect.SetWindowText( _T( "Connect" ) );
		pClientDlg->setConectStatus( _T( "连接失败！" ) );
		pClientDlg->updateConectStatus();
	}
}

void HMNWPHandler4ClientDemo::onRecvBuffer( const unsigned char* pBuf, unsigned int uLenBuf ) const{
	CHMNWPDemoClientDlgDlg* pClientDlg = ( CHMNWPDemoClientDlgDlg* )theApp.m_pMainWnd;
	SOCKET sConnect;

	sConnect = g_nwpClient.getSocket();
	if ( pClientDlg ) {
		pClientDlg->insertItem( (CString)(pBuf) );
	}
}