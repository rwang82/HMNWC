#ifndef __CRRMSGHANDLER4FETCHFILEMETADATA_H__
#define __CRRMSGHANDLER4FETCHFILEMETADATA_H__
#include "CRRMsgHandlerBase.h"

class CRRMsgHandler4FetchFileMetaData : public CRRMsgHandlerBase{
public:
	CRRMsgHandler4FetchFileMetaData();
	virtual ~CRRMsgHandler4FetchFileMetaData();
	
public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgFT* pRMsgFT );
};




#endif //__CRRMSGHANDLER4FETCHFILEMETADATA_H__