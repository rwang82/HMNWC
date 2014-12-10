#ifndef __CRACCOUNTADMIN_H__
#define __CRACCOUNTADMIN_H__
#include "CRAccountBase.h"

class CRAccountAdmin : public CRAccountBase{
public:
	CRAccountAdmin(){};
	CRAccountAdmin(const CRAccountRegParam& paramAccountReg);
	virtual ~CRAccountAdmin();
	
	// interface of CRAccountBase.
public:
	virtual int getSortType(); 
	
	// interface of CRPersistenceObj.
public:
	virtual bool save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const;
	virtual bool loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode );

};


#endif //__CRACCOUNTADMIN_H__