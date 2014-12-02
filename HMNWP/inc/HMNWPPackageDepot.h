#ifndef __HMNWPPACKAGEDEPOT_H__
#define __HMNWPPACKAGEDEPOT_H__
#include "hmcmn_event.h"
#include "HMNWPEnvCfg.h"
#include <list>
HMNWP_NAMESPACE_BEGIN
//
struct HMNWPHeader;
struct HMNWPPackageBox {
	HMNWPPackageBox( const HMNWPHeader* pNWPHeader, const unsigned char* pBufPayload );
	~HMNWPPackageBox();
	HMNWPHeader* m_pHeader;
	unsigned char* m_pBufPayload;
};
//
class HMNWPPackageDepot {
public:
	typedef std::list< HMNWPPackageBox* > packagebox_contianer_type;
public:
	HMNWPPackageDepot();
	~HMNWPPackageDepot();

public:
	void pushbackPackage( const HMNWPHeader* pNWPHeader, const unsigned char* pBufPayload );

private:
	void _clearAllPackage();
	bool _isRawBufReady() const;
	unsigned int _getRawBufTotalLen() const;
	bool _fillRawBufTotal( unsigned char* pRawBuf, unsigned int uLenRawBuf ) const;

public:
	static bool isValidNWPHeader( const HMNWPHeader* pNWPHeader );

public:
	hmcmn::hm_event< const unsigned char*, unsigned int > m_eventRawBufReady;

private:
	packagebox_contianer_type m_containerPackageBox;
};

HMNWP_NAMESPACE_END
#endif //__HMNWPPACKAGEDEPOT_H__
