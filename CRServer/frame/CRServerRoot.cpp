#include "stdafx.h"
#include "CRServerRoot.h"
#include "HMNWPServer.h"
#include "CRSrvEventHandler.h"
#include "CRSrvSettings.h"
#include "CRRMsgHandlerDepot.h"
#include "CRClientStubDepot.h"
#include "CRModuleDepot.h"
#include "CRModuleIDDefs.h"
#include "CRModuleCmdDispatch.h"
#include "CRModuleAccountMgr.h"
#include "CRModuleProductMgr.h"
#include "CRRCmdDefs.h"
#include "CRRMsgHandler4Login.h"
#include "CRRMsgHandler4Logoff.h"
#include "CRRMsgHandler4AccountReg.h"
#include "CRRMsgHandler4ProductPublish.h"
#include "CRRMsgHandler4AddAttetion.h"
#include "CRRMsgHandler4FetchAccountInfo.h"
#include "CRSrvDBProxy.h"
#include "hmcmn_event_depot.h"
#include "HMMisc.h"
#include "tchar.h"
#include <string>
//
#define MODULE_ADD( id, module_cls ) \
	do { \
		m_pModuleDepot->addModule( id, new module_cls() ); \
	} while( 0 )
#define CMDHANDLER_ADD( cmd_type, cmm_handler_cls ) \
	do { \
        m_pRMsgHandlerDepot->regRMsgHandler( cmd_type, new cmm_handler_cls() ); \
	} while( 0 )
//
CRServerRoot::CRServerRoot()
: m_pEventDepot( NULL )
, m_pModuleDepot( NULL )
, m_pRMsgHandlerDepot( NULL )
, m_pNWPServer( NULL )
, m_pSEHandler( NULL )
, m_pCRSrvSettings( NULL )
, m_pSrvDBProxy( NULL ) {
	_init();
}

CRServerRoot::~CRServerRoot() {
	_unInit();

}

void CRServerRoot::_init() {
	//

	//////////////////////////////////////////////////////////
	// no depends.
	m_pCRSrvSettings = new CRSrvSettings();
	m_pEventDepot = new hmcmn::hmcmn_event_depot();
	m_pModuleDepot = new CRModuleDepot();
	m_pClientStubDepot = new CRClientStubDepot();
	m_pSrvDBProxy = new CRSrvDBProxy();

	//////////////////////////////////////////////////////////
	// depends some.
	// depend on hmcmn_event_depot.
	m_pSEHandler = new CRSrvEventHandler();
	m_pNWPServer = new hmnwp::HMNWPServer(m_pSEHandler);
	// depend on hmcmn_event_depot.
	m_pRMsgHandlerDepot = new CRRMsgHandlerDepot();

	//////////////////////////////////////////////////////////
	// add modules.
	_initModules();

	//////////////////////////////////////////////////////////
	// add cmd handlers.
	_initCmdHandlers();

	//////////////////////////////////////////////////////////
    // start listen.
	if (!m_pCRSrvSettings->isReady()) {
		assert( false );
		return;
	}
	m_pNWPServer->listen( m_pCRSrvSettings->m_nListenPort );
}

void CRServerRoot::_initModules() {
	MODULE_ADD( ECRMODULE_ID_CMDDISPATCH, CRModuleCmdDispatch );
    MODULE_ADD( ECRMODULE_ID_ACCOUNTMGR, CRModuleAccountMgr );
	MODULE_ADD( ECRMODULE_ID_PRODUCTMGR, CRModuleProductMgr );
}

void CRServerRoot::_unInitModules() {
    if ( m_pModuleDepot ) {
	    m_pModuleDepot->deleteAllModule();
	}
}

void CRServerRoot::_initCmdHandlers() {
	CMDHANDLER_ADD( CRCMDTYPE_REQ_LOGIN, CRRMsgHandler4Login );
	CMDHANDLER_ADD( CRCMDTYPE_REQ_LOGOFF, CRRMsgHandler4Logoff );
	CMDHANDLER_ADD( CRCMDTYPE_REQ_ACCOUNT_REG, CRRMsgHandler4AccountReg );
	CMDHANDLER_ADD( CRCMDTYPE_REQ_PRODUCT_PUBLISH, CRRMsgHandler4ProductPublish );
	CMDHANDLER_ADD( CRCMDTYPE_REQ_ADD_ATTETION, CRRMsgHandler4AddAttetion );
    CMDHANDLER_ADD( CRCMDTYPE_REQ_FETCH_ACCOUNT_INFO, CRRMsgHandler4FetchAccountInfo );
} 

void CRServerRoot::_unInit( ) {
	// close socket.
	if ( m_pNWPServer ) {
	    m_pNWPServer->close();
	}
	// uninit modules.
	_unInitModules();

	//////////////////////////////////////////////////////////
	// depends some.
	if (m_pSEHandler) {
		delete m_pSEHandler;
		m_pSEHandler = NULL;
	}
	if ( m_pRMsgHandlerDepot ) {
	    delete m_pRMsgHandlerDepot;
		m_pRMsgHandlerDepot = NULL;
	}
	if (m_pNWPServer) {
		delete m_pNWPServer;
		m_pNWPServer = NULL;
	}

	//////////////////////////////////////////////////////////
	// no depends.
	if (m_pCRSrvSettings) {
		delete m_pCRSrvSettings;
		m_pCRSrvSettings = NULL;
	}
	if ( m_pEventDepot ) {
	    delete m_pEventDepot;
		m_pEventDepot = NULL;
	}
	if ( m_pModuleDepot ) {
	    delete m_pModuleDepot;
		m_pModuleDepot = NULL;
	}
	if ( m_pClientStubDepot ) {
	    delete m_pClientStubDepot;
		m_pClientStubDepot = NULL;
	}
	if ( m_pSrvDBProxy ) {
	    delete m_pSrvDBProxy;
		m_pSrvDBProxy = NULL;
	}
}



