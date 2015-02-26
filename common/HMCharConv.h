#ifndef __HMCHARCONV_H__
#define __HMCHARCONV_H__
#include "tchar.h"
#include <string>


bool UTF8ToTCHAR( const unsigned char* szUtf8Buf, unsigned int uLenUtf8Buf, std::basic_string< TCHAR >& strDest );

bool UTF8ToTCHAR( const std::string strUtf8, std::basic_string< TCHAR >& strDest );

bool TCHARToUTF8( const std::basic_string< TCHAR >& strSource, std::basic_string< char >& strDest );

bool UTF8ToUTF16( const unsigned char* szUtf8Buf, unsigned int uLenUtf8Buf, std::basic_string< wchar_t >& wstrUtf16 );

bool UTF16ToANSI( const std::basic_string< wchar_t >& wstrUtf16, std::basic_string< char >& strAnsi );

bool UTF16ToUTF8( const std::basic_string< wchar_t >& wstrUtf16, std::basic_string<char>& strUtf8 );

bool ANSIToUTF16( const std::basic_string<char>& strAnsi, std::basic_string< wchar_t >& wstrUtf16 );


#endif //__HMCHARCONV_H__