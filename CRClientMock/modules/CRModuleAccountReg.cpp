#include "stdafx.h"
#include "CRModuleAccountReg.h"
#include "CRClientMock.h"
#include "CRClientEvtDefs.h"
#include "CRTaskAccountReg.h"
#include "CRTypes.h"
#include "json/json.h"
#include <functional>
//
using namespace std::placeholders;
//
AccountRegParam::AccountRegParam()
: m_tstrUserName( _T("") )
, m_tstrPassword( _T("") )
, m_eSortType( EACCOUNT_SORT_UNKNOWN )
{}

AccountRegParam::AccountRegParam( const tstring_type& tstrUserName, const tstring_type& tstrPassword, ENUMACCOUNTSORT eSortType )
: m_tstrUserName( tstrUserName )
, m_tstrPassword( tstrPassword )
, m_eSortType( eSortType ) {

}

AccountRegParam::AccountRegParam( const AccountRegParam& val )
: m_tstrUserName( val.m_tstrUserName )
, m_tstrPassword( val.m_tstrPassword )
, m_eSortType( val.m_eSortType ) {

}

AccountRegParam::~AccountRegParam() {

}
//
CRModuleAccountReg::CRModuleAccountReg()
: m_pfobj4OnAccountRegBtnClick( new hmcmn::hmcmn_event_depot::arg2event_handler_type( std::bind( &CRModuleAccountReg::_onEvtAccountRegBtnClick, this, _1, _2 ) ) ) {
	theApp.m_eventDepot.bind( ECRCE_ID_ACCOUNT_REG_BTNCLICK, m_pfobj4OnAccountRegBtnClick );
}

CRModuleAccountReg::~CRModuleAccountReg() {
	if ( m_pfobj4OnAccountRegBtnClick ) {
	    theApp.m_eventDepot.unbind( ECRCE_ID_ACCOUNT_REG_BTNCLICK, m_pfobj4OnAccountRegBtnClick );
	    delete m_pfobj4OnAccountRegBtnClick;
		m_pfobj4OnAccountRegBtnClick = NULL;
	}
}

void CRModuleAccountReg::_onEvtAccountRegBtnClick( void* pParam1, void* pParam2 ) {
    AccountRegParam* pAccountRegParam = NULL;
	HMTaskEngine::task_id_type taskId;

	pAccountRegParam = (AccountRegParam*)pParam1;
	
	theApp.m_taskEngineMain.pushbackTask( new CRTaskAccountReg( *pAccountRegParam ), taskId );
    
}










