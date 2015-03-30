#ifndef __CRFILESRVAPP_H__
#define __CRFILESRVAPP_H__
//
class CRFSSettings;

class CRFileSrvApp {
public:
	CRFileSrvApp();
	~CRFileSrvApp();
public:
	void run();

private:
	void _init();
	void _unInit();

public:
	const CRFSSettings* m_pFSSettings;
};



#endif //__CRFILESRVAPP_H__