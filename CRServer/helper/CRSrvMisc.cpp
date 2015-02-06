#include "stdafx.h"
#include "CRSrvMisc.h"
#include "CRRMsg.h"
#include "CRRMsgMaker.h"
#include "CRServerRoot.h"
#include "HMNWPServer.h"
#include "Json/json.h"
#include <atlconv.h>


void gfnSendFailedAck( const CRRMsgMetaData& rmsgMetaData, int nRMsgAckType, int nErrCode ) {
	Json::Value valParams;
	std::string strRMsg;
	USES_CONVERSION;

	valParams[ "result" ] = 0;
	valParams[ "reason" ] = nErrCode;
	CRRMsgMaker::createRMsg( valParams, nRMsgAckType, strRMsg );
	//
	g_CRSrvRoot.m_pNWPServer->send( rmsgMetaData.m_sConnect, (const unsigned char*)strRMsg.c_str(), strRMsg.length() + 1 );
}