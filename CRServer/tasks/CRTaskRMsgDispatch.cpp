#include "stdafx.h"
#include "CRTaskRMsgDispatch.h"
#include "CRRMsgParser.h"
#include "CRServerRoot.h"
#include "CRRMsgHandlerDepot.h"
#include "CRClientStubDepot.h"
#include "CRRMsgBase.h"
#include "CRLog.h"
#include "json/json.h"
#include "FuncPack.h"

CRTaskRMsgDispatch::CRTaskRMsgDispatch( SOCKET sConnect, const sockaddr_in& sAddr, const unsigned char* pRawBuf, unsigned int uLenRawBuf )
: m_rawRMsg( sConnect, sAddr, pRawBuf, uLenRawBuf ) {
}

CRTaskRMsgDispatch::~CRTaskRMsgDispatch() {
}

void CRTaskRMsgDispatch::Run() {
	CRRMsgBase* pRMsg = NULL;
	CRRMsgHandlerBase* pRMsgHandler = NULL;
	CRClientStub* pClientStub = NULL;
	
	// get pRMsg.
	pRMsg = CRRMsgParser::createRMsg( m_rawRMsg.m_pRawBuf, m_rawRMsg.m_uLenRawBuf );
	if ( !pRMsg )
		return; // we think it's no a valid remote message.
	CFuncPack fpkDelRMsg( ::gfnDelObj< CRRMsgBase >, pRMsg );
    // get pRMsgHandler.
	pRMsgHandler = g_CRSrvRoot.m_pRMsgHandlerDepot->getRMsgHandler( pRMsg->m_nCmdType );
	if ( !pRMsgHandler )
		return;
	// get pClientStub.
	//pClientStub = g_CRSrvRoot.m_pClientStubDepot->getClientStub( m_rawRMsg.m_metaData.m_sConnect );
	CRLOG_ERROR( "RecvRMsg: type:%d, os:%d, sn:%d", pRMsg->m_nCmdType, pRMsg->m_eOSType, pRMsg->m_nCmdSN );
	//
	pRMsg->execute( m_rawRMsg.m_metaData, pRMsgHandler );
}