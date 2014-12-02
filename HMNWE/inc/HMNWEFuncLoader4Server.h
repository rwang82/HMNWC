#ifndef __HMNWEFUNCLOADER4SERVER_H__
#define __HMNWEFUNCLOADER4SERVER_H__

class HMNWEFuncLoader4Server {
	typedef void( WINAPI *pfnGetAcceptExSockaddrsType )(
		PVOID lpOutputBuffer,
		DWORD dwReceiveDataLength,
		DWORD dwLocalAddressLength,
		DWORD dwRemoteAddressLength,
		LPSOCKADDR* localSockaddr,
		LPINT localSockaddrLength,
		LPSOCKADDR* remoteSockaddr,
		LPINT remoteSockaddrLength );
public:
	~HMNWEFuncLoader4Server();
	static HMNWEFuncLoader4Server* getInstance();
private:
	HMNWEFuncLoader4Server();


private:
	bool _loadFunc();

public:
	pfnGetAcceptExSockaddrsType m_pfnGetAcceptExSockaddrs;
};


#endif //__HMNWEFUNCLOADER4SERVER_H__
