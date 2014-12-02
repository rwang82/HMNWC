#ifndef __CRMODULELOGIN_H__
#define __CRMODULELOGIN_H__
#include "CRModuleBase.h"
#include "hmcmn_event_depot.h"
//
enum ENUMLOGINSTATETYPE {
    ELOGIN_STATE_LOGOFF = 0,
	ELOGIN_STATE_LOGGINGOFF,
	ELOGIN_STATE_LOGIN,
	ELOGIN_STATE_LOGGING,
};

class CRModuleLogin : public CRModuleBase {
public:
	CRModuleLogin();
	virtual ~CRModuleLogin();

public:
	ENUMLOGINSTATETYPE getLoginState() const;
	
private:
	void _doLogin();
	void _doLogoff();
	void _setLoginState( ENUMLOGINSTATETYPE eLoginState );
	void _enableConnect();
	// event handler
private:
	void _onConnected();
	void _onDisConnected();
	void _onLoginBtnClick();
	void _onLoginAck( void* pParam1, void* pParam2 );
	void _onLogoffAck( void* pParam1, void* pParam2 );

private:
	ENUMLOGINSTATETYPE m_eLoginState;
	hmcmn::hmcmn_event_depot::arg0event_handler_type* m_pfobj4OnLoginBtnClick;
    hmcmn::hmcmn_event_depot::arg0event_handler_type* m_pfobj4OnConnected;
	hmcmn::hmcmn_event_depot::arg0event_handler_type* m_pfobj4OnDisConnected;
	hmcmn::hmcmn_event_depot::arg2event_handler_type* m_pfobj4LoginAck;
	hmcmn::hmcmn_event_depot::arg2event_handler_type* m_pfobj4LogoffAck;
};

#endif //__CRMODULELOGIN_H__