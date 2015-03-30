#include "stdafx.h"
#include "CRSrvRoot.h"
#include "CRSrvEventHandler.h"

CRSrvRoot::CRSrvRoot( const CRRMsgListener* pRMsgListener )
: m_pRMsgListener( pRMsgListener )
, m_pRMsgDispatcher( new CRRMsgDispatcher( this ) )
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

