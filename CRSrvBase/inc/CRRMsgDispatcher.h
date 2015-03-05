#ifndef __CRRMSGDISPATCH_H__
#define __CRRMSGDISPATCH_H__
#include "HMTaskEngine.h"
#include "hmcmn_event_depot.h"
//
class CRSrvRoot;
//
class CRRMsgDispatcher {
public:
	CRRMsgDispatcher( CRSrvRoot* pSrvRoot );
	virtual ~CRRMsgDispatcher();

public:

private:
	void _onClientAccept( void* pParam1, void* pParam2 );
	void _onClientDisConnect( void* pParam1, void* pParam2 );
	void _onClientRequest( void* pParam1, void* pParam2, void* pParam3, void* pParam4 );

private:
	HMTaskEngine m_taskEngine4CmdDispatch;
	hmcmn::hmcmn_event_depot::arg2event_handler_type* m_pFuncObjClientAccept;
	hmcmn::hmcmn_event_depot::arg2event_handler_type* m_pFuncObjClientDisConnect;
	hmcmn::hmcmn_event_depot::arg4event_handler_type* m_pFuncObjClientRequest;
	CRSrvRoot* m_pSrvRoot;
};


#endif //__CRRMSGDISPATCH_H__