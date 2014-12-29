#ifndef __HMCHARCONV_H__
#define __HMCHARCONV_H__
#include <string>

bool UTF8ToUTF16( const unsigned char* szUtf8Buf, unsigned int uLenUtf8Buf, std::basic_string< wchar_t >& wstrUtf16 );


#endif //__HMCHARCONV_H__