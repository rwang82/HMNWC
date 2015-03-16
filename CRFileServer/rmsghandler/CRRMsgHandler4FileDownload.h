#ifndef __CRRMSGHANDLER4FILEDOWNLOAD_H__
#define __CRRMSGHANDLER4FILEDOWNLOAD_H__
#include "CRRMsgHandlerBase.h"

class CRRMsgHandler4FileDownload : public CRRMsgHandlerBase {
public:
	CRRMsgHandler4FileDownload();
	virtual ~CRRMsgHandler4FileDownload();
	
public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgFT* pRMsgFT );
};

#endif //__CRRMSGHANDLER4FILEDOWNLOAD_H__