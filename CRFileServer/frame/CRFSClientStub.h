#ifndef __CRFSCLIENTSTUB_H__
#define __CRFSCLIENTSTUB_H__
#include "CRClientStub.h"
#include "CRRMsgRaw.h"
#include "CRRMsgFT.h"

class CRFSClientStub : public CRClientStub {
public:
	CRFSClientStub( CRSrvRoot* pSrvRoot, SOCKET sConnect, const sockaddr_in& sAddr );
	virtual ~CRFSClientStub();
	
private:
	virtual void onRMsg( const CRRMsgRaw& rmsgRaw );

private:
    //CRRMsgFT* _createRMsgFT( const unsigned char* pRawBuf, unsigned int uLenRawBuf );
    //bool _parseFTMetaData(  )
};


#endif //__CRFSCLIENTSTUB_H__