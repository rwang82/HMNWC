#ifndef __CRSRVDBPROXY_H__
#define __CRSRVDBPROXY_H__
#include "CRTypes.h"
//
class CRDBImplBase;
class CRSaveable;
class CRLoadable;
//
class CRSrvDBProxy {
public:
	CRSrvDBProxy();
	~CRSrvDBProxy();

public:
	bool save2DB( const CRSaveable* pSaveableObj, int& nErrCode );
	bool loadFromDB( void* pParamKey, CRLoadable* pLoadableObj, int& nErrCode );

private:
	CRDBImplBase* m_pDBImpl;
};


#endif //__CRSRVDBPROXY_H__