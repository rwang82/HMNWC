#ifndef __HMNWPUPSTATE_SAVEPAYLOAD_H__
#define __HMNWPUPSTATE_SAVEPAYLOAD_H__
#include "HMNWPEnvCfg.h"
#include "HMNWPUPStateBase.h"
HMNWP_NAMESPACE_BEGIN

class HMNWPUPState_SavePayload : public HMNWPUPStateBase {
public:
	HMNWPUPState_SavePayload( HMNWPUnPackImpl* pUPImpl );
	virtual ~HMNWPUPState_SavePayload();

public:
	virtual void reset();
	virtual ENUMRAWBUFTYPE analyseRawBufType( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) const;
private:
	virtual void _parseRawData_BODYIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat );
	virtual void _parseRawData_TAILIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat );

};

HMNWP_NAMESPACE_END
#endif //__HMNWPUPSTATE_SAVEPAYLOAD_H__
