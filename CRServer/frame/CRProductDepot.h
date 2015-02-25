#ifndef __CRPRODUCTDEPOT_H__
#define __CRPRODUCTDEPOT_H__
#include "CRTypes.h"
#include "CRProduct.h"
#include "CRAccountProducts.h"
#include <map>
#include <list>

namespace Json {
	class Value;
}
class CRProduct;

class CRProductDepot {
	// CRProduct* maybe need use boost::share_ptr< CRProduct* > do this job.
public:
	typedef std::map< tstring_type, CRProduct* > uuid2product_map_type;
    typedef std::list< CRProduct* > product_list_type;
	typedef std::map< tstring_type, product_list_type* > name2pl_map_type;
	typedef std::map< tstring_type, int > name2flag_map_type; // save flag read account all product from db.
public:
	CRProductDepot();
	virtual ~CRProductDepot();

public:
	bool addProduct2Pend( const CRProduct* pProductNew, int& nErrCode );
	bool fillAccountProducts2Json( const CRFetchAccountProducts& fapParam, Json::Value& valProducts, int& nErrCode );
private:
	bool _hasProduct( const tstring_type& tstrUUID );
	bool _hasProductInCache( const tstring_type& tstrUUID ) const;
	bool _loadProductFromDB( const tstring_type& tstrUUID, int& nErrCode );
	bool _loadAccountProductsFromDB( const CRFetchAccountProducts& fapParam, int& nErrCode );
	void _saveProduct2Cache( CRProduct* pProductNew );
	void _saveProduct2UUIDMap( CRProduct* pProductNew );
	void _saveProduct2AccountMap( CRProduct* pProductNew );
	void _clearCache();
	bool _fillProduct2Item( const CRProduct* pProduct, Json::Value& valItem );
	bool _setReadAccountProductFromDBFlag( const tstring_type& tstrAccountName );
	void _clearRAPFDBFlag( const tstring_type& tstrAccountName );
	bool _hasRAPFDBFlag( const tstring_type& tstrAccountName ) const;
	void _eraseProductInList( const tstring_type& tstrUUID, product_list_type* pProductList );
private:
	uuid2product_map_type m_mapUUID2ProductCache;
	name2pl_map_type m_mapName2ProductListCache;
	name2flag_map_type m_mapName2Flag;
};

#endif //__CRPRODUCTDEPOT_H__