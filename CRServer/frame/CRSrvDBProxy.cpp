#include "stdafx.h"
#include "CRSrvDBProxy.h"
#include "CRDBImplMYSQL.h"
#include "CRSaveable.h"
#include "CRLoadable.h"
#include "CRErrCode.h"

CRSrvDBProxy::CRSrvDBProxy()
: m_pDBImpl( new CRDBImplMYSQL() ) {
}

CRSrvDBProxy::~CRSrvDBProxy() {
	if ( m_pDBImpl ) {
	    delete m_pDBImpl;
		m_pDBImpl = NULL;
	}
}

bool CRSrvDBProxy::save2DB( const CRSaveable* pSaveableObj, int& nErrCode ) {
	if ( !m_pDBImpl || !pSaveableObj ) {
	    nErrCode = CRERR_SRV_PARAM_INVALID;
		return false;
	}
    return pSaveableObj->save2DB( m_pDBImpl, nErrCode );
}

bool CRSrvDBProxy::loadFromDB( void* pParamKey, CRLoadable* pLoadableObj, int& nErrCode ) {
    if ( !m_pDBImpl || !pLoadableObj ) {
	    nErrCode = CRERR_SRV_PARAM_INVALID;
		return false;
	}
	return pLoadableObj->loadFromDB( pParamKey, m_pDBImpl, nErrCode );
}