#ifndef __CRACCOUNTLOGOFF_H__
#define __CRACCOUNTLOGOFF_H__
#include "CRAccountBase.h"

class CRAccountLogoff : public CRAccountBase {
public:
	CRAccountLogoff(const CRAccountRegParam& paramAccountReg);
	virtual ~CRAccountLogoff();
	
	// interface of CRAccountBase.
public:
	virtual int getSortType(); 
	virtual bool doLogin( const CRLoginParam& loginParam, int& nErrCode );
	virtual void doLogoff( const CRLogoffParam& logoffParam, int& nErrCode );
};

#endif //__CRACCOUNTLOGOFF_H__