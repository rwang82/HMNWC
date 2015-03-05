#include "stdafx.h"
#include "CRSrvRoot.h"
#include "CRSrvEventHandler.h"

CRSrvRoot::CRSrvRoot( CRClientStubFactoryBase* pCSF )
: m_pCSF( pCSF )
, m_clientStubDepot( this )
, m_nwpServer( new CRSrvEventHandler( &m_eventDepot ) ){
	_init();
}

CRSrvRoot::~CRSrvRoot() {
	_unInit();
}

void CRSrvRoot::_init() {
	

}

void CRSrvRoot::_unInit() {

}

