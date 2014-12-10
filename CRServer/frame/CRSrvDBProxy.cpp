#include "stdafx.h"
#include "CRSrvDBProxy.h"
#include "CRDBImplMYSQL.h"
#include "CRPersistenceObj.h"
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

bool CRSrvDBProxy::save2DB( const CRPersistenceObj* pPersistenceObj, int& nErrCode ) {
	if ( !m_pDBImpl || !pPersistenceObj ) {
	    nErrCode = CRERR_SRV_PARAM_INVALID;
		return false;
	}
    return pPersistenceObj->save2DB( m_pDBImpl, nErrCode );
}

bool CRSrvDBProxy::loadFromDB( void* pParamKey, CRPersistenceObj* pPersistenceObj, int& nErrCode ) {
    if ( !m_pDBImpl || !pPersistenceObj ) {
	    nErrCode = CRERR_SRV_PARAM_INVALID;
		return false;
	}
	return pPersistenceObj->loadFromDB( pParamKey, m_pDBImpl, nErrCode );
}