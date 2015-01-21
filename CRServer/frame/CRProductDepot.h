#ifndef __CRPRODUCTDEPOT_H__
#define __CRPRODUCTDEPOT_H__
#include "CRTypes.h"
#include "CRProduct.h"
#include <map>

class CRProduct;

class CRProductDepot {
public:
	typedef std::map< tstring_type, CRProduct* > uuid2product_map_type;
public:
	CRProductDepot();
	virtual ~CRProductDepot();

public:
	const CRProduct* getProduct( const tstring_type& tstrUUID ) const;
	bool addProduct2Pend( const CRProduct* pProductNew, int& nErrCode );

private:
	bool _hasProduct( const tstring_type& tstrUUID );
	bool _hasProductInCache( const tstring_type& tstrUUID ) const;
	bool _loadProductFromDB( const tstring_type& tstrUUID, int& nErrCode );

private:
	uuid2product_map_type m_mapUUID2ProductCache;
};

#endif //__CRPRODUCTDEPOT_H__