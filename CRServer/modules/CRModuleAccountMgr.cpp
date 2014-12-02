#include "stdafx.h"
#include "CRModuleAccountMgr.h"
#include "CRServerRoot.h"
#include "hmcmn_event_depot.h"
#include "CRRMsgHandler4Login.h"

CRModuleAccountMgr::CRModuleAccountMgr() {
	//g_CRSrvRoot.m_pEventDepot->bind(  );
}

CRModuleAccountMgr::~CRModuleAccountMgr() {

}

bool CRModuleAccountMgr::doLogin( const CRLoginParam& loginParam, int& nErrCode ) {
	
	return true;
	//loginParam.

	return true;
}

bool CRModuleAccountMgr::doLogoff( const CRLogoffParam& logoffParam, int& nErrCode ) {

	return true;
}













