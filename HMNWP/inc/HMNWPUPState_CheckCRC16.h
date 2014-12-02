#ifndef __HMNWPUPSTATE_CHECKCRC16_H__
#define __HMNWPUPSTATE_CHECKCRC16_H__
#include "HMNWPUPStateBase.h"
#include "HMNWPPackage.h"
HMNWP_NAMESPACE_BEGIN
//
class HMNWPUPState_CheckCRC16 : public HMNWPUPStateBase {
public:
	HMNWPUPState_CheckCRC16( HMNWPUnPackImpl* pUPImpl );
	virtual ~HMNWPUPState_CheckCRC16();

public:
	virtual void reset();
	virtual ENUMRAWBUFTYPE analyseRawBufType( const unsigned char* pRawBuf, unsigned int uLenRawBuf ) const;

private:
	virtual void _parseRawData_BODYIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat );
	virtual void _parseRawData_TAILIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat );

private:
	unsigned char m_bufCRC16[ HMNWP_LEN_CRC16 ];
	unsigned int m_uLenCRC16Ready;

};

HMNWP_NAMESPACE_END
#endif // __HMNWPUPSTATE_CHECKCRC16_H__
