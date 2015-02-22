#include "stdafx.h"
#include "CRProductDepot.h"
#include "CRProduct.h"
#include "CRServerRoot.h"
#include "CRSrvDBProxy.h"
#include "CRErrCode.h"
#include "FuncPack.h"

CRProductDepot::CRProductDepot() {

}

CRProductDepot::~CRProductDepot() {

}

const CRProduct* CRProductDepot::getProduct( const tstring_type& tstrUUID ) const {
	uuid2product_map_type::const_iterator citUUID2Product;

	citUUID2Product = m_mapUUID2ProductCache.find( tstrUUID );
	if ( citUUID2Product == m_mapUUID2ProductCache.end() )
		return NULL;
	
	return citUUID2Product->second;
}

bool CRProductDepot::addProduct2Pend( const CRProduct* pProductNew, int& nErrCode ) {
	if ( !pProductNew )
        return false;
	if ( _hasProduct( pProductNew->m_tstrUUID ) ) {
		assert( false );
		return false;
	}

	if ( !g_CRSrvRoot.m_pSrvDBProxy->save2DB( pProductNew, nErrCode ) )
		return false;

	//
	m_mapUUID2ProductCache[ pProductNew->m_tstrUUID ] = new CRProduct( *pProductNew );
	return true;
}

bool CRProductDepot::_hasProduct( const tstring_type& tstrUUID ) {
	int nErrCode = CRERR_SRV_NONE;
	return _hasProductInCache( tstrUUID ) || _loadProductFromDB( tstrUUID, nErrCode );
}

bool CRProductDepot::_hasProductInCache( const tstring_type& tstrUUID ) const {
	uuid2product_map_type::const_iterator itId2Product;

	itId2Product = m_mapUUID2ProductCache.find( tstrUUID );
	return ( itId2Product != m_mapUUID2ProductCache.end() );
}

bool CRProductDepot::_loadProductFromDB( const tstring_type& tstrUUID, int& nErrCode ) {

	// need more code here. 

	return false;
	//CRProduct* pNewProduct = new CRProduct();
	//CFuncPack fpkDeProduct( ::gfnDelObj< CRProduct >, pNewProduct );

	//if ( !g_CRSrvRoot.m_pSrvDBProxy->loadFromDB( (void*)&tstrUUID, pNewProduct, nErrCode ) )
	//	return false;

	//fpkDeProduct.Cancel();
	//m_mapUUID2ProductCache[ tstrUUID ] = pNewProduct;
	//return true;
}
