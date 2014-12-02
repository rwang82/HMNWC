#include "stdafx.h"
#include "HMTaskAcceptConnect.h"
#include "HMNWEClientProxyDepot.h"
#include "HMNWEServer.h"
#include "FuncPack.h"
#include "MemFuncPack.h"
#include <assert.h>
#include "winsock2.h"
#include "mswsock.h"
//
#define HMTAC_FLAG_NONE (0x00000000)
#define HMTAC_FLAG_INITSUCCESS (0x00000001)
//
HMTaskAcceptConnect::HMTaskAcceptConnect( HMNWEServer* pNWEFrame, SOCKET sListen, HANDLE hCompletion, HMNWEEventHandler4Server* pEventHandler )
: m_sListen(sListen)
, m_hCompletion(hCompletion)
, m_pNWEFrame(pNWEFrame)
, m_pfnAcceptEx(NULL)
, m_hEventAccept(NULL)
, m_uFlag(HMTAC_FLAG_NONE)
, m_pEventHandler( pEventHandler )
{
	_init();
}

HMTaskAcceptConnect::~HMTaskAcceptConnect() {
	_unInit();
}

void HMTaskAcceptConnect::_init() {
	//
	if ( !_loadFunc() ) {
		return; // failed.
	}
	//
	::CreateIoCompletionPort((HANDLE)m_sListen, m_hCompletion, (DWORD)0, 0);
	//
	m_hEventAccept = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	// if AcceptEx I/O not enough, thread will receive FD_ACCEPT network event,
	// means you should post AcceptEx I/O more.
	::WSAEventSelect(m_sListen, m_hEventAccept, FD_ACCEPT);
	//
	m_uFlag |= HMTAC_FLAG_INITSUCCESS;
}

void HMTaskAcceptConnect::_unInit() {
	if (m_hEventAccept) {
		::CloseHandle(m_hEventAccept);
		m_hEventAccept = NULL;
	}
}

void HMTaskAcceptConnect::Run() {
	if (!m_pNWEFrame || !m_pfnAcceptEx || ( !( m_uFlag & HMTAC_FLAG_INITSUCCESS ) ) ) {
		assert( false );
		return;
	}
	HANDLE aryEvent[ 3 ];
	DWORD dwWaitRet;

	while ( 1 )	{
		//
		if ( !_postAcceptReq( 5 ) ) {
			// need write some log.
		}
		//
		aryEvent[ 0 ] = m_hEventTaskEngineExit;
		aryEvent[ 1 ] = m_hEventCurTaskExit;
		aryEvent[ 2 ] = m_hEventAccept;
		dwWaitRet = ::WaitForMultipleObjects( 3, aryEvent, FALSE, INFINITE );
		//
		if ( dwWaitRet == WAIT_OBJECT_0 ) {
			break; // m_hEventTaskEngineExit
		} else if ( dwWaitRet == ( WAIT_OBJECT_0 + 1 ) ) {
			break; // m_hEventCurTaskExit
		} else if ( dwWaitRet == ( WAIT_OBJECT_0 + 2 ) ) {
			// m_hEventAccept, need more AcceptEx IO.
			continue;
		} else {
			assert( false );
		}
	}


}

bool HMTaskAcceptConnect::_loadFunc() {
	GUID guidAcceptEx = WSAID_ACCEPTEX;
	GUID guidGetAcceptExSockaddr = WSAID_GETACCEPTEXSOCKADDRS;
	DWORD dwBytes;
	int nRet;

	nRet = ::WSAIoctl(m_sListen,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&guidAcceptEx,
		sizeof( guidAcceptEx ),
		&m_pfnAcceptEx,
		sizeof( m_pfnAcceptEx ),
		&dwBytes,
		NULL,
		NULL );
	assert(nRet == 0);
	return ( ( m_pfnAcceptEx != NULL ) );
}

bool HMTaskAcceptConnect::_postAcceptReq(unsigned int uAcceptIOCount) {
	if ( !m_pfnAcceptEx ) {
		assert( false );
		return false;
	}
	HMNWEClientProxy* pNWECPNew = NULL;
	HMNWEClientDepot* pNWECPDepot = m_pNWEFrame->m_pClientDepot;
	SOCKET sAcceptNew;
	DWORD dwRecv = 0;
	BOOL bRes = FALSE;

	for ( unsigned int uAcceptIOIndex = 0; uAcceptIOIndex < uAcceptIOCount; ++uAcceptIOIndex ) {
		sAcceptNew = ::WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
		if ( sAcceptNew == INVALID_SOCKET ) {
			return false;
		}
		CFuncPack fpkCloseSocket( closesocket, sAcceptNew );
		CFuncPack fpkShutdownSocket( shutdown, sAcceptNew, SD_BOTH );
		//
		pNWECPNew = pNWECPDepot->createClientProxy( sAcceptNew, m_hCompletion, m_pEventHandler );
		if ( !pNWECPNew ) {
			return false;
		}
		CMemFuncPack mfpkRemoveCP( pNWECPDepot, &HMNWEClientDepot::removeClientProxy, pNWECPNew->getId() );
		//
		dwRecv = 0;
		bRes = m_pfnAcceptEx(
			m_sListen,
			sAcceptNew,
			pNWECPNew->m_szBufData4Accept,
			BUFSIZE_ACCEPT_NWDATA - ( ( sizeof( sockaddr_in )+16 ) * 2 ),
			sizeof( sockaddr_in )+16,
			sizeof( sockaddr_in )+16,
			&dwRecv,
			&( pNWECPNew->m_olAccept ) );
		if ( !bRes ) {
			DWORD dwErr = ::WSAGetLastError();
			if ( dwErr != WSA_IO_PENDING ) {
				assert( false );
				return false;
			}
		}
		//
		mfpkRemoveCP.Cancel();
		fpkCloseSocket.Cancel();
		fpkShutdownSocket.Cancel();
	}

	return true;
}