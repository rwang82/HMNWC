#include "HMCharConv.h"
#include "Windows.h"

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
