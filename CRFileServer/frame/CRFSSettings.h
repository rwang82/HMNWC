#ifndef __CRFSSETTINGS_H__
#define __CRFSSETTINGS_H__
#include "tchar.h"
#include <string>

class CRFSSettings {
public:
	typedef std::basic_string< TCHAR > tstring_type;
public:
	CRFSSettings();
	~CRFSSettings();
	
public:
	bool isReady();

private:
    bool _load();

public:
	tstring_type m_tstrFileDepotDir;
private:
	unsigned int m_uFlag;
};


#endif //__CRFSSETTINGS_H__