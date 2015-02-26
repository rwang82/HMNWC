#ifndef __CRATTETIONRECORDLIST_H__
#define __CRATTETIONRECORDLIST_H__
#include "CRLoadable.h"
#include "CRTypes.h"
#include <list>

class CRAttetionRecord;

class CRFetchAttetionRecordListParam {
public:
	enum ENUMFETCHMODE {
	    EFM_ATTETION = 0,
		EFM_ATTETIONED,
	};
	CRFetchAttetionRecordListParam();
	~CRFetchAttetionRecordListParam() {}

public:
	ENUMFETCHMODE m_eFetchMode;
	utf8_type m_strAccountName;
	unsigned int m_uIndexStart;
	unsigned int m_uCount;
};

class CRAttetionRecordList : public CRLoadable {
public:
	typedef std::list< CRAttetionRecord* > attetionrecord_list_type;
public:
	CRAttetionRecordList();
	virtual ~CRAttetionRecordList();
	
public:
	virtual bool loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode );

private:
	void _clearAllRecords();

public:
	attetionrecord_list_type m_listAttetionRecords;
};


#endif //__CRATTETIONRECORDLIST_H__