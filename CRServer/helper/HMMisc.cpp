#include "stdafx.h"
#include "HMMisc.h"
#include "FuncPack.h"

bool getProcessFilePath( std::basic_string< TCHAR >& tstrProcessFilePath ) {
	DWORD dwLenCopied;
	TCHAR szProcessFilePath[ MAX_PATH + 2];
	
	dwLenCopied = ::GetModuleFileName( NULL, szProcessFilePath, MAX_PATH + 2 );
	
	tstrProcessFilePath = szProcessFilePath;
	return dwLenCopied <= MAX_PATH;
}

bool getProcessDirPath( std::basic_string< TCHAR >& tstrProcessDirPath ) {
	std::basic_string< TCHAR > tstrProcessFilePath;
	std::basic_string< TCHAR >::size_type posBackSlash;

	if (!getProcessFilePath( tstrProcessFilePath ))
		return false;
	posBackSlash = tstrProcessFilePath.rfind( _T( '\\' ) );
	if (posBackSlash == std::basic_string< TCHAR >::npos)
		return false;
	//
	tstrProcessDirPath = tstrProcessFilePath.substr( 0, posBackSlash );
	return true;
}
