#ifndef __CRFTMSGMAKER_H__
#define __CRFTMSGMAKER_H__
#include "CRRMsgFT.h"

class CRFTMsgMaker {
public:
	CRFTMsgMaker();
	~CRFTMsgMaker();

public:
	static bool buildFTMsg( const CRRMsgFT& rmsgFT, unsigned char** ppBufFTMsg, unsigned int& uLenBufFTMsg );
};



#endif //__CRFTMSGMAKER_H__