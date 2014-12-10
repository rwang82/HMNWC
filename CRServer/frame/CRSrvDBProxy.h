#ifndef __CRSRVDBPROXY_H__
#define __CRSRVDBPROXY_H__
#include "CRTypes.h"
//
class CRDBImplBase;
class CRPersistenceObj;
//
class CRSrvDBProxy {
public:
	CRSrvDBProxy();
	~CRSrvDBProxy();

public:
	bool save2DB( const CRPersistenceObj* pPersistenceObj, int& nErrCode );
	bool loadFromDB( void* pParamKey, CRPersistenceObj* pPersistenceObj, int& nErrCode );

private:
	CRDBImplBase* m_pDBImpl;
};


#endif //__CRSRVDBPROXY_H__