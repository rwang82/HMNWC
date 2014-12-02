#ifndef __PRINT_ATOM_H__
#define __PRINT_ATOM_H__
#include "HMTSHelper.h"

class HMAtomPrint {
public:
	virtual ~HMAtomPrint();
	static HMAtomPrint* getInstance();
private:
	HMAtomPrint();

public:
	void out( const TCHAR* szData );

private:
	HMTSHelper m_tsHelper;
};


#endif //__PRINT_ATOM_H__