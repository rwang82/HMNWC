#include "stdafx.h"
#include "CRFSSettings.h"
#include "HMMisc.h"
#include "HMIniHelper.h"
#include <assert.h>
//
#define CRFSSETTINGS_FLAG_NONE (0x00000000)
#define CRFSSETTINGS_FLAG_LOAD_SUCCESS (0x00000001)

#define CRFSSETTINGS_FILENAME (_T("CRFSSettings.ini"))
#define CRFSSETTINGS_SEC_ROOT (_T("root"))
#define CRFSSETTINGS_KEY_FILEDEPOTDIR (_T("file_depot_dir"))

#define CSSRVSETTING_READ_INT( section, key, nVal ) \
	do { \
		if (!iniHelper.getInt( section, key, nVal )) { \
			assert( false ); \
			return false; \
		} \
	} while (0)
#define CSSRVSETTING_READ_STR( section, key, strVal ) \
	do { \
		if (!iniHelper.getStr( section, key, strVal )) { \
			assert( false ); \
			return false; \
		} \
	} while (0)

CRFSSettings::CRFSSettings() {
	_load();
}

CRFSSettings::~CRFSSettings() {

}

bool CRFSSettings::isReady() {
	return (m_uFlag & CRFSSETTINGS_FLAG_LOAD_SUCCESS);
}

bool CRFSSettings::_load() {
	tstring_type tstrCfgFilePath;
	//
	m_uFlag &= ~CRFSSETTINGS_FLAG_LOAD_SUCCESS;
	//
	if (!getProcessDirPath( tstrCfgFilePath )) {
		assert( false );
		return false;
	}
	tstrCfgFilePath += _T( '\\' );
	tstrCfgFilePath += CRFSSETTINGS_FILENAME;
	//
	HMIniHelper iniHelper( tstrCfgFilePath.c_str() );
	CSSRVSETTING_READ_STR( CRFSSETTINGS_SEC_ROOT, CRFSSETTINGS_KEY_FILEDEPOTDIR, m_tstrFileDepotDir );

	m_uFlag |= CRFSSETTINGS_FLAG_LOAD_SUCCESS;
	return true;
}
