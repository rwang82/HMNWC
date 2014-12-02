#ifndef __HMNWPUPSTATEBASE_H__
#define __HMNWPUPSTATEBASE_H__
#include "HMNWPEnvCfg.h"
#include <assert.h>
HMNWP_NAMESPACE_BEGIN
//
enum ENUMRAWBUFTYPE {
	ERAWBUF_TYPE_UNKNOWN = -1,
	ERAWBUF_TYPE_NOTIN = 0,
	ERAWBUF_TYPE_BODYIN_ONLY,
	ERAWBUF_TYPE_TAILIN_ONLY,
	ERAWBUF_TYPE_ALLIN,
	ERAWBUF_TYPE_HEADIN_ONLY
};
//
class HMNWPUnPackImpl;
//
class HMNWPUPStateBase {
public:
	HMNWPUPStateBase( HMNWPUnPackImpl* pUPImpl ) { m_pUPImpl = pUPImpl; };
	virtual ~HMNWPUPStateBase() {};

public:
	virtual void reset() = 0;	
	virtual ENUMRAWBUFTYPE analyseRawBufType( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) const = 0;
private:
	virtual void _parseRawData_BODYIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat );
	virtual void _parseRawData_TAILIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat );
	virtual void _parseRawData_ALLIN( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat );
	virtual void _parseRawData_HEADIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat );

public:
	void parseRawData( const unsigned char* pRawBuf, unsigned int uLenRawBuf, ENUMRAWBUFTYPE eRawBufType, unsigned int& uLenEat );

protected:
	HMNWPUnPackImpl* m_pUPImpl;
};

HMNWP_NAMESPACE_END
#endif //__HMNWPUPSTATEBASE_H__
