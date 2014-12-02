#ifndef __CRTASKRMSGDISPATCH_H__
#define __CRTASKRMSGDISPATCH_H__
#include "HMTaskEngine.h"
//
struct CRRMsgRaw;
//
class CRTaskRMsgDispatch : public HMTaskBase {
public:
	CRTaskRMsgDispatch( const unsigned char* pRawBuf, unsigned int uLenRawBuf );
	virtual ~CRTaskRMsgDispatch();

public:
	virtual void Run();

private:
	unsigned char* m_pRawBuf;
	unsigned int m_uLenRawBuf;
};


#endif //__CRTASKRMSGDISPATCH_H__