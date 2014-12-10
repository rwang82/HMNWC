#ifndef __CRACCOUNTUSER_H__
#define __CRACCOUNTUSER_H__
#include "CRAccountBase.h"

class CRAccountUser : public CRAccountBase{
public:
	CRAccountUser(){};
	CRAccountUser(const CRAccountRegParam& paramAccountReg);
	virtual ~CRAccountUser();

	// interface of CRAccountBase.
public:
	virtual int getSortType(); 

	// interface of CRPersistenceObj.
public:
	virtual bool save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const;
	virtual bool loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode );

};


#endif //__CRACCOUNTUSER_H__