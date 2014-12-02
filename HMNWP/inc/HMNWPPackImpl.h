#ifndef __HMNWPPACKIMPL_H__
#define __HMNWPPACKIMPL_H__
#include "HMNWPPackage.h"
HMNWP_NAMESPACE_BEGIN
//
class HMNWPPackImpl {
public:
	HMNWPPackImpl();
	~HMNWPPackImpl();

public:
	static bool createPackages( const unsigned char* pRawBuf, unsigned int uLenRawData, nwppackage_container_type& containerNWPPackage );
	static void destroyPackages( nwppackage_container_type* pContainerNWPPackage );
	
};

HMNWP_NAMESPACE_END
#endif //__HMNWPPACKIMPL_H__
