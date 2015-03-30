#ifndef __CRRMSGHANDLER4FILEUPLOAD_H__
#define __CRRMSGHANDLER4FILEUPLOAD_H__
#include "CRRMsgHandlerBase.h"
#include "CRTypes.h"
//
class CRFUParam {
public:
	CRFUParam();
	~CRFUParam();
public:
	utf8_type m_strOwner;
	utf8_type m_strFId;
	unsigned int m_uPosStart;
	unsigned int m_uSegment;
	unsigned int m_uTotalSize;
};
//
class CRRMsgHandler4FileUpload : public CRRMsgHandlerBase {
public:
	CRRMsgHandler4FileUpload();
	virtual ~CRRMsgHandler4FileUpload();

public:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgFT* pRMsgFT );

private:
	bool _parseFUParam( const Json::Value& valParams, CRFUParam& fuParam );
	bool _saveFile( const CRFUParam* pFUParam, const CRRMsgFT* pRMsgFT );
	bool _createAccountDir( const CRFUParam* pFUParam, tstring_type& tstrAccountDir );
	void _sendSuccessAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, const CRFUParam& fuParam );
	void _sendFailedAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, const CRFUParam& fuParam );
};


#endif //__CRRMSGHANDLER4FILEUPLOAD_H__