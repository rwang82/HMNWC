#ifndef __CRPRODUCT_H__
#define __CRPRODUCT_H__
#include "CRTypes.h"
#include "CRPersistenceObj.h"

enum ENUMCRPRODUCTSTATUS {
    CRPRODUCT_STATUS_PENDING = 0,
	CRPRODUCT_STATUS_PUBLISHED = 1
};

class CRProduct : public CRPersistenceObj{
public:
	CRProduct();
	CRProduct( const CRProduct& val );

public:
	virtual bool save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const;
	virtual bool loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode );

public:
	tstring_type m_tstrUUID;
    tstring_type m_tstrTitle;
	tstring_type m_tstrPrice;
	tstring_type m_tstrDescribe;
	tstr_container_type m_containerImages;
	tstr_container_type m_containerKeywords;
};


#endif //__CRPRODUCT_H__