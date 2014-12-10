#ifndef __CRACCOUNTDEPOT_H__
#define __CRACCOUNTDEPOT_H__
#include "CRAccountBase.h"
#include "HMTSHelper.h"
#include "CRTypes.h"
#include <map>

class CRAccountDepot {
public:
	typedef std::map< tstring_type, CRAccountBase* > name2obj_map_type;
public:
	CRAccountDepot();
	~CRAccountDepot();

public:
	bool hasAccount( const tstring_type& tstrAccountName, int& nErrCode );
	bool addAccount( CRAccountBase* pAccountNew, int& nErrCode );
	CRAccountBase* getAccount( const tstring_type& tstrAccountName, int& nErrCode );

private:
	bool _hasAccount( const tstring_type& tstrAccountName, int& nErrCode );
	void _clearAllAccount();
	bool _loadAccountFromDB( const tstring_type& tstrAccountName, int& nErrCode );

private:
	HMTSHelper m_tsAccess;
	name2obj_map_type m_mapName2AccountObj;
};


#endif //__CRACCOUNTDEPOT_H__