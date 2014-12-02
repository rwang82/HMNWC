#ifndef __CRMODULECMDDISPATCH_H__
#define __CRMODULECMDDISPATCH_H__
#include "CRModuleBase.h"
#include "HMTaskEngine.h"
#include "hmcmn_event_depot.h"

class CRModuleCmdDispatch : public CRModuleBase {
public:
	CRModuleCmdDispatch();
	virtual ~CRModuleCmdDispatch();

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
};


#endif //__CRMODULECMDDISPATCH_H__