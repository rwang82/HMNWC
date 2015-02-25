#ifndef __CRPRODUCT_H__
#define __CRPRODUCT_H__
#include "CRTypes.h"
#include "CRSaveable.h"
#include "CRLoadable.h"

enum ENUMCRPRODUCTSTATUS {
    CRPRODUCT_STATUS_PENDING = 0,
	CRPRODUCT_STATUS_PUBLISHED = 1
};

class CRProduct : public CRSaveable, public CRLoadable{
public:
	CRProduct();
	CRProduct( const CRProduct& val );

	// interface of CRSaveable.
public:
	virtual bool save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const;
	
	// interface of CRLoadable.
public:
	virtual bool loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode );

public:
	tstring_type m_tstrPublisher; // the username of publisher
	tstring_type m_tstrUUID;
    tstring_type m_tstrTitle;
	tstring_type m_tstrPrice;
	tstring_type m_tstrDescribe;
	int m_nSortType; // default sort.
	tstring_type m_tstrUDSort; // user define sort.
	tstr_container_type m_containerImages;
	tstr_container_type m_containerKeywords;
	int m_nPassStatus;
};


#endif //__CRPRODUCT_H__