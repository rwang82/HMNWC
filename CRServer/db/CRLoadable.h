#ifndef __CRLOADABLE_H__
#define __CRLOADABLE_H__
//
class CRDBImplBase;
//
class CRLoadable {
public:
	CRLoadable(){}
	virtual ~CRLoadable(){}

public:
	virtual bool loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode ) = 0;

};


#endif //__CRLOADABLE_H__

