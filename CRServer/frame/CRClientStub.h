#ifndef __CRCLIENTSTUB_H__
#define __CRCLIENTSTUB_H__

class CRClientStub {
public:
	CRClientStub( SOCKET sConnect, const sockaddr_in& sAddr );
	~CRClientStub();

public:


private:
	SOCKET m_sConnect;
	sockaddr_in m_sAddr;

};



#endif //__CRCLIENTSTUB_H__