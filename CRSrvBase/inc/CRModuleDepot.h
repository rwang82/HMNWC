#ifndef __CRMODULEDEPOT_H__
#define __CRMODULEDEPOT_H__
#include "CRModuleBase.h"
#include <map>
//
class HMTSHelper;
//
class CRSRV_API CRModuleDepot {
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
	HMTSHelper* m_pTSAccess;
	id2module_map_type* m_pMapId2Module;
};

#endif //__CRMODULEDEPOT_H__



