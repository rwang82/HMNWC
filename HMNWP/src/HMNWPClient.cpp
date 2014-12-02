#include "stdafx.h"
#include "HMNWPClient.h"
#include "HMNWEClient.h"
#include "HMNWPEventHandler4Client.h"
#include "HMNWPEventAdaptor4Client.h"
#include "HMNWPPackImpl.h"
#include "FuncPack.h"
#include <assert.h>
HMNWP_NAMESPACE_BEGIN

HMNWPClient::HMNWPClient( const HMNWPEventHandler4Client* pNWPEventHandler )
: m_pNWEClient( NULL )
, m_pNWPEventAdaptor( NULL ) {
	m_pNWPEventAdaptor = new HMNWPEventAdaptor4Client( pNWPEventHandler );
	m_pNWEClient = new HMNWEClient( m_pNWPEventAdaptor );
}

HMNWPClient::~HMNWPClient() {
	if ( m_pNWEClient ) {
		delete m_pNWEClient;
		m_pNWEClient = NULL;
	}
	if ( m_pNWPEventAdaptor ) {
		delete m_pNWPEventAdaptor;
		m_pNWPEventAdaptor = NULL;
	}
}

bool HMNWPClient::connect( const sockaddr_in& sAddrRemote ) {
	return m_pNWEClient->connect( sAddrRemote );
}

void HMNWPClient::close() {
	if (m_pNWEClient) {
		m_pNWEClient->close( );
	}
}

bool HMNWPClient::send( const unsigned char* pBuf, unsigned int uLenBuf ) {
	nwppackage_container_type containerNWPPackage;
	
	if ( !HMNWPPackImpl::createPackages( pBuf, uLenBuf, containerNWPPackage ) ) {
		assert( false );
		return false;
	}
	CFuncPack fpkDestroyPackages( &HMNWPPackImpl::destroyPackages, &containerNWPPackage );
	//
	for ( auto pNWPPackage : containerNWPPackage ) {
		if ( !m_pNWEClient->send( pNWPPackage->getBufData(), pNWPPackage->getLenBufData() ) )
			return false;
	}

	return true;
}

SOCKET HMNWPClient::getSocket() const { 
	return m_pNWEClient->getSocket();
}

const sockaddr_in HMNWPClient::getAddress() const {
    return m_pNWEClient->getAddress();
}

bool HMNWPClient::isConnected() const { 
	return m_pNWEClient->isConnected();
}

inline ENUMHMNWCCONNECTSTATETYPE HMNWPClient::getConnectState() const {
	return m_pNWEClient->getConnectState();
}

HMNWP_NAMESPACE_END










