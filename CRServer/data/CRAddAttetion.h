#ifndef __CRADDATTETION_H__
#define __CRADDATTETION_H__
#include "CRTypes.h"
#include "CRPersistenceObj.h"

class CRAddAttetion : public CRSaveable, public CRLoadable {
public:
	CRAddAttetion();
	virtual ~CRAddAttetion();
	
public:
	virtual bool save2DB( CRDBImplBase* pDBImpl, int& nErrCode ) const;
	virtual bool loadFromDB( void* pParamKey, CRDBImplBase* pDBImpl, int& nErrCode );

public:
	tstring_type m_tstrUserName;
	tstring_type m_tstrDestUserName;

};



#endif //__CRADDATTETION_H__