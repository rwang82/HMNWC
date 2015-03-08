////////////////////////////////////////////////////////////////
// file transfer remote message protocol.
////////////////////////////////////////////////////////////////
#ifndef __CRRMSGFT_H__
#define __CRRMSGFT_H__
#include "CRRMsgBase.h"
#include "json/json.h"
#include <string>
//
class CRClientStub;
//
class CRRMsgFT : public CRRMsgBase{
public:
	CRRMsgFT( unsigned char ucVer, const unsigned char* pBufMetaData, __int16 lenMetaData, 
		const unsigned char* pBufPayload, __int32 lenPayload );
	~CRRMsgFT();

protected:
	virtual void _execute( const CRRMsgMetaData& rmsgMetaData, CRRMsgHandlerBase* pRMsgHandler );

private:
	bool _parseMetaData( const Json::Value& jsonRoot );

public:
    unsigned char m_ucVer;
	Json::Value m_jsonRoot;
	__int32 m_lenPayload;
	const unsigned char* m_pBufPayload;
};




#endif //__CRRMSGFU_H__