#include "stdafx.h"
#include "CRMisc.h"
#include "json\json.h"
#include "HMCharConv.h"
#include <atlconv.h>

void strContainer2JsonStr( const utf8_container_type& container, std::string& strJson ) {
    USES_CONVERSION;
	if ( container.size() == 0 ) {
	    strJson = "[]";
		return;
	}
	Json::FastWriter writer;
	Json::Value jsonRoot;

	for ( const utf8_type& strVal : container ) {
	    jsonRoot.append( strVal.c_str() );
	}
	strJson = writer.write( jsonRoot );
}


void strContainer2JsonStrWithQuotes( const utf8_container_type& container, std::string& strJson ) {
    USES_CONVERSION;
	int nCount = container.size();
	if ( nCount == 0 ) {
	    strJson = "[]";
		return;
	}
	strJson = "[\\\"";
	for ( int nIndex = 0; nIndex < nCount; ++nIndex ) {
	    strJson += container[ nIndex ];
		if ( nIndex + 1 != nCount ) {
		    strJson += "\\\",\\\"";
		}
	}
	strJson += "\\\"]";
}


