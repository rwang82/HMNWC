#ifndef __CRACCOUNTLOGOFF_H__
#define __CRACCOUNTLOGOFF_H__
#include "CRAccountBase.h"

class CRAccountLogoff : public CRAccountBase {
public:
	CRAccountLogoff(const CRAccountData& paramAccountReg);
	virtual ~CRAccountLogoff();
	
	// interface of CRAccountBase.
public:
	virtual int getSortType(); 
	virtual bool doLogin( const CRLoginParam& loginParam, int& nErrCode );
	virtual bool doLogoff( const CRLogoffParam& logoffParam, int& nErrCode );

	// interface of CRPersistenceObj.
public:
	virtual bool save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const;
	virtual bool loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode );
};

#endif //__CRACCOUNTLOGOFF_H__