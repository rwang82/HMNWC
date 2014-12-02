#include "stdafx.h"
#include "HMTaskSendNWData4Server.h"
#include "HMNWEServer.h"
#include "HMNWESendReqDepot.h"
#include "HMNWEClientProxyDepot.h"

HMTaskSendNWData4Server::HMTaskSendNWData4Server( HMNWEClientDepot* pNWECPDepot, SOCKET sConnect, const unsigned char* pBuf, unsigned int uLenBuf )
: m_sConnect( sConnect )
, m_pNWECPDepot( pNWECPDepot )
, m_pBuf( NULL )
, m_uLenBuf( 0 )
{
	m_pBuf = new unsigned char[ uLenBuf ];
	memcpy( m_pBuf, pBuf, uLenBuf );
	m_uLenBuf = uLenBuf;
}

HMTaskSendNWData4Server::~HMTaskSendNWData4Server() {
	if ( m_pBuf ) {
		delete[] m_pBuf;
		m_pBuf = NULL;
	}
}

void HMTaskSendNWData4Server::Run() {
	if ( !m_pNWECPDepot || !m_pBuf || ( m_uLenBuf == 0 ) ) {
		return;
	}
	
	if ( !m_pNWECPDepot->send( m_sConnect, m_pBuf, m_uLenBuf ) ) {
		// write some log info.
	}
}