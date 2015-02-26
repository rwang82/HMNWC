#ifndef __CRMISC_H__
#define __CRMISC_H__
#include "CRTypes.h"

void strContainer2JsonStr( const utf8_container_type& container, std::string& strJson );
void strContainer2JsonStrWithQuotes( const utf8_container_type& container, std::string& strJson );


#endif //__CRMISC_H__