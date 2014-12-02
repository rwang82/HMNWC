#ifndef __HMNWESERVERPROXY_H__
#define __HMNWESERVERPROXY_H__

class HMNWEServerProxy {
public:
	HMNWEServerProxy();
	~HMNWEServerProxy();

private:
	OVERLAPPED m_olConnect;
};

#endif //__HMNWESERVERPROXY_H__
