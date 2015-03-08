#ifndef __CRFSMSGLISTENER_H__
#define __CRFSMSGLISTENER_H__
#include "CRRMsgListener.h"
#include "CRRMsgFT.h"
#include "CRRMsgHandlerDepot.h"

class CRFSRMsgListener : public CRRMsgListener {
public:
	CRFSRMsgListener();
	virtual ~CRFSRMsgListener();
	
public:
	virtual void onAccept( CRSrvRoot* pSrvRoot, const CRRMsgMetaData& rmsgMetaData ) const;
    virtual void onDisConnect( CRSrvRoot* pSrvRoot, const CRRMsgMetaData& rmsgMetaData ) const;
	virtual void onRMsg( CRSrvRoot* pSrvRoot, const CRRMsgRaw& rmsgRaw ) const;

private:
	static CRRMsgFT* _createRMsgFT( const unsigned char* pRawBuf, unsigned int uLenRawBuf );
	void _initRMHD();
	
private:
	CRRMsgHandlerDepot m_rmsgHandlerDepot;
};


#endif //__CRFSMSGLISTENER_H__