#include "stdafx.h"
#include "HMNWPServer.h"
#include "HMNWEServer.h"
#include "HMNWPClientProxyDepot.h"
#include "HMNWPEventAdaptor4Server.h"
#include "HMNWPPackImpl.h"
#include "FuncPack.h"
HMNWP_NAMESPACE_BEGIN
//
#define HMNWPSERVER_FLAG_NONE (0x00000000)
#define HMNWPSERVER_FLAG_EXIT (0x00000001)
//
HMNWPServer::HMNWPServer( HMNWPEventHandler4Server* pEventHandler )
: m_pNWPCPDepot( NULL )
, m_pNWPEventAdaptor( NULL )
, m_pNWEServer( NULL )
, m_uFlag( HMNWPSERVER_FLAG_NONE ) {
	m_pNWPCPDepot = new HMNWPClientProxyDepot();
	m_pNWPEventAdaptor = new HMNWPEventAdaptor4Server( pEventHandler, m_pNWPCPDepot );
	m_pNWEServer = new HMNWEServer( m_pNWPEventAdaptor );
}

HMNWPServer::~HMNWPServer() {
	//
	m_uFlag |= HMNWPSERVER_FLAG_EXIT;
	//
	if ( m_pNWEServer ) {
		delete m_pNWEServer;
		m_pNWEServer = NULL;
	}
	if ( m_pNWPEventAdaptor ) {
		delete m_pNWPEventAdaptor;
		m_pNWPEventAdaptor = NULL;
	}
	if ( m_pNWPCPDepot ) {
		delete m_pNWPCPDepot;
		m_pNWPCPDepot = NULL;
	}
}

bool HMNWPServer::listen( SHORT sListenPort ) {
	if ( !m_pNWEServer )
		return false;
	return m_pNWEServer->listen( sListenPort );
}

void HMNWPServer::close() {
    if ( !m_pNWEServer )
		return;
	m_pNWEServer->close();
}

void HMNWPServer::send( SOCKET sConnect, const unsigned char* pBuf, unsigned int uLenBuf ) {
	if ( m_uFlag & HMNWPSERVER_FLAG_EXIT ) {
		return;
	}
	if ( !m_pNWEServer ) {
		return;
	}
	nwppackage_container_type containerNWPPackage;
	nwppackage_container_type::iterator itNWPPkg, iendNWPPkg;
	HMNWPPackage* pNWPPkg;
	//
	HMNWPPackImpl::createPackages( pBuf, uLenBuf, containerNWPPackage );
	CFuncPack fpkDestroyPackages( &HMNWPPackImpl::destroyPackages, &containerNWPPackage );
	//
	iendNWPPkg = containerNWPPackage.end();
	for ( itNWPPkg = containerNWPPackage.begin(); itNWPPkg != iendNWPPkg; ++itNWPPkg ) {
		pNWPPkg = *itNWPPkg;
		m_pNWEServer->send( sConnect, pNWPPkg->getBufData(), pNWPPkg->getLenBufData() );
	}

}

HMNWP_NAMESPACE_END
