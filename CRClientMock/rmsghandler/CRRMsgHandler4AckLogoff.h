#ifndef __CRRMSGHANDLER4ACKLOGOFF_H__
#define __CRRMSGHANDLER4ACKLOGOFF_H__
#include "CRRMsgHandlerBase.h"

class CRRMsgHandler4AckLogoff : public CRRMsgHandlerBase{
public:
	CRRMsgHandler4AckLogoff();
	virtual ~CRRMsgHandler4AckLogoff();
	
private:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgBinary* pRMsgBinary );

private:
	bool _getLogoffResult( const CRRMsgJson* pRMsgJson );
};

#endif //__CRRMSGHANDLER4ACKLOGOFF_H__