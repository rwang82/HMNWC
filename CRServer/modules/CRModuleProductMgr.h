#ifndef __CRMODULEPRODUCTMGR_H__
#define __CRMODULEPRODUCTMGR_H__
#include "CRModuleBase.h"
#include "CRProductDepot.h"
#include "CRRMsg.h"
#include "CRTypes.h"

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
	bool fillAccountProducts2Json( const CRFetchAccountProducts& fapParam, Json::Value& valProducts, int& nErrCode );
private:
	CRProductDepot m_productDepot;

};



#endif //__CRMODULEPRODUCTMGR_H__