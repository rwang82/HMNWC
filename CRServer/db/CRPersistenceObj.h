#ifndef __CRPERSISTENCEOBJ_H__
#define __CRPERSISTENCEOBJ_H__
//
class CRDBImplBase;
//
class CRPersistenceObj {
public:
	CRPersistenceObj(){};
	virtual ~CRPersistenceObj(){};

public:
	virtual bool save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const = 0;
	virtual bool loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode ) = 0;
};

#endif //__CRPERSISTENCEOBJ_H__