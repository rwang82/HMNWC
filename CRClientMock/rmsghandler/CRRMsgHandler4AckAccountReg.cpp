#include "stdafx.h"
#include "CRRMsgHandler4AckAccountReg.h"
#include "CRRMsg.h"

CRRMsgHandler4AckAccountReg::CRRMsgHandler4AckAccountReg() {

}

CRRMsgHandler4AckAccountReg::~CRRMsgHandler4AckAccountReg() {

}

void CRRMsgHandler4AckAccountReg::accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson ) {
	if ( _isAccountRegSuccess( pRMsgJson ) ) {
		::MessageBox( 0, _T("account register success!"), 0, MB_OK );
	} else {
		::MessageBox( 0, _T("account regisgter failed!"), 0, MB_OK );
	}

}

bool CRRMsgHandler4AckAccountReg::_isAccountRegSuccess( const CRRMsgJson* pRMsgJson ) {
    const Json::Value& valParams = pRMsgJson->m_jsonRoot[ "params" ];
	if ( !valParams.isObject() )
		return false;
	const Json::Value& valResult = valParams[ "result" ];
	if ( !valResult.isInt() )
		return false;
	return valResult.asInt() == 1;
}



