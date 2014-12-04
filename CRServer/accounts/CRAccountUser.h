#ifndef __CRACCOUNTUSER_H__
#define __CRACCOUNTUSER_H__
#include "CRAccountBase.h"

class CRAccountUser : public CRAccountBase{
public:
	CRAccountUser(const CRAccountRegParam& paramAccountReg);
	virtual ~CRAccountUser();
	
	// interface of CRAccountBase.
public:
	virtual int getSortType(); 

};


#endif //__CRACCOUNTUSER_H__