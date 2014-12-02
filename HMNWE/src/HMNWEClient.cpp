#include "stdafx.h"
#include "HMNWEClient.h"
#include "HMTaskEngine.h"
#include "HMTaskConnect2Remote.h"
#include "HMTaskWaitIOEvent4Client.h"
#include "HMNWEServerProxy.h"
#include "HMNWESendReqDepot.h"
#include "HMNWERecvReqDepot.h"
#include "HMNWEEventHandler4Client.h"
#include "HMSocketInit.h"
#include "hm_nwc_types.h"
#include "funcpack.h"
#include "memfuncpack.h"
#include <assert.h>
#include "mswsock.h"
//
#ifndef HITTEST_BIT
#define HITTEST_BIT( val, bit ) ( ( val & bit ) == bit )
#endif //HITTEST_BIT
//
#define HMNWECLIENT_FLAG_NONE (0x00000000)
#define HMNWECLIENT_FLAG_INITSUCCESS (0x00000001)
//
HMNWEClient::HMNWEClient( const HMNWEEventHandler4Client* pEventHandler )
: m_uFlag( HMNWECLIENT_FLAG_NONE )
, m_eConnState( EHMNWC_CONNSTATE_DISCONNECTED )
, m_pSocketInitObj( NULL )
, m_hCompletion( NULL )
, m_sConnect( NULL )
, m_pEngine4Connect( NULL )
, m_pEngine4WaitIOEvent( NULL )
, m_pOLConnect( NULL )
, m_pSendReqDepot( NULL )
, m_pEventHandler( pEventHandler ) {
	_init();
}

HMNWEClient::~HMNWEClient() {
	_unInit();
}

bool HMNWEClient::connect( const sockaddr_in& sAddrRemote ) {
	switch ( getConnectState() )
	{
	case EHMNWC_CONNSTATE_CONNECTING:
	case EHMNWC_CONNSTATE_CONNECTED:
	case EHMNWC_CONNSTATE_DISCONNECTING:
	{
		assert( false );
		return false;
	}
		break;
	case EHMNWC_CONNSTATE_DISCONNECTED:
	{
		if (!(m_uFlag & HMNWECLIENT_FLAG_INITSUCCESS)) {
			return false;
		}
		return _connect( sAddrRemote );
	}
		break;
	default:
		assert( false );
		break;
	}

	return false;
}

void HMNWEClient::close() {
	switch ( getConnectState() )
	{
	case EHMNWC_CONNSTATE_DISCONNECTED:
	case EHMNWC_CONNSTATE_DISCONNECTING:
	case EHMNWC_CONNSTATE_CONNECTING:
	{
		assert( false );
		return;
	}
	case EHMNWC_CONNSTATE_CONNECTED:
	{
		_close();
		return;
	}
		break;
	default:
		assert( false );
		break; 
	}
}

bool HMNWEClient::_init() {
	if ( m_pEngine4Connect || m_pEngine4WaitIOEvent ) {
		assert( false );
		return false;
	}
	m_pSocketInitObj = new HMSocketInit();
	m_pSendReqDepot = new HMNWESendReqDepot();
	m_pRecvReqDepot = new HMNWERecvReqDepot();
	m_pEngine4Connect = new HMTaskEngine();
	m_pEngine4WaitIOEvent = new HMTaskEngine();
	m_pOLConnect = new OVERLAPPED();
	m_uFlag |= HMNWECLIENT_FLAG_INITSUCCESS;
	return true;
}

void HMNWEClient::_unInit() {
	//
	_reset();
	//
	if ( m_pEngine4WaitIOEvent ) {
		delete m_pEngine4WaitIOEvent;
		m_pEngine4WaitIOEvent = NULL;
	}
	//
	if ( m_pEngine4Connect ) {
		delete m_pEngine4Connect;
		m_pEngine4Connect = NULL;
	}
	if ( m_pOLConnect ) {
		delete m_pOLConnect;
		m_pOLConnect = NULL;
	}
	if ( m_pRecvReqDepot ) {
		delete m_pRecvReqDepot;
		m_pRecvReqDepot = NULL;
	}
	if ( m_pSendReqDepot ) {
		delete m_pSendReqDepot;
		m_pSendReqDepot = NULL;
	}
	if (m_pSocketInitObj) {
		delete m_pSocketInitObj;
		m_pSocketInitObj = NULL;
	}
	//
	m_uFlag &= ~HMNWECLIENT_FLAG_INITSUCCESS;
}

void HMNWEClient::_setConnectState( ENUMHMNWCCONNECTSTATETYPE eConnState ) {
	m_eConnState = eConnState;
}

ENUMHMNWCCONNECTSTATETYPE HMNWEClient::getConnectState() const {
	return m_eConnState;
}

bool HMNWEClient::_connect( const sockaddr_in& sAddrRemote ) {
	assert( m_eConnState == EHMNWC_CONNSTATE_DISCONNECTED );
	SOCKADDR_IN si;
	DWORD dwErr;
	HMTaskEngine::task_id_type idTask;

	//
	_reset();
	//
	_setConnectState( EHMNWC_CONNSTATE_CONNECTING );
	//
	m_hCompletion = ::CreateIoCompletionPort( INVALID_HANDLE_VALUE, 0, 0, 0 );
	//
	m_sConnect = ::WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
	//
	si.sin_family = AF_INET;
	si.sin_port = ::ntohs( 0 );
	si.sin_addr.S_un.S_addr = INADDR_ANY;
	if ( 0 != ::bind( m_sConnect, ( sockaddr* )&si, sizeof( si ) ) ) {
		dwErr = ::WSAGetLastError();
		_setConnectState( EHMNWC_CONNSTATE_DISCONNECTED );
		return false;
	}
	//
	CreateIoCompletionPort( ( HANDLE )m_sConnect, m_hCompletion, ( DWORD )0, 0 );
	//
	::memset( m_pOLConnect, 0, sizeof( OVERLAPPED ) );
	//
	m_pEngine4WaitIOEvent->pushbackTask( new HMTaskWaitIOEvent4Client( this, m_hCompletion ), idTask );
	m_pEngine4Connect->pushbackTask( new HMTaskConnect2Remote( this, sAddrRemote ), idTask );
	//
	m_sAddrRemote = sAddrRemote;
	::Sleep(16);
	return true;
}

void HMNWEClient::_close() {
	if (m_eConnState == EHMNWC_CONNSTATE_DISCONNECTED) {
		assert( false );
		return;
	}
	//
	_setConnectState( EHMNWC_CONNSTATE_DISCONNECTING );
	//
	_reset();
}

void HMNWEClient::_reset() {
	if ( m_sConnect && ( m_sConnect != INVALID_SOCKET ) ) {
		shutdown( m_sConnect, SD_BOTH );
		closesocket( m_sConnect );
		m_sConnect = NULL;
	}
	//
	if ( m_hCompletion ) {
		::CloseHandle( m_hCompletion );
		m_hCompletion = NULL;
	}
	//
	m_pEngine4WaitIOEvent->resetTaskQueue();
	m_pEngine4Connect->resetTaskQueue();
}

bool HMNWEClient::_parseOLPTR( const OVERLAPPED* pOL, ENUMIOEVENTTYPE4CLIENT& eIOEvent ) {
	if ( !pOL ) {
		eIOEvent = EIOEVENT4CLIENT_TYPE_UNKNOWN; 
		return false;
	}

	if ( pOL == m_pOLConnect ) {
		eIOEvent = EIOEVENT4CLIENT_TYPE_CONNECT;
		return true;
	}

	if ( m_pSendReqDepot->hasReq( pOL ) ){
		eIOEvent = EIOEVENT4CLIENT_TYPE_SEND;
		return true;
	}

	if ( m_pRecvReqDepot->hasRecvReq( pOL ) ) {
		eIOEvent = EIOEVENT4CLIENT_TYPE_RECV;
		return true;
	}

	eIOEvent = EIOEVENT4CLIENT_TYPE_UNKNOWN;
	return false;
}

void HMNWEClient::_onIOEvt( ENUMIOEVENTTYPE4CLIENT eIOEvt4Client, OVERLAPPED* pOL, DWORD dwTrans ) {
	switch ( eIOEvt4Client )
	{
	case EIOEVENT4CLIENT_TYPE_CONNECT:
		// it's a dummy, replace by _onEvtConnectSuccess.
		break;
	case EIOEVENT4CLIENT_TYPE_RECV:
		{
		if ( m_pEventHandler && pOL) {
			HMNWERecvReq* pRecvReq = ( HMNWERecvReq* )pOL;
			assert( dwTrans <= pRecvReq->m_uLenBuf );
			if ( dwTrans == 0 ) {
				m_pEventHandler->onDisConnect();
			} else {
				m_pEventHandler->onRecv( pRecvReq->m_pBufNWData, dwTrans );
			}
		}

		if ( dwTrans == 0 ) {
			_setConnectState( EHMNWC_CONNSTATE_DISCONNECTED );
			m_pRecvReqDepot->clearAllReq();
		} else {
			m_pRecvReqDepot->removeReq( pOL );
			_postRecvReq( 1 );
		}
		}
		break;
	case EIOEVENT4CLIENT_TYPE_SEND:
		m_pSendReqDepot->removeReq( pOL );
		break;
	default:
		break;
	}
}

void HMNWEClient::_onEvtConnectFailed() {
	_setConnectState( EHMNWC_CONNSTATE_DISCONNECTED );
	if ( m_pEventHandler ) {
		m_pEventHandler->onDisConnect();
	}
	::shutdown( m_sConnect,SD_BOTH );
	::closesocket( m_sConnect );
	//
	_clearRecvReq();
}

void HMNWEClient::_onEvtConnectSuccess() {
	_setConnectState( EHMNWC_CONNSTATE_CONNECTED );
	if ( m_pEventHandler ) {
		m_pEventHandler->onConnect();
	}
	
	//_postRecvReq( 5 );
	_postRecvReq( 1 );
}

bool HMNWEClient::_isConnected() const {
	return m_eConnState == EHMNWC_CONNSTATE_CONNECTED;
}

bool HMNWEClient::send( const unsigned char* pBuf, unsigned int uLenBuf ) {
	if ( !pBuf || ( uLenBuf == 0 ) || !_isConnected() ) {
		return false;
	}
	HMNWESendReq* pSendReq = NULL;
	int nRes;
	DWORD dwTrans;
	DWORD dwFlag;
	DWORD dwErr;
	WSABUF wsaBuf;

	pSendReq = m_pSendReqDepot->createReq( pBuf, uLenBuf );
	wsaBuf.buf = (char*)pSendReq->m_pBufNWData;
	wsaBuf.len = pSendReq->m_uLenBuf;
	dwFlag = 0;
	nRes = ::WSASend( m_sConnect, &wsaBuf, 1, &dwTrans, dwFlag, &pSendReq->m_ol, NULL );
	if ( nRes != 0 ) {
		dwErr = ::WSAGetLastError();
		if ( dwErr != WSA_IO_PENDING ) {
			assert( false );
			return false;
		}
	}

	return true;
}

void HMNWEClient::_clearRecvReq() {
	m_pRecvReqDepot->clearAllReq();
}

bool HMNWEClient::_postRecvReq( unsigned int uReqCount ) {
	const HMNWERecvReq* pRecvReq = NULL;
	WSABUF buf;
	DWORD dwTrans;
	DWORD dwFlags;
	int nRes;
	DWORD dwErr;

	for ( unsigned int uReqIndex = 0; uReqIndex < uReqCount; ++uReqIndex ) {
		pRecvReq = m_pRecvReqDepot->createRecvReq();
		buf.buf = (char*)pRecvReq->m_pBufNWData;
		buf.len = pRecvReq->m_uLenBuf;
		dwTrans = 0;
		dwFlags = 0;
		nRes = ::WSARecv( m_sConnect, &buf, 1, &dwTrans, &dwFlags, (LPWSAOVERLAPPED)&( pRecvReq->m_ol ), NULL );
		if ( nRes != 0 ) {
			dwErr = ::WSAGetLastError();
			if ( dwErr != WSA_IO_PENDING ) {
				if ( dwErr == WSAENOTSOCK ) { // 

					break;
				}
				assert( false );
				return false;
			}
		}
	}

	return true;
}




