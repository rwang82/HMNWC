#include "stdafx.h"
#include "CRMisc.h"
#include "json\json.h"
#include "HMCharConv.h"
#include <atlconv.h>

void strContainer2JsonStr( const tstr_container_type& container, std::string& strJson ) {
    USES_CONVERSION;
	if ( container.size() == 0 ) {
	    strJson = "[]";
		return;
	}
	Json::FastWriter writer;
	Json::Value jsonRoot;

	for ( const tstring_type& tstrVal : container ) {
	    jsonRoot.append( T2A( tstrVal.c_str() ) );
	}
	strJson = writer.write( jsonRoot );
}


void strContainer2JsonStrWithQuotes( const tstr_container_type& container, std::string& strJson ) {
    USES_CONVERSION;
	int nCount = container.size();
	if ( nCount == 0 ) {
	    strJson = "[]";
		return;
	}
	strJson = "[\\\"";
	for ( int nIndex = 0; nIndex < nCount; ++nIndex ) {
	    strJson += T2A( container[ nIndex ].c_str() );
		if ( nIndex + 1 != nCount ) {
		    strJson += "\\\",\\\"";
		}
	}
	strJson += "\\\"]";
}


