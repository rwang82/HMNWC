#ifndef __CRRMSGHANDLER4FILEUPLOAD_H__
#define __CRRMSGHANDLER4FILEUPLOAD_H__
#include "CRRMsgHandlerBase.h"

class CRRMsgHandler4FileUpload : public CRRMsgHandlerBase {
public:
	CRRMsgHandler4FileUpload();
	virtual ~CRRMsgHandler4FileUpload();

public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgFT* pRMsgFT );
};


#endif //__CRRMSGHANDLER4FILEUPLOAD_H__