#ifndef __CRSRVSETTINGS_H__
#define __CRSRVSETTINGS_H__
#include "tchar.h"
#include <string>

class CRSrvSettings {
public:
	typedef std::basic_string< TCHAR > utf8_type;
public:
	CRSrvSettings();
	~CRSrvSettings();

public:
	bool isReady();

private:
	bool _load();

public:
	int m_nListenPort;
private:
	unsigned int m_uFlag;
};

#endif //__CRSRVSETTINGS_H__




