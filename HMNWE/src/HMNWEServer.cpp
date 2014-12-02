#include "stdafx.h"
#include "HMNWEServer.h"
#include "HMTaskWaitIOEvent4Server.h"
#include "HMTaskSendNWData4Server.h"
#include "HMTaskAcceptConnect.h"
#include "HMNWEClientProxyDepot.h"
#include "HMTaskEngine.h"
#include "HMNWEEventHandler4Server.h"
#include "HMNWEFuncLoader4Server.h"
#include "HMSocketInit.h"
#include "FuncPack.h"
#include <assert.h>
//
#define INVALID_LISTEN_PORT (0xFFFFFFFF)
//
HMNWEServer::HMNWEServer( HMNWEEventHandler4Server* pEventHandler )
: m_hCompletion( NULL )
, m_pSocketInitObj( NULL )
, m_sListen( NULL )
, m_nListenPort( INVALID_LISTEN_PORT )
, m_pClientDepot( NULL )
, m_pEngine4WaitIOEvent( NULL )
, m_pEngine4Send(NULL)
, m_pEngine4Accept(NULL)
, m_pEventHandler( pEventHandler )
{
	_init();
}

HMNWEServer::~HMNWEServer() {
	_unInit();
}

void HMNWEServer::_init() {
	if (m_hCompletion || m_sListen || m_pClientDepot) {
		assert( false );
		return;
	}
	//
	m_pSocketInitObj = new HMSocketInit();
	//
	m_pEngine4WaitIOEvent = new HMTaskEngine();
	m_pEngine4Send = new HMTaskEngine();
	m_pEngine4Accept = new HMTaskEngine();
	//
	m_pClientDepot = new HMNWEClientDepot();
}

void HMNWEServer::_unInit() {
	//
	_close();
	//
	if (m_pEngine4WaitIOEvent) {
		delete m_pEngine4WaitIOEvent;
		m_pEngine4WaitIOEvent = NULL;
	}
	if (m_pEngine4Send) {
		delete m_pEngine4Send;
		m_pEngine4Send = NULL;
	}
	if (m_pEngine4Accept) {
		delete m_pEngine4Accept;
		m_pEngine4Accept = NULL;
	}
	if ( m_pClientDepot ) {
		delete m_pClientDepot;
		m_pClientDepot = NULL;
	}
	if (m_pSocketInitObj) {
		delete m_pSocketInitObj;
		m_pSocketInitObj = NULL;
	}
}

void HMNWEServer::_close() {
	//
	m_pEngine4WaitIOEvent->resetTaskQueue();
	//
	m_pEngine4WaitIOEvent->resetTaskQueue();
	//
	if ( m_sListen && ( m_sListen != INVALID_SOCKET ) ) {
		::shutdown( m_sListen, SD_BOTH );
		::closesocket( m_sListen );
		m_sListen = NULL;
	}
	//
	m_nListenPort = INVALID_LISTEN_PORT;
	//
	if ( m_hCompletion ) {
		::CloseHandle( m_hCompletion );
		m_hCompletion = NULL;
	}
}

bool HMNWEServer::listen( int nPort ) {
	if ( m_sListen != NULL || m_hCompletion != NULL) {
		assert( false );
		return false;
	}
	HMTaskEngine::task_id_type idTask;
	//
	m_sListen = _startListenPort( nPort );
	if ( !m_sListen || ( m_sListen == INVALID_SOCKET ) ) {
		return false;
	}
	m_nListenPort = nPort;
	//
	m_hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	//
	m_pEngine4WaitIOEvent->pushbackTask( new HMTaskWaitIOEvent4Server( this, m_hCompletion, m_pEventHandler ), idTask );
	//
	m_pEngine4Accept->pushbackTask( new HMTaskAcceptConnect( this, m_sListen, m_hCompletion, m_pEventHandler ), idTask );

	return true;
}

SOCKET HMNWEServer::_startListenPort(int nPort) {
	if (m_sListen) {
		assert( false );
		return NULL;
	}
	SOCKET sListen = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	CFuncPack fpkCloseSocket(::closesocket, sListen);
	CFuncPack fpkShutdownSocket(::shutdown, sListen, SD_BOTH);
	if (sListen == INVALID_SOCKET) {
		int nLastErr = ::WSAGetLastError();
		return NULL;
	}
	SOCKADDR_IN si;
	si.sin_family = AF_INET;
	si.sin_port = ::htons(nPort);
	si.sin_addr.S_un.S_addr = INADDR_ANY;
	if (0 != ::bind(sListen, (sockaddr*)&si, sizeof( si ))) {
		int nLastErr = ::WSAGetLastError();
		return NULL;
	}
	if (0 != ::listen(sListen, SOMAXCONN)){
		int nLastErr = ::WSAGetLastError();
		return NULL;
	}

	fpkShutdownSocket.Cancel();
	fpkCloseSocket.Cancel();
	return sListen;
}

void HMNWEServer::send( SOCKET sConnect, const unsigned char* pBuf, unsigned int uLenBuf ) {
	HMTaskSendNWData4Server* pTaskSendNWData = NULL;
	HMTaskEngine::task_id_type idTask;

	pTaskSendNWData = new HMTaskSendNWData4Server( m_pClientDepot, sConnect, pBuf, uLenBuf );
	m_pEngine4Send->pushbackTask( pTaskSendNWData, idTask );
	
	return ;
}


