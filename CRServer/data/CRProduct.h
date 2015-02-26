#ifndef __CRPRODUCT_H__
#define __CRPRODUCT_H__
#include "CRTypes.h"
#include "CRSaveable.h"
#include "CRLoadable.h"
#include <string>

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
	utf8_type m_strPublisher; // the username of publisher
	utf8_type m_strUUID;
    utf8_type m_strTitle;
	utf8_type m_strPrice;
	utf8_type m_strDescribe;
	int m_nSortType; // default sort.
	utf8_type m_strUDSort; // user define sort.
	utf8_container_type m_containerImages;
	utf8_container_type m_containerKeywords;
	int m_nPassStatus;
};


#endif //__CRPRODUCT_H__