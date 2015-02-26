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
	utf8_type m_strUserNameFrom;
	utf8_type m_strUserNameTo;

};



#endif //__CRATTETIONRECORD_H__