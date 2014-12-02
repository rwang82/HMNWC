#ifndef __HMNWPUPSTATE_FINDHEADER_H__
#define __HMNWPUPSTATE_FINDHEADER_H__
#include "HMNWPEnvCfg.h"
#include "HMNWPUPStateBase.h"
HMNWP_NAMESPACE_BEGIN
//
struct HMNWPHeader;
//
class HMNWPUPState_FindHeader : public HMNWPUPStateBase {
public:
	HMNWPUPState_FindHeader( HMNWPUnPackImpl* pUPImpl );
	virtual ~HMNWPUPState_FindHeader();

public:
	virtual void reset();
	virtual ENUMRAWBUFTYPE analyseRawBufType( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) const;
private:
	virtual void _parseRawData_ALLIN( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat );
	virtual void _parseRawData_HEADIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat );
	virtual void _parseRawData_TAILIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat );
public:
	static const unsigned char* _findHeadStartPos( const unsigned char* pRawBuf, unsigned int uLenRawBuf );

private:
	void _fillNWPHeader( const unsigned char* pBuf, unsigned int uLenBuf );

private:
	unsigned int m_uFlag;
	HMNWPHeader* m_pNWPHeaderPending;
	unsigned int m_uLenNWPHeaderBufPending;
};

HMNWP_NAMESPACE_END
#endif //__HMNWPUPSTATE_FINDHEADER_H__
