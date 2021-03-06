#ifndef __CRSERVERROOT_H__
#define __CRSERVERROOT_H__
//
namespace hmnwp {
	class HMNWPServer;
}
namespace hmcmn {
    class hmcmn_event_depot;
}
class CRSrvEventHandler;
class CRSrvSettings;
class CRRMsgHandlerDepot;
class CRModuleDepot;
class CRClientStubDepot;
class CRSrvDBProxy;
//
class CRServerRoot {
public:
	CRServerRoot();
	~CRServerRoot();

private:
	void _init();
	void _unInit();
	void _initModules();
	void _unInitModules();
	void _initCmdHandlers();
public:
	hmcmn::hmcmn_event_depot* m_pEventDepot;
	CRRMsgHandlerDepot* m_pRMsgHandlerDepot;
	CRClientStubDepot* m_pClientStubDepot;
	CRModuleDepot* m_pModuleDepot;
	hmnwp::HMNWPServer* m_pNWPServer;
	CRSrvDBProxy* m_pSrvDBProxy;

private:
	CRSrvEventHandler* m_pSEHandler;
	CRSrvSettings* m_pCRSrvSettings;
};

extern CRServerRoot g_CRSrvRoot;

#endif //__CRSERVERROOT_H__

