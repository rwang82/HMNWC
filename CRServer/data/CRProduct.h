#ifndef __CRPRODUCT_H__
#define __CRPRODUCT_H__
#include "CRTypes.h"

class CRProduct {
public:
    tstring_type m_tstrTitle;
	tstring_type m_tstrPrice;
	tstring_type m_tstrDescribe;
	tstr_container_type m_containerImages;
	tstr_container_type m_containerKeywords;
};


#endif //__CRPRODUCT_H__