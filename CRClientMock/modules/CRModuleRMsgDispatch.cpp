#include "stdafx.h"
#include "CRModuleRMsgDispatch.h"
#include "CRClientMock.h"
#include "CRCCommDefs.h"
#include "CRRMsgParser.h"
#include "CRRMsgBase.h"
#include "CRTaskRMsgDispatch.h"
#include <assert.h>
#include <functional>
//
using namespace std::placeholders;
//
CRModuleRMsgDispatch::CRModuleRMsgDispatch()
: m_pFuncObj4RecvBuffer( new CRCCommProxyBase::arg2_funcobj_type( std::bind( &CRModuleRMsgDispatch::_onRecvBuffer, this, _1, _2 ) ) ) {
	CRCCommProxyBase* pCommProxy4RMsg = (CRCCommProxyBase*)theApp.m_commDepot.getCommProxy( ECRCCOMMPROXY_ID_RMSG );

    if ( !pCommProxy4RMsg ) {
	    assert( false );
		return;
	}
	//
	pCommProxy4RMsg->bindRecvBufferEvent( m_pFuncObj4RecvBuffer );
}

CRModuleRMsgDispatch::~CRModuleRMsgDispatch() {
	CRCCommProxyBase* pCommProxy4RMsg = (CRCCommProxyBase*)theApp.m_commDepot.getCommProxy( ECRCCOMMPROXY_ID_RMSG );

    if ( !pCommProxy4RMsg ) {
	    assert( false );
		return;
	}
	if ( m_pFuncObj4RecvBuffer ) {
		pCommProxy4RMsg->unBindRecvBufferEvent( m_pFuncObj4RecvBuffer );
		delete m_pFuncObj4RecvBuffer;
		m_pFuncObj4RecvBuffer = NULL;
	}
}

void CRModuleRMsgDispatch::_onRecvBuffer( void* pParam1, void* pParam2 ) {
	const unsigned char* pRawBuf = (const unsigned char*)pParam1;
	unsigned int uLenRawBuf = (unsigned int)pParam2;
	HMTaskEngine::task_id_type taskId;

    m_taskEngine4CmdDispatch.pushbackTask( new CRTaskRMsgDispatch( pRawBuf, uLenRawBuf ), taskId );

}