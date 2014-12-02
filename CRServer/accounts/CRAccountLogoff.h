#ifndef __CRACCOUNTLOGOFF_H__
#define __CRACCOUNTLOGOFF_H__
#include "CRAccountBase.h"

class CRAccountLogoff : public CRAccountBase {
public:
	CRAccountLogoff();
	virtual ~CRAccountLogoff();
	
	// interface of CRAccountBase.
public:
	virtual int getSortType(); 

};

#endif //__CRACCOUNTLOGOFF_H__