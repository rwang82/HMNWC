#include "stdafx.h"
#include "CRSrvSettings.h"
#include "HMMisc.h"
#include "HMIniHelper.h"
#include <assert.h>
//
#define CRSRVSETTINGS_FLAG_NONE (0x00000000)
#define CRSRVSETTINGS_FLAG_LOAD_SUCCESS (0x00000001)

#define CRSRVSETTINGS_FILENAME (_T("CRSrvSettings.ini"))

#define CRSRVSETTINGS_SEC_ROOT (_T("root"))
#define CRSRVSETTINGS_KEY_LISTEN_PORT (_T("listen_port"))

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
//
CRSrvSettings::CRSrvSettings()
: m_uFlag( CRSRVSETTINGS_FLAG_NONE ) {
	_load();
}

CRSrvSettings::~CRSrvSettings() {

}

bool CRSrvSettings::_load() {
	tstring_type tstrCfgFilePath;
	//
	m_uFlag &= ~CRSRVSETTINGS_FLAG_LOAD_SUCCESS;
	//
	if (!getProcessDirPath( tstrCfgFilePath )) {
		assert( false );
		return false;
	}
	tstrCfgFilePath += _T( '\\' );
	tstrCfgFilePath += CRSRVSETTINGS_FILENAME;
	//
	HMIniHelper iniHelper( tstrCfgFilePath.c_str() );
	CSSRVSETTING_READ_INT( CRSRVSETTINGS_SEC_ROOT, CRSRVSETTINGS_KEY_LISTEN_PORT, m_nListenPort );


	m_uFlag |= CRSRVSETTINGS_FLAG_LOAD_SUCCESS;
	return true;
}

bool CRSrvSettings::isReady() {
	return (m_uFlag & CRSRVSETTINGS_FLAG_LOAD_SUCCESS);
}

