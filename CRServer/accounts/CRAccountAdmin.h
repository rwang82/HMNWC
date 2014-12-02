#ifndef __CRACCOUNTADMIN_H__
#define __CRACCOUNTADMIN_H__
#include "CRAccountBase.h"

class CRAccountAdmin : public CRAccountBase{
public:
	CRAccountAdmin(const tstring_type& tstrAccountName, 
		const tstring_type& tstrPassword, 
		const tstring_type& tstrPhoneNum = _T(""), 
		const tstring_type& tstrEMail = _T(""));
	virtual ~CRAccountAdmin();
	
	// interface of CRAccountBase.
public:
	virtual int getSortType(); 



};


#endif //__CRACCOUNTADMIN_H__