#ifndef __CRATTETIONRECORD_H__
#define __CRATTETIONRECORD_H__
#include "CRTypes.h"
#include "CRSaveable.h"

class CRAttetionRecord : public CRSaveable {
public:
	CRAttetionRecord();
	virtual ~CRAttetionRecord();
	
public:
	virtual bool save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const;

public:
	tstring_type m_tstrUserName;
	tstring_type m_tstrDestUserName;

};



#endif //__CRATTETIONRECORD_H__