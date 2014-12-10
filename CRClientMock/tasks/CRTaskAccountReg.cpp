#include "stdafx.h"
#include "CRTaskAccountReg.h"
#include "CRModuleAccountReg.h"
#include "CRRMsgMaker.h"
#include "CRRCmdDefs.h"
#include "CRCCommProxyBase.h"
#include "CRCCommDefs.h"
#include "CRClientMock.h"
#include <atlconv.h>
	
CRTaskAccountReg::CRTaskAccountReg( const AccountRegParam& paramAccountReg )
: m_pParamAccountReg( new AccountRegParam( paramAccountReg ) ) {
}

CRTaskAccountReg::~CRTaskAccountReg() {
	if ( m_pParamAccountReg ) {
	    delete m_pParamAccountReg;
		m_pParamAccountReg = NULL;
	}
}

bool CRTaskAccountReg::_fillParams( Json::Value& valParams ) {
	USES_CONVERSION;

	// fill valParams.
	valParams[ "username" ] = T2A( m_pParamAccountReg->m_tstrUserName.c_str() );
	valParams[ "password" ] = T2A( m_pParamAccountReg->m_tstrPassword.c_str() );
	valParams[ "sort" ] = (int)m_pParamAccountReg->m_eSortType;
	valParams[ "phone" ] = "";
	valParams[ "email" ] = "";

	return true;
}

int CRTaskAccountReg::_getCmdType() const {
	return CRCMDTYPE_REQ_ACCOUNT_REG;
}