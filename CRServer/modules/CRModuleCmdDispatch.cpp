#include "stdafx.h"
#include "CRModuleCmdDispatch.h"
#include "CRServerRoot.h"
#include "CRSrvEvtDefs.h"
#include "CRTaskRMsgDispatch.h"
#include "CRTaskClientAccept.h"
#include "CRTaskClientDisConnect.h"
#include <functional>
//
using namespace std::placeholders;
//
CRModuleCmdDispatch::CRModuleCmdDispatch()
: m_pFuncObjClientAccept( new hmcmn::hmcmn_event_depot::arg2event_handler_type( std::bind( &CRModuleCmdDispatch::_onClientAccept, this, _1, _2 ) ) )
, m_pFuncObjClientDisConnect( new hmcmn::hmcmn_event_depot::arg2event_handler_type( std::bind( &CRModuleCmdDispatch::_onClientDisConnect, this, _1, _2 ) ) )
, m_pFuncObjClientRequest( new hmcmn::hmcmn_event_depot::arg4event_handler_type( std::bind( &CRModuleCmdDispatch::_onClientRequest, this, _1, _2, _3, _4 ) ) ) {
	//
	g_CRSrvRoot.m_pEventDepot->bind( ECRSRVEVT_CLIENT_ACCEPTED, m_pFuncObjClientAccept );
    g_CRSrvRoot.m_pEventDepot->bind( ECRSRVEVT_CLIENT_DISCONNECTED, m_pFuncObjClientDisConnect );
	g_CRSrvRoot.m_pEventDepot->bind( ECRSRVEVT_CLIENT_REQUEST, m_pFuncObjClientRequest );

}

CRModuleCmdDispatch::~CRModuleCmdDispatch() {
	//
	if ( m_pFuncObjClientAccept ) {
	    g_CRSrvRoot.m_pEventDepot->unbind( ECRSRVEVT_CLIENT_ACCEPTED, (hmcmn::hmcmn_event_depot::arg2event_handler_type*)m_pFuncObjClientAccept );
	    delete m_pFuncObjClientAccept;
		m_pFuncObjClientAccept = NULL;
	}
	if ( m_pFuncObjClientDisConnect ) {
        g_CRSrvRoot.m_pEventDepot->unbind( ECRSRVEVT_CLIENT_DISCONNECTED, m_pFuncObjClientDisConnect );
	    delete m_pFuncObjClientDisConnect;
		m_pFuncObjClientDisConnect= NULL;
	}
	if ( m_pFuncObjClientRequest ) {
	    g_CRSrvRoot.m_pEventDepot->unbind( ECRSRVEVT_CLIENT_REQUEST, m_pFuncObjClientRequest );
	    delete m_pFuncObjClientRequest;
		m_pFuncObjClientRequest = NULL;
	}
}

void CRModuleCmdDispatch::_onClientAccept( void* pParam1, void* pParam2 ) {
    SOCKET sConnect = (SOCKET)pParam1;
    const sockaddr_in* pAddr = (const sockaddr_in*)pParam2;
	HMTaskEngine::task_id_type taskId;

	m_taskEngine4CmdDispatch.pushbackTask( new CRTaskClientAccept( sConnect, pAddr ), taskId );
}

void CRModuleCmdDispatch::_onClientDisConnect( void* pParam1, void* pParam2 ) {
    SOCKET sConnect = (SOCKET)pParam1;
    const sockaddr_in* pAddr = (const sockaddr_in*)pParam2;
	HMTaskEngine::task_id_type taskId;

	//
	m_taskEngine4CmdDispatch.pushbackTask( new CRTaskClientDisConnect( sConnect, pAddr ), taskId );
}

void CRModuleCmdDispatch::_onClientRequest( void* pParam1, void* pParam2, void* pParam3, void* pParam4 ) {
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
	m_taskEngine4CmdDispatch.pushbackTask( new CRTaskRMsgDispatch( sConnect, *pAddr, pRawBuf, uLenRawBuf ), taskId );
}


