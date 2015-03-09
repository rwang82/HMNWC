#include "stdafx.h"
#include "CRProductDepot.h"
#include "CRProduct.h"
#include "CRAccountProducts.h"
#include "CRServerRoot.h"
#include "CRSrvDBProxy.h"
#include "CRErrCode.h"
#include "FuncPack.h"
#include "HMCharConv.h"
#include "Json/json.h"

CRProductDepot::CRProductDepot() {

}

CRProductDepot::~CRProductDepot() {
	_clearCache();
}

bool CRProductDepot::addProduct2Pend( const CRProduct* pProductNew, int& nErrCode ) {
	if ( !pProductNew )
        return false;
	if ( _hasProduct( pProductNew->m_strUUID ) ) {
		assert( false );
		return false;
	}

	if ( !g_CRSrvRoot.m_pSrvDBProxy->save2DB( pProductNew, nErrCode ) )
		return false;

	//
	_saveProduct2Cache( new CRProduct( *pProductNew ) );

	return true;
}

bool CRProductDepot::fillAccountProducts2Json( const CRFetchAccountProducts& fapParam, Json::Value& valProducts, int& nErrCode ) {
	product_list_type* pProductList = NULL;
	product_list_type::iterator itProduct, iendProduct;
    name2pl_map_type::iterator itName2PL;
	nErrCode = CRERR_SRV_NONE;
	
	// clear cache.
	itName2PL = m_mapName2ProductListCache.find( fapParam.m_strAccountName );
	if ( itName2PL != m_mapName2ProductListCache.end() ) {
	    delete itName2PL->second;
		itName2PL->second = NULL;
		m_mapName2ProductListCache.clear();
		_clearRAPFDBFlag( fapParam.m_strAccountName );
	}
	//
	if ( !_loadAccountProductsFromDB( fapParam, nErrCode ) )
	    return false;
	//
	itName2PL = m_mapName2ProductListCache.find( fapParam.m_strAccountName );
	if ( itName2PL == m_mapName2ProductListCache.end() ) {
		valProducts.resize(0);
	    return true; // means no product published.
	}

	// save cache version, not finish.
	//itName2PL = m_mapName2ProductListCache.find( fapParam.m_strAccountName );
	//if ( itName2PL == m_mapName2ProductListCache.end() ) {
	//	if ( !_loadAccountProductsFromDB( fapParam, nErrCode ) )
	//		return false;
	//	itName2PL = m_mapName2ProductListCache.find( fapParam.m_strAccountName );
	//	if ( itName2PL == m_mapName2ProductListCache.end() )
	//		return false;
	//}

	pProductList = itName2PL->second;
	assert( pProductList );
	iendProduct = pProductList->end();
	for ( itProduct = pProductList->begin(); itProduct!=iendProduct; ++itProduct ) {
	    Json::Value valPItem;
        if ( !_fillProduct2Item( *itProduct, valPItem ) )
			continue;
		valProducts.append( valPItem );
	}

	return true;
}

bool CRProductDepot::_fillProduct2Item( const CRProduct* pProduct, Json::Value& valItem ) {
	if ( !pProduct )
		return false;
	std::string strUTF8;
	utf8_container_type::const_iterator citStr, ciendStr;
	//
	valItem[ "uuid" ] = pProduct->m_strUUID;
	valItem[ "publisher" ] = pProduct->m_strPublisher;
	valItem[ "title" ] = pProduct->m_strTitle;
	valItem[ "price" ] = pProduct->m_strPrice;
	valItem[ "describe" ] = pProduct->m_strDescribe;
	valItem[ "sort" ] = pProduct->m_nSortType;
	valItem[ "udsort" ] = pProduct->m_strUDSort;
	Json::Value& valImages = valItem["images"];
	if ( pProduct->m_containerImages.size() == 0 ) {
	    valImages = Json::Value(Json::arrayValue);
	} else {
		ciendStr = pProduct->m_containerImages.end();
		for ( citStr = pProduct->m_containerImages.begin(); citStr!=ciendStr; ++citStr ) {
			valImages.append( *citStr );
		}
	}
	//
	Json::Value& valKeywords = valItem["keywords"];
	if ( pProduct->m_containerKeywords.size() == 0 ) {
	    valKeywords = Json::Value( Json::arrayValue );
	} else {
        ciendStr = pProduct->m_containerKeywords.end();
        for ( citStr = pProduct->m_containerKeywords.begin(); citStr!=ciendStr; ++citStr ) {
            valKeywords.append( *citStr );
        }    
	}

	return true;
}

bool CRProductDepot::_setReadAccountProductFromDBFlag( const utf8_type& strAccountName ) {
	if ( strAccountName.length() == 0 )
		return false;
    m_mapName2Flag[ strAccountName ] = 1;
	return true;
}

void CRProductDepot::_clearRAPFDBFlag( const utf8_type& strAccountName ) {
    m_mapName2Flag.erase( strAccountName );
}

bool CRProductDepot::_hasRAPFDBFlag( const utf8_type& strAccountName ) const {
	return m_mapName2Flag.find( strAccountName ) != m_mapName2Flag.end();
}

void CRProductDepot::_saveProduct2UUIDMap( CRProduct* pProductNew ) {
	if ( !pProductNew )
		return;
    uuid2product_map_type::iterator itId2P;

	itId2P = m_mapUUID2ProductCache.find( pProductNew->m_strUUID );
	if ( itId2P != m_mapUUID2ProductCache.end() ) {
		delete itId2P->second;
		itId2P->second = pProductNew;
	} else {
        m_mapUUID2ProductCache[ pProductNew->m_strUUID ] = pProductNew;
	}
}

void CRProductDepot::_eraseProductInList( const utf8_type& strUUID, product_list_type* pProductList ) {
    product_list_type::iterator itP, iendP;
	
	iendP = pProductList->end();
	for ( itP = pProductList->begin(); itP!=iendP; ++itP ) {
		CRProduct* pProduct = (*itP);
	    if ( pProduct->m_strUUID == strUUID ) {
		    // delete pProduct; // because m_mapUUID2ProductCache hold CRProduct.
			pProductList->erase( itP );
            return;
		}
	}

}

void CRProductDepot::_saveProduct2AccountMap( CRProduct* pProductNew ) {
	name2flag_map_type::iterator itName2Flag;
	name2pl_map_type::iterator itName2PL;
	product_list_type* pListProduct = NULL;

	if ( !_hasRAPFDBFlag( pProductNew->m_strPublisher ) ) 
		return;
	//
	itName2PL = m_mapName2ProductListCache.find( pProductNew->m_strPublisher );
	if ( itName2PL != m_mapName2ProductListCache.end() ) {
	    pListProduct = itName2PL->second;
	} else {
	    pListProduct = new std::list< CRProduct* >();
		m_mapName2ProductListCache[ pProductNew->m_strPublisher ] = pListProduct;
	}
	assert( pListProduct != NULL );
	//
	_eraseProductInList( pProductNew->m_strUUID, pListProduct );
	//
	pListProduct->push_front( pProductNew );
}

void CRProductDepot::_saveProduct2Cache( CRProduct* pProductNew ) {
	if ( !pProductNew )
		return;
	//
	_saveProduct2UUIDMap( pProductNew );
	//
	_saveProduct2AccountMap( pProductNew );

}

void CRProductDepot::_clearCache() {
	//
    name2pl_map_type::iterator itName2PL, iendName2PL;
	iendName2PL = m_mapName2ProductListCache.end();
	for ( itName2PL = m_mapName2ProductListCache.begin(); itName2PL!=iendName2PL; ++itName2PL ) {
	    itName2PL->second->clear();
		delete itName2PL->second;
		itName2PL->second = NULL;
	}
	m_mapName2ProductListCache.clear();
	//
	uuid2product_map_type::iterator itId2P, iendId2P;
	iendId2P = m_mapUUID2ProductCache.end();
	for ( itId2P = m_mapUUID2ProductCache.begin(); itId2P!=iendId2P; ++itId2P ) {
	    delete itId2P->second;
        itId2P->second = NULL;
	}
	m_mapUUID2ProductCache.clear();
}

bool CRProductDepot::_hasProduct( const utf8_type& strUUID ) {
	int nErrCode = CRERR_SRV_NONE;
	return _hasProductInCache( strUUID ) || _loadProductFromDB( strUUID, nErrCode );
}

bool CRProductDepot::_hasProductInCache( const utf8_type& strUUID ) const {
	uuid2product_map_type::const_iterator itId2Product;

	itId2Product = m_mapUUID2ProductCache.find( strUUID );
	return ( itId2Product != m_mapUUID2ProductCache.end() );
}

bool CRProductDepot::_loadAccountProductsFromDB( const CRFetchAccountProducts& fapParam, int& nErrCode ) {
	CRAccountProducts accountProducts;
	nErrCode = CRERR_SRV_NONE;
	CRAccountProducts::product_list_type::iterator itProduct, iendProduct;

	if ( !g_CRSrvRoot.m_pSrvDBProxy->loadFromDB( (void*)&fapParam, &accountProducts, nErrCode ) )
		return false;
    //
	_setReadAccountProductFromDBFlag( fapParam.m_strAccountName );
	//
	iendProduct = accountProducts.m_listProduct.end();
	for ( itProduct = accountProducts.m_listProduct.begin(); itProduct!=iendProduct; ++itProduct ) {
	    _saveProduct2Cache( *itProduct );
	}

	return true;
}

bool CRProductDepot::_loadProductFromDB( const utf8_type& strUUID, int& nErrCode ) {
	CRProduct* pNewProduct = new CRProduct();
	CFuncPack fpkDeProduct( ::gfnDelObj< CRProduct >, pNewProduct );

	if ( !g_CRSrvRoot.m_pSrvDBProxy->loadFromDB( (void*)&strUUID, pNewProduct, nErrCode ) )
		return false;

	fpkDeProduct.Cancel();
	_saveProduct2Cache( pNewProduct );
	return true;
}
