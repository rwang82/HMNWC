#include "stdafx.h"
#include "CRRMsgDispatcher.h"
#include "CRSrvRoot.h"
#include "CRSrvEvtDefs.h"
#include "CRTaskRMsgDispatch.h"
#include "CRTaskOnAccept.h"
#include "CRTaskOnDisConnect.h"
#include <functional>
//
using namespace std::placeholders;
//
CRRMsgDispatcher::CRRMsgDispatcher( CRSrvRoot* pSrvRoot )
: m_pSrvRoot( pSrvRoot )
, m_pFuncObjClientAccept( new hmcmn::hmcmn_event_depot::arg2event_handler_type( std::bind( &CRRMsgDispatcher::_onClientAccept, this, _1, _2 ) ) )
, m_pFuncObjClientDisConnect( new hmcmn::hmcmn_event_depot::arg2event_handler_type( std::bind( &CRRMsgDispatcher::_onClientDisConnect, this, _1, _2 ) ) )
, m_pFuncObjClientRequest( new hmcmn::hmcmn_event_depot::arg4event_handler_type( std::bind( &CRRMsgDispatcher::_onClientRequest, this, _1, _2, _3, _4 ) ) ) {
	//
	m_pSrvRoot->m_eventDepot.bind( ECRSRVEVT_CLIENT_ACCEPTED, m_pFuncObjClientAccept );
    m_pSrvRoot->m_eventDepot.bind( ECRSRVEVT_CLIENT_DISCONNECTED, m_pFuncObjClientDisConnect );
	m_pSrvRoot->m_eventDepot.bind( ECRSRVEVT_CLIENT_REQUEST, m_pFuncObjClientRequest );

}

CRRMsgDispatcher::~CRRMsgDispatcher() {
	//
	if ( m_pFuncObjClientAccept ) {
	    m_pSrvRoot->m_eventDepot.unbind( ECRSRVEVT_CLIENT_ACCEPTED, m_pFuncObjClientAccept );
	    delete m_pFuncObjClientAccept;
		m_pFuncObjClientAccept = NULL;
	}
	if ( m_pFuncObjClientDisConnect ) {
        m_pSrvRoot->m_eventDepot.unbind( ECRSRVEVT_CLIENT_DISCONNECTED, m_pFuncObjClientDisConnect );
	    delete m_pFuncObjClientDisConnect;
		m_pFuncObjClientDisConnect= NULL;
	}
	if ( m_pFuncObjClientRequest ) {
	    m_pSrvRoot->m_eventDepot.unbind( ECRSRVEVT_CLIENT_REQUEST, m_pFuncObjClientRequest );
	    delete m_pFuncObjClientRequest;
		m_pFuncObjClientRequest = NULL;
	}
}

void CRRMsgDispatcher::_onClientAccept( void* pParam1, void* pParam2 ) {
    SOCKET sConnect = (SOCKET)pParam1;
    const sockaddr_in* pAddr = (const sockaddr_in*)pParam2;
	HMTaskEngine::task_id_type taskId;

	m_taskEngine4CmdDispatch.pushbackTask( new CRTaskOnAccept( sConnect, pAddr, m_pSrvRoot ), taskId );
}

void CRRMsgDispatcher::_onClientDisConnect( void* pParam1, void* pParam2 ) {
    SOCKET sConnect = (SOCKET)pParam1;
    const sockaddr_in* pAddr = (const sockaddr_in*)pParam2;
	HMTaskEngine::task_id_type taskId;

	//
	m_taskEngine4CmdDispatch.pushbackTask( new CRTaskOnDisConnect( sConnect, pAddr, m_pSrvRoot ), taskId );
}

void CRRMsgDispatcher::_onClientRequest( void* pParam1, void* pParam2, void* pParam3, void* pParam4 ) {
    SOCKET sConnect = (SOCKET)pParam1;
    const sockaddr_in* pAddr = (const sockaddr_in*)pParam2;
	const unsigned char* pRawBuf = (const unsigned char*)pParam3;
    unsigned int uLenRawBuf = (unsigned int)pParam4;
	HMTaskEngine::task_id_type taskId;

	if ( !pAddr ) {
	    assert( false );
		return;
	}
	//
	m_taskEngine4CmdDispatch.pushbackTask( new CRTaskRMsgDispatch( sConnect, *pAddr, pRawBuf, uLenRawBuf, m_pSrvRoot ), taskId );
}


