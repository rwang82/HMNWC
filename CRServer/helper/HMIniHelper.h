#ifndef __HMINIHELPER_H__
#define __HMINIHELPER_H__
#include "tchar.h"
#include <string>

class HMIniHelper {
public:
	typedef std::basic_string< TCHAR > tstring_type;
public:
	HMIniHelper( const TCHAR* pIniFilePath );
	~HMIniHelper( );

public:
	bool isReady();
	bool getInt( const tstring_type& tstrSectionName, const tstring_type& tstrKey, int& nVal );
	bool getStr( const tstring_type& tstrSectionName, const tstring_type& tstrKey, tstring_type& tstrVal);

private:
	bool _isReady();

private:
	tstring_type m_tstrIniFilePath;
};



#endif //__HMINIHELPER_H__