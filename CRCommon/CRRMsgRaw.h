#ifndef __CRRMSGRAW_H__
#define __CRRMSGRAW_H__
//
struct CRRMsgMetaData {
	CRRMsgMetaData();
	CRRMsgMetaData( SOCKET sConnect, const sockaddr_in& sAddr );
	~CRRMsgMetaData();
    SOCKET m_sConnect;
	sockaddr_in m_sAddr;
	// may be need more. eg: time.
};
//
struct CRRMsgRaw {
	CRRMsgRaw( SOCKET sConnect, const sockaddr_in& sAddr, const unsigned char* pRawBuf, unsigned int uLenRawBuf );
	~CRRMsgRaw();
    CRRMsgMetaData m_metaData;
	unsigned char* m_pRawBuf;
	unsigned int m_uLenRawBuf;
};



#endif //__CRRMSGRAW_H__