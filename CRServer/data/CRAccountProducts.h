#ifndef __CRACCOUNTPRODUCTS_H__
#define __CRACCOUNTPRODUCTS_H__
#include "CRLoadable.h"
#include "CRTypes.h"
#include <list>
//
class CRProduct;
//
struct CRFetchAccountProducts {
	CRFetchAccountProducts( const tstring_type& tstrAccountName, unsigned int uIndexStart, unsigned int uCount ) {
	    m_tstrAccountName = tstrAccountName;
		m_uIndexStart = uIndexStart;
		m_uCount = uCount;
	}
	~CRFetchAccountProducts(){}
    tstring_type m_tstrAccountName;
	unsigned int m_uIndexStart;
	unsigned int m_uCount;
};
//
class CRAccountProducts : public CRLoadable {
public:
	typedef std::list< CRProduct* > product_list_type;
public:
	CRAccountProducts();
	virtual ~CRAccountProducts();
	
public:
	virtual bool loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode );

public:
	product_list_type m_listProduct;
};


#endif //__CRACCOUNTPRODUCTS_H__