#ifndef __CRACCOUNTADMIN_H__
#define __CRACCOUNTADMIN_H__
#include "CRAccountBase.h"

class CRAccountAdmin : public CRAccountBase{
public:
	CRAccountAdmin(const CRAccountRegParam& paramAccountReg);
	virtual ~CRAccountAdmin();
	
	// interface of CRAccountBase.
public:
	virtual int getSortType(); 


};


#endif //__CRACCOUNTADMIN_H__