#ifndef __HMNWPUNPACKIMPL_H__
#define __HMNWPUNPACKIMPL_H__
#include "HMNWPEnvCfg.h"
#include "HMNWPUPStateBase.h"
#include "hmcmn_event.h"
#include <list>
HMNWP_NAMESPACE_BEGIN
//
struct HMNWPHeader;
struct HMNWPPackage;
class HMPendingDataDepot;
class HMNWPPackageDepot;
//
struct HMRawBufData {
	HMRawBufData( const unsigned char* pRawBuf, unsigned int uLenRawData );
	~HMRawBufData();
	unsigned char* m_pRawBuf;
	unsigned int m_uLenRawBuf;
	unsigned int m_uIndexCheckStart;
};
//
class HMNWPUnPackImpl {
	friend class HMNWPUPState_FindHeader;
	friend class HMNWPUPState_SavePayload;
	friend class HMNWPUPState_CheckCRC16;

public:
	typedef std::list< HMRawBufData* > hmrawbufdata_container_type;
	typedef std::list< HMNWPPackage* > hmnwppackage_container_type;
public:
	HMNWPUnPackImpl();
	~HMNWPUnPackImpl();

public:
	void onRecvRawData( const unsigned char* pRawBuf, unsigned int uLenRawBuf );

private:
	HMNWPUPStateBase* _getCurNWPUPState();
	void _fillNWPHeader( const HMNWPHeader* pNWPHeader );
	void _clearNWPHeader();
	unsigned int _getLenBufPayloadReady() const { return m_uLenBufPayloadReady; }
	bool _fillBufPayload( const unsigned char* pBufPayload, unsigned int uLenBuf );
	void _clearBufPayload();
	const HMNWPHeader* _getNWPHeader() const { return m_pNWPHeader; }
	bool _checkCRC16( unsigned __int16 uCRC16 );
	void _reset();
	void _parseRawBufData( const unsigned char* pRawBuf, unsigned int uLenRawBuf );
	bool _checkValidRawBuf( const unsigned char* pRawBuf, unsigned int uLenRawBuf );
	void _moveCheckStartPosTo( const unsigned char* pPosCheckStart );
	//void _moveCheckStartPos1Step();
	void _reParseRawBufData();
	void _onEvtPackageReady( const HMNWPHeader* pNWPHeader, const unsigned char* pBufPayload );
	void _onEvtRawBufReady( const unsigned char* pRawBuf, unsigned int uLenRawBuf );
	
public:
	hmcmn::hm_event< const HMNWPHeader*, const unsigned char* > m_eventPackageReady;
	hmcmn::hm_event< const unsigned char*, unsigned int > m_eventRawBufReady;

private:
	HMPendingDataDepot* m_pDepotPendingData;
	HMNWPPackageDepot* m_pDepotPackage;
	HMNWPHeader* m_pNWPHeader;
	unsigned char* m_pBufPayload;
	unsigned int m_uLenBufPayload;
	unsigned int m_uLenBufPayloadReady;
	unsigned int m_uFlag;
	HMNWPUPState_FindHeader* m_pNWPUPStateFindHeader;
	HMNWPUPState_SavePayload* m_pNWPUPStateSavePayload;
	HMNWPUPState_CheckCRC16* m_pNWPUPStateCheckCRC16;
};

HMNWP_NAMESPACE_END
#endif //__HMNWPUNPACKIMPL_H__
