#ifndef __CRMISC_H__
#define __CRMISC_H__
#include "CRTypes.h"

void strContainer2JsonStr( const tstr_container_type& container, std::string& strJson );
void strContainer2JsonStrWithQuotes( const tstr_container_type& container, std::string& strJson );


#endif //__CRMISC_H__