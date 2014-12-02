#ifndef __CRMODULEACCOUNTMGR_H__
#define __CRMODULEACCOUNTMGR_H__
#include "CRModuleBase.h"
#include "CRRMsgBase.h"
//
struct CRRMsgMetaData;
struct CRLoginParam;
struct CRLogoffParam;
//
class CRModuleAccountMgr : public CRModuleBase{
public:
	CRModuleAccountMgr();
	~CRModuleAccountMgr();

public:
	bool doLogin( const CRLoginParam& loginParam, int& nErrCode );
	bool doLogoff( const CRLogoffParam& logoffParam, int& nErrCode );

};




#endif //__CRMODULEACCOUNTMGR_H__