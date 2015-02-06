#include "stdafx.h"
#include "CRAccountCreator.h"
#include "CRTypes.h"
#include "CRAccountAdmin.h"
#include "CRAccountUser.h"
#include "CRServerRoot.h"
#include "CRSrvDBProxy.h"
#include "CRErrCode.h"
#include "FuncPack.h"
#include <atlconv.h>

CRAccountBase* CRAccountCreator::create( const CRAccountData& paramAccountReg, int& nErrCode ) {
	switch ( paramAccountReg.m_eSortType )
	{
	case EACCOUNT_SORT_USER:
	{
		return new CRAccountUser( paramAccountReg );
	}
		break;
	case EACCOUNT_SORT_ADMIN:
	{
	    return new CRAccountAdmin( paramAccountReg );
	}
		break;
	case EACCOUNT_SORT_UNKNOWN:
	default:
		assert( false );
		return NULL;
		break;
	}

	assert( false );
	return false;
}

CRAccountBase* CRAccountCreator::loadFromDB( const tstring_type& tstrAccountName, int& nErrCode ) {
	//
	CRAccountUser* pAccountUser = new CRAccountUser();
	CFuncPack fpkDelAccountUser( ::gfnDelObj< CRAccountUser >, pAccountUser );
	if ( g_CRSrvRoot.m_pSrvDBProxy->loadFromDB( (void*)&tstrAccountName, pAccountUser, nErrCode ) ) {
	    fpkDelAccountUser.Cancel();
		return pAccountUser;
	}
	//
	CRAccountAdmin* pAccountAdmin = new CRAccountAdmin();
	CFuncPack fpkDelAccountAdmin( ::gfnDelObj< CRAccountAdmin >, pAccountAdmin );
	if ( g_CRSrvRoot.m_pSrvDBProxy->loadFromDB( (void*)&tstrAccountName, pAccountAdmin, nErrCode ) ) {
	    fpkDelAccountAdmin.Cancel();
		return pAccountAdmin;
	}

	// load failed.
	return NULL;
}

















