#ifndef __CRMODULEACCOUNTMGR_H__
#define __CRMODULEACCOUNTMGR_H__
#include "CRModuleBase.h"
#include "CRRMsgBase.h"
#include "CRAccountBase.h"
#include "CRAccountDepot.h"
#include "HMTSHelper.h"
#include "hmcmn_event_depot.h"
#include <map>
//
struct CRRMsgMetaData;
//
class CRModuleAccountMgr : public CRModuleBase{
public:
	typedef std::map< SOCKET, CRAccountBase* > socket2account_map_type;
public:
	CRModuleAccountMgr();
	~CRModuleAccountMgr();

public:
	bool doLogin( const CRLoginParam& loginParam, int& nErrCode );
	bool doLogoff( const CRLogoffParam& logoffParam, int& nErrCode );
	bool doRegAccount( const CRAccountRegParam& accountRegParam, int& nErrCode );

public:
	const CRAccountBase* getAccount( SOCKET sConnect ) const;

	// event handler.
public:
	void onEvtClientAccept( void* pParam1, void* pParam2 );
	void onEvtClientDisConnect( void* pParam1, void* pParam2 );

private:
	void _addAccount2SocketMap( SOCKET sConnect, CRAccountBase* pAccount );
	void _eraseAccountFromSocketMap( SOCKET sConnect );
	void _eraseAccountFromSocketMap( CRAccountBase* pAccount );
	bool _hasAccountInSocketMap( SOCKET sConnect ) const;
	bool _hasAccountInSocketMap( CRAccountBase* pAccount ) const;
	CRAccountBase* _getAccountInSocketMap( SOCKET sConnect );

private:
	//hmcmn::hmcmn_event_depot::arg2event_handler_type* m_pFuncObjClientAccept;
	//hmcmn::hmcmn_event_depot::arg2event_handler_type* m_pFuncObjClientDisConnect;
	CRAccountDepot m_accountDepot;
	HMTSHelper m_tsAccess;
	socket2account_map_type m_mapSocket2Account;
};




#endif //__CRMODULEACCOUNTMGR_H__