#ifndef __CRLOGINRECORD_H__
#define __CRLOGINRECORD_H__
#include "CRRMsg.h"
#include "CRTypes.h"
//
struct CRLoginInfo {
    CRRMsgMetaData m_rmsgMetaData;
};
//
class CRLoginRecord {
	typedef std::map< ENUMOSTYPE, CRLoginInfo* > os2record_map_type;
public:
	CRLoginRecord();
	~CRLoginRecord();

public:
	bool addRecord( const CRRMsgMetaData& rmsgMetaData, ENUMOSTYPE eOSType, int& nErrCode );
	bool eraseRecord( const CRRMsgMetaData& rmsgMetaData, ENUMOSTYPE eOSType, int& nErrCode );
    bool eraseRecord( SOCKET sConnect );
	bool hasLogin( ENUMOSTYPE eOSType ) const;
	bool getLoginInfo( ENUMOSTYPE eOSType, CRLoginInfo& loginInfo ) const;

private:
	void _clearAllLoginInfo();

private:
	os2record_map_type m_mapOS2Record;
};


#endif //__CRLOGINRECORD_H__