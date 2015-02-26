#include "HMCharConv.h"
#include "Windows.h"
#include <assert.h>


bool UTF8ToTCHAR( const std::string strUtf8, std::basic_string< TCHAR >& strDest ) {
    return UTF8ToTCHAR( (const unsigned char*)strUtf8.c_str(), strUtf8.length() + 1, strDest );
}

bool UTF8ToTCHAR( const unsigned char* szUtf8Buf, unsigned int uLenUtf8Buf, std::basic_string< TCHAR >& strDest ) {
    std::basic_string< wchar_t > wstrUtf16;

	if ( !UTF8ToUTF16( szUtf8Buf, uLenUtf8Buf, wstrUtf16 ) )
		return false;

#ifdef _UNICODE
	strDest = wstrUtf16;
#else 
	std::string strAnsi;
	if ( !UTF16ToANSI( wstrUtf16, strAnsi ) ) {
	    return false;
	}
	strDest = strAnsi;
#endif //_UNICODE
	
	return true;
}

bool TCHARToUTF8( const std::basic_string< TCHAR >& strSource, std::basic_string< char >& strUtf8 ) {
	std::basic_string< wchar_t > wstrUtf16;
#ifdef _UNICODE
	wstrUtf16 = strSource;
#else
	if ( !ANSIToUTF16( strSource, wstrUtf16 ) )
		return false;
#endif //__UNICODE
	
	return UTF16ToUTF8( wstrUtf16, strUtf8 );
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
	if ( nCopied <= 0 ) {
	    delete []pBufWChar;
		return false;
	}
	pBufWChar[ nLenWChar ] = L'\0';

	//
	wstrUtf16 = pBufWChar;
	delete []pBufWChar;
	return true;
}

bool UTF16ToANSI( const std::basic_string< wchar_t >& wstrUtf16, std::basic_string< char >& strAnsi ) {
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

bool UTF16ToUTF8( const std::basic_string< wchar_t >& wstrUtf16, std::basic_string<char>& strUtf8 ) {
	int nSizeNeed;
	char* pBufUtf8 = NULL;

	nSizeNeed = ::WideCharToMultiByte( CP_UTF8, 0, wstrUtf16.c_str(), -1, NULL, 0, NULL, NULL );
	if ( nSizeNeed <= 0 ) {
		assert( false );
	    return false;
	}
	pBufUtf8 = new char[ nSizeNeed + 1 ];
	memset( pBufUtf8, 0, (nSizeNeed + 1)*sizeof(char) );
	if ( 0 >= ::WideCharToMultiByte( CP_UTF8, 0, wstrUtf16.c_str(), -1, pBufUtf8, nSizeNeed, NULL, NULL ) ) {
	    delete []pBufUtf8;
		return false;
	}
	strUtf8 = pBufUtf8;
	delete []pBufUtf8;
	return true;
}

bool ANSIToUTF16( const std::basic_string<char>& strAnsi, std::basic_string< wchar_t >& wstrUtf16 ) {
	int nLenWChar;
	int nCopied;
	WCHAR* pBufWChar = NULL;

	nLenWChar = ::MultiByteToWideChar( CP_ACP, 0, (LPCSTR)strAnsi.c_str(), strAnsi.length() + 1, NULL, 0 );
	if ( nLenWChar <= 0 )
	    return false;
	pBufWChar = new WCHAR[ nLenWChar + 1];
	nCopied = MultiByteToWideChar( CP_ACP, 0, (LPCSTR)strAnsi.c_str(), strAnsi.length() + 1, pBufWChar, nLenWChar );
	if ( nCopied <= 0 ) {
		delete []pBufWChar;
	    return false;
	}
	pBufWChar[ nLenWChar ] = L'\0';

	//
	wstrUtf16 = pBufWChar;
	delete []pBufWChar;
	return true;
}