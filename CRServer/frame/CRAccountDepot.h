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
	bool hasAccount( const tstring_type& tstrAccountName );
	bool addAccount( CRAccountBase* pAccountNew );
	CRAccountBase* getAccount( const tstring_type& tstrAccountName ) const;

private:
	bool _hasAccount( const tstring_type& tstrAccount ) const;
	void _clearAllAccount();

private:
	HMTSHelper m_tsAccess;
	name2obj_map_type m_mapName2AccountObj;
};


#endif //__CRACCOUNTDEPOT_H__