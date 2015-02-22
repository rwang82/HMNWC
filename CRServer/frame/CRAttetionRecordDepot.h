#ifndef __CRATTETIONRECORDDEPOT_H__
#define __CRATTETIONRECORDDEPOT_H__
#include "CRTypes.h"
#include "CRAttetionRecordList.h"

class CRAttetionRecordDepot {
public:
	CRAttetionRecordDepot();
	~CRAttetionRecordDepot();

public:
	bool getRecords( const CRFetchAttetionRecordListParam& param, CRAttetionRecordList& listRecords, int& nErrCode );


};



#endif //__CRATTETIONRECORDDEPOT_H__