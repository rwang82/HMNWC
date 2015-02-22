#ifndef __CRMODULEATTETIONRECORD_H__
#define __CRMODULEATTETIONRECORD_H__
#include "CRModuleBase.h"
#include "CRAttetionRecordList.h"
#include "CRAttetionRecordDepot.h"

class CRModuleAttetionRecord : public CRModuleBase {
public:
	CRModuleAttetionRecord();
	virtual ~CRModuleAttetionRecord();

public:
	bool doFetchRecords( const CRFetchAttetionRecordListParam& param, CRAttetionRecordList& listRecords, int& nErrCode );

private:
	CRAttetionRecordDepot m_depotAttetionRecord;
};



#endif //__CRMODULEATTETIONRECORD_H__