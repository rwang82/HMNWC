#ifndef __CRMODULEACCOUNTREG_H__
#define __CRMODULEACCOUNTREG_H__
#include "CRModuleBase.h"
#include "hmcmn_event_depot.h"
#include "CRClientTypes.h"
//
struct AccountRegParam{
	AccountRegParam();
	AccountRegParam( const tstring_type& tstrUserName, const tstring_type& tstrPassword, int nSortType );
	AccountRegParam( const AccountRegParam& val );
	~AccountRegParam();
    tstring_type m_tstrUserName;
	tstring_type m_tstrPassword;
	int m_nSortType;
};
//
class CRModuleAccountReg : public CRModuleBase {
public:
	CRModuleAccountReg();
	virtual ~CRModuleAccountReg();

	// event handler. 
private:
	void _onEvtAccountRegBtnClick( void* pParam1, void* pParam2 );



private:
	hmcmn::hmcmn_event_depot::arg2event_handler_type* m_pfobj4OnAccountRegBtnClick;
};


#endif //__CRMODULEACCOUNTREG_H__