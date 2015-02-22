#ifndef __CRPRODUCT_H__
#define __CRPRODUCT_H__
#include "CRTypes.h"
#include "CRSaveable.h"

enum ENUMCRPRODUCTSTATUS {
    CRPRODUCT_STATUS_PENDING = 0,
	CRPRODUCT_STATUS_PUBLISHED = 1
};

class CRProduct : public CRSaveable{
public:
	CRProduct();
	CRProduct( const CRProduct& val );

public:
	virtual bool save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const;

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
};


#endif //__CRPRODUCT_H__