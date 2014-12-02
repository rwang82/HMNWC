#ifndef __CRACCOUNTBASE_H__
#define __CRACCOUNTBASE_H__
#include "tchar.h"
#include <string>

class CRAccountBase {
public:
	typedef std::basic_string< TCHAR > tstring_type;
public:
	CRAccountBase( const tstring_type& tstrAccountName, 
		const tstring_type& tstrPassword, 
		const tstring_type& tstrPhoneNum = _T(""), 
		const tstring_type& tstrEMail = _T("") );
	virtual ~CRAccountBase(){};

public:
	virtual int getSortType() = 0; 

public:
	tstring_type m_tstrAccountName;
	tstring_type m_tstrPassword;
	tstring_type m_tstrPhoneNum;
	tstring_type m_tstrEMail;
};


#endif //__CRACCOUNTBASE_H__