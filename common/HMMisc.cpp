#include "stdafx.h"
#include "HMMisc.h"
#include "FuncPack.h"

bool getProcessFilePath( std::basic_string< TCHAR >& strProcessFilePath ) {
	DWORD dwLenCopied;
	TCHAR szProcessFilePath[ MAX_PATH + 2];
	
	dwLenCopied = ::GetModuleFileName( NULL, szProcessFilePath, MAX_PATH + 2 );
	
	strProcessFilePath = szProcessFilePath;
	return dwLenCopied <= MAX_PATH;
}

bool getProcessDirPath( std::basic_string< TCHAR >& strProcessDirPath ) {
	std::basic_string< TCHAR > strProcessFilePath;
	std::basic_string< TCHAR >::size_type posBackSlash;

	if (!getProcessFilePath( strProcessFilePath ))
		return false;
	posBackSlash = strProcessFilePath.rfind( _T( '\\' ) );
	if (posBackSlash == std::basic_string< TCHAR >::npos)
		return false;
	//
	strProcessDirPath = strProcessFilePath.substr( 0, posBackSlash );
	return true;
}
