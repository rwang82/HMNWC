#ifndef __CRRMSGPARSER_H__
#define __CRRMSGPARSER_H__
#include "json/json.h"
//
struct CRRMsgBase;
//
class CRRMsgParser {
private:
	CRRMsgParser();
	~CRRMsgParser();

public:
	static CRRMsgBase* createRMsg( const unsigned char* pRawBuf, unsigned int uLenRawBuf );

};


#endif //__CRRMSGPARSER_H__
