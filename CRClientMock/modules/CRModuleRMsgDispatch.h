#ifndef __CRMODULERMSGDISPATCH_H__
#define __CRMODULERMSGDISPATCH_H__
#include "CRModuleBase.h"
#include "HMTaskEngine.h"
#include "CRCCommProxyBase.h"

class CRModuleRMsgDispatch : public CRModuleBase {
public:
	CRModuleRMsgDispatch();
	virtual ~CRModuleRMsgDispatch();

public:
	

private:
	void _onRecvBuffer( void* pParam1, void* pParam2 );

private:
	HMTaskEngine m_taskEngine4CmdDispatch;
	CRCCommProxyBase::arg2_funcobj_type* m_pFuncObj4RecvBuffer;

};




#endif //__CRMODULERMSGDISPATCH_H__


