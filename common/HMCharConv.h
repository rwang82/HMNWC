#ifndef __HMCHARCONV_H__
#define __HMCHARCONV_H__
#include "tchar.h"
#include <string>


bool UTF8ToTCHAR( const unsigned char* szUtf8Buf, unsigned int uLenUtf8Buf, std::basic_string< TCHAR >& tstrDest );

bool UTF8ToUTF16( const unsigned char* szUtf8Buf, unsigned int uLenUtf8Buf, std::basic_string< wchar_t >& wstrUtf16 );

bool UTF16ToANSI( const std::basic_string< wchar_t >& wstrUtf16, std::basic_string< char > strAnsi );



#endif //__HMCHARCONV_H__