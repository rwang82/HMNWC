#ifndef __CRMODULEPRODUCTMGR_H__
#define __CRMODULEPRODUCTMGR_H__
#include "CRModuleBase.h"
#include "CRProductDepot.h"
#include "CRRMsg.h"

class CRProductPublishParam {
public:
	const CRRMsgMetaData* m_pRMsgMetaData;
	CRProduct m_product;
};

class CRModuleProductMgr : public CRModuleBase {
public:
	CRModuleProductMgr();
	~CRModuleProductMgr();

public:
	bool doPublishProduct( const CRProductPublishParam& paramPublishProduct, int& nErrCode );

private:
	CRProductDepot m_productDepot;

};



#endif //__CRMODULEPRODUCTMGR_H__