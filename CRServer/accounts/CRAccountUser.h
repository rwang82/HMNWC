#ifndef __CRACCOUNTUSER_H__
#define __CRACCOUNTUSER_H__
#include "CRAccountBase.h"

class CRAccountUser : public CRAccountBase{
public:
	CRAccountUser(const tstring_type& tstrAccountName, 
		const tstring_type& tstrPassword, 
		const tstring_type& tstrPhoneNum = _T(""), 
		const tstring_type& tstrEMail = _T(""));
	virtual ~CRAccountUser();
	
	// interface of CRAccountBase.
public:
	virtual int getSortType(); 
	

};


#endif //__CRACCOUNTUSER_H__