#include "HMCharConv.h"
#include "Windows.h"
#include <assert.h>


bool UTF8ToTCHAR( const unsigned char* szUtf8Buf, unsigned int uLenUtf8Buf, std::basic_string< TCHAR >& tstrDest ) {
    std::basic_string< wchar_t > wstrUtf16;

	if ( !UTF8ToUTF16( szUtf8Buf, uLenUtf8Buf, wstrUtf16 ) )
		return false;

#ifdef _UNICODE
	tstrDest = wstrUtf16;
#else 
	std::string strAnsi;
	if ( !UTF16ToANSI( wstrUtf16, strAnsi ) ) {
	    return false;
	}
	tstrDest = strAnsi;
#endif //_UNICODE
	
	return true;
}

bool UTF8ToUTF16( const unsigned char* szUtf8Buf, unsigned int uLenUtf8Buf, std::basic_string< wchar_t >& wstrUtf16 ) {
	if ( !szUtf8Buf || uLenUtf8Buf == 0 )
		return false;
	int nLenWChar;
	int nCopied;
	WCHAR* pBufWChar = NULL;

	nLenWChar = ::MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)szUtf8Buf, uLenUtf8Buf, NULL, 0 );
	if ( nLenWChar <= 0 )
	    return false;
	pBufWChar = new WCHAR[ nLenWChar + 1];
	nCopied = MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)szUtf8Buf, uLenUtf8Buf, pBufWChar, nLenWChar );
	if ( nCopied <= 0 )
		return false;
	pBufWChar[ nLenWChar ] = L'\0';

	//
	wstrUtf16 = pBufWChar;
	return true;
}


bool UTF16ToANSI( const std::basic_string< wchar_t >& wstrUtf16, std::basic_string< char > strAnsi ) {
	int nSizeNeed;
	char* pBufAnsi = NULL;

	nSizeNeed = ::WideCharToMultiByte( CP_ACP, 0, wstrUtf16.c_str(), -1, NULL, 0, NULL, NULL );
	if ( nSizeNeed <= 0 ) {
		assert( false );
	    return false;
	}
	pBufAnsi = new char[ nSizeNeed + 1 ];
	memset( pBufAnsi, 0, (nSizeNeed + 1)*sizeof(char) );
	if ( 0 >= ::WideCharToMultiByte( CP_ACP, 0, wstrUtf16.c_str(), -1, pBufAnsi, nSizeNeed, NULL, NULL ) ) {
	    delete []pBufAnsi;
		return false;
	}
	strAnsi = pBufAnsi;
	delete []pBufAnsi;
	return true;
}
