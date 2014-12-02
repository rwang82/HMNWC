#ifndef __HMPENDINGDATADEPOT_H__
#define __HMPENDINGDATADEPOT_H__
#include "HMNWPEnvCfg.h"
#include <list>
HMNWP_NAMESPACE_BEGIN
//
struct HMPendingData {
	HMPendingData( const unsigned char* pBufPending, unsigned int uLenBufPending );
	~HMPendingData();

	unsigned char* m_pRawBuf;
	unsigned int m_uLenRawBuf;
	unsigned int m_uIndexPendingStart;
	unsigned int m_uId;

private:
	unsigned int _allocalId() const;
};
//
class HMPendingDataDepot {
public:
	typedef std::list< HMPendingData* > pendingdata_container_type;
public:
	HMPendingDataDepot();
	~HMPendingDataDepot();

public:
	//bool getPendingData( unsigned char** ppBufPending, unsigned int& uLenBufPending );
	//unsigned int getPendingDataLen();
	bool pushback( const unsigned char* pBufPending, unsigned int uLenBufPending );
	const HMPendingData* get1stPendingData() const;
	HMPendingData* get1stPendingData();
	void del1stPendingData();
	const HMPendingData* getLastPendingData() const;
	HMPendingData* getLastPendingData();
	unsigned int getPendDataCount() const;

private:
	void _clearAllPendData();

private:
	pendingdata_container_type m_containerPendingData;
};

HMNWP_NAMESPACE_END
#endif //__HMPENDINGDATADEPOT_H__