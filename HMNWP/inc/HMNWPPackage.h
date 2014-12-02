//////////////////////////////////////////////////////////////////////////
// |---------------|---------------------------------|-------|
// |  HMNWPHeader  |             payload             | crc16 |
// |---------------|---------------------------------|-------|
//////////////////////////////////////////////////////////////////////////
#ifndef __HMNWPPACKAGEDEF_H__
#define __HMNWPPACKAGEDEF_H__
#include "HMNWEEnvCfg.h"
#include "HMNWPEnvCfg.h"
#include <deque>
HMNWP_NAMESPACE_BEGIN
//
extern const unsigned char HMNWP_PACKAGE_BEG1;
extern const unsigned char HMNWP_PACKAGE_BEG2;
extern const unsigned char HMNWP_PACKAGE_VER;
//
#pragma pack(1)
struct HMNWPHeader {
	HMNWPHeader();
	~HMNWPHeader();
	void reset();
	unsigned char m_ucBeg1;
	unsigned char m_ucBeg2;
	unsigned char m_ucVer;
	__int16 m_i16BundleBufIndex; // a bundle buffer index.
	__int16 m_i16PackageIndex; // a big bundle of buffer will separate to a group of packages.
	__int16 m_i16PackageCount; // the count of group of package to make up a bundle buffer.
	unsigned char m_ucBodyProtocol;
	__int16 m_i16PayloadLen;
};
#pragma pack()
//
#define HMNWP_LEN_NWPHEADER (sizeof( HMNWPHeader ))
#define HMNWP_LEN_CRC16 (2)
#define HMNWP_LEN_PAYLOAD_MAX (BUFSIZE_SEND_NWDATA - HMNWP_LEN_NWPHEADER - HMNWP_LEN_CRC16)
//
struct HMNWPPackage{
public:
	HMNWPPackage( const HMNWPHeader* header, const unsigned char* pBufPayload );
	~HMNWPPackage();

public:
	inline bool isPackageValid();
	const unsigned char* getBufData() const { return m_pBufPackage; };
	unsigned int getLenBufData() const { return m_uLenBufData; }

private:
	unsigned char* m_pBufPackage;
	unsigned int m_uLenBufData;
	unsigned char m_ucFlag;
};
//
typedef std::deque< HMNWPPackage* > nwppackage_container_type;
//
HMNWP_NAMESPACE_END
#endif //__HMNWPPACKAGEDEF_H__
