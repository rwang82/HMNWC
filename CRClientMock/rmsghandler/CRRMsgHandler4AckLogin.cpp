#include "stdafx.h"
#include "CRRMsgHandler4AckLogin.h"
#include "CRRMsg.h"
#include "CRClientMock.h"
#include "CRClientEvtDefs.h"

CRRMsgHandler4AckLogin::CRRMsgHandler4AckLogin() {

}

CRRMsgHandler4AckLogin::~CRRMsgHandler4AckLogin() {

}

void CRRMsgHandler4AckLogin::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
	if ( _isLoginSuccess( pRMsgJson ) ) {
	    theApp.m_eventDepot.fire( ECRCE_ID_LOGIN_ACK, (void*)1, (void*)0 );
	} else {
	    theApp.m_eventDepot.fire( ECRCE_ID_LOGIN_ACK, (void*)0, (void*)0 );
	}
}

void CRRMsgHandler4AckLogin::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary ) {

}

bool CRRMsgHandler4AckLogin::_isLoginSuccess( const CRRMsgJson* pRMsgJson ) {
    const Json::Value& valParams = pRMsgJson->m_jsonRoot[ "params" ];
	if ( !valParams.isObject() )
		return false;
	const Json::Value& valResult = valParams[ "result" ];
	if ( !valResult.isInt() )
		return false;
	return (valResult.asInt() == 1);
}
