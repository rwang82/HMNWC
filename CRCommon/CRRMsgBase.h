#ifndef __CRRMSGBASE_H__
#define __CRRMSGBASE_H__
#include "CRTypes.h"
//
class CRRMsgHandlerBase;
struct CRRMsgMetaData;
class CRClientStub;
//
struct CRRMsgBase {
public:
	CRRMsgBase();
	virtual ~CRRMsgBase();

public:
	void execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler );

protected:
	virtual void _execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler ) = 0;

public:
	int m_nCmdType;
	int m_nCmdSN;
	ENUMOSTYPE m_eOSType;
};



#endif //__CRRMSGBASE_H__