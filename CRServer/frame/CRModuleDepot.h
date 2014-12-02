#ifndef __CRMODULEDEPOT_H__
#define __CRMODULEDEPOT_H__
#include "CRModuleBase.h"
#include "HMTSHelper.h"
#include <map>

class CRModuleDepot {
public:
	typedef unsigned int module_id_type;
	typedef std::map< module_id_type, CRModuleBase* > id2module_map_type;
public:
	CRModuleDepot();
	~CRModuleDepot();

public:
	bool addModule( unsigned int uModuleID, CRModuleBase* pModule );
	CRModuleBase* getModule( unsigned int uModuleID );
	bool hasModule( unsigned int uModuleID );
	void deleteAllModule() { _deleteAllModule(); };

private:
	bool _hasModule( unsigned int uModuleID );
	void _deleteAllModule();

private:
	HMTSHelper m_tsAccess;
	id2module_map_type m_mapId2Module;
};

#endif //__CRMODULEDEPOT_H__



