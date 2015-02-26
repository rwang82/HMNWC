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
	typedef std::map< utf8_type, CRProduct* > uuid2product_map_type;
    typedef std::list< CRProduct* > product_list_type;
	typedef std::map< utf8_type, product_list_type* > name2pl_map_type;
	typedef std::map< utf8_type, int > name2flag_map_type; // save flag read account all product from db.
public:
	CRProductDepot();
	virtual ~CRProductDepot();

public:
	bool addProduct2Pend( const CRProduct* pProductNew, int& nErrCode );
	bool fillAccountProducts2Json( const CRFetchAccountProducts& fapParam, Json::Value& valProducts, int& nErrCode );
private:
	bool _hasProduct( const utf8_type& strUUID );
	bool _hasProductInCache( const utf8_type& strUUID ) const;
	bool _loadProductFromDB( const utf8_type& strUUID, int& nErrCode );
	bool _loadAccountProductsFromDB( const CRFetchAccountProducts& fapParam, int& nErrCode );
	void _saveProduct2Cache( CRProduct* pProductNew );
	void _saveProduct2UUIDMap( CRProduct* pProductNew );
	void _saveProduct2AccountMap( CRProduct* pProductNew );
	void _clearCache();
	bool _fillProduct2Item( const CRProduct* pProduct, Json::Value& valItem );
	bool _setReadAccountProductFromDBFlag( const utf8_type& strAccountName );
	void _clearRAPFDBFlag( const utf8_type& strAccountName );
	bool _hasRAPFDBFlag( const utf8_type& strAccountName ) const;
	void _eraseProductInList( const utf8_type& strUUID, product_list_type* pProductList );
private:
	uuid2product_map_type m_mapUUID2ProductCache;
	name2pl_map_type m_mapName2ProductListCache;
	name2flag_map_type m_mapName2Flag;
};

#endif //__CRPRODUCTDEPOT_H__