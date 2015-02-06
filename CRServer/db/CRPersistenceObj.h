#ifndef __CRPERSISTENCEOBJ_H__
#define __CRPERSISTENCEOBJ_H__
//
class CRDBImplBase;
//
class CRSaveable {
public:
	CRSaveable(){};
	virtual ~CRSaveable(){};

public:
	virtual bool save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const = 0;
};

class CRLoadable {
public:
	CRLoadable(){}
	virtual ~CRLoadable(){}

public:
	virtual bool loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode ) = 0;

};

#endif //__CRPERSISTENCEOBJ_H__