#include "stdafx.h"
#include "HMIniHelper.h"
//
#define DEFAULT_INI_VAL (0xEEFFEEFF)
//
HMIniHelper::HMIniHelper( const TCHAR* szIniFilePath )
: m_tstrIniFilePath( szIniFilePath ? szIniFilePath : _T("") ) {
	
}

HMIniHelper::~HMIniHelper() {

}

bool HMIniHelper::isReady() {
	return _isReady();
}

bool HMIniHelper::getInt( const tstring_type& tstrSectionName, const tstring_type& tstrKey, int& nVal ) {
	if ( !_isReady() || tstrSectionName.length() == 0 || tstrKey.length() == 0) {
		assert( false );
		return false;
	}
	int nValDest;

	nValDest = ::GetPrivateProfileInt( tstrSectionName.c_str(), tstrKey.c_str(), DEFAULT_INI_VAL, m_tstrIniFilePath.c_str() );
	if (nValDest == DEFAULT_INI_VAL) {
		return false;
	}
	//
	nVal = nValDest;
	return true;
}

bool HMIniHelper::getStr( const tstring_type& tstrSectionName, const tstring_type& tstrKey, tstring_type& tstrVal ) {
	if (!_isReady( ) || tstrSectionName.length( ) == 0 || tstrKey.length( ) == 0) {
		assert( false );
		return false;
	}
	DWORD dwDestStrLen;
	DWORD dwTmp;
	TCHAR* pDestStr = NULL;

	dwDestStrLen = ::GetPrivateProfileString( tstrSectionName.c_str( ), tstrKey.c_str( ), NULL, NULL, 0, m_tstrIniFilePath.c_str( ) );
	if (dwDestStrLen == 0) {
		assert( false );
		return false;
	}
	pDestStr = new TCHAR[dwDestStrLen + 2];
	dwTmp = ::GetPrivateProfileString( tstrSectionName.c_str(), tstrKey.c_str(), NULL, pDestStr, dwDestStrLen + 2, m_tstrIniFilePath.c_str() );
	assert( dwTmp < dwDestStrLen );
	pDestStr[dwTmp + 1] = 0;
	//
	tstrVal = pDestStr;
	delete[]pDestStr;
	pDestStr = NULL;
	return true;
}

bool HMIniHelper::_isReady() {
	return ( m_tstrIniFilePath.length() > 0 ) 
		&& ( ::_taccess( m_tstrIniFilePath.c_str( ), 0 ) == 0 );
}

