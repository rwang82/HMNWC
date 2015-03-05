#ifndef __CRRMSGHANDLER4FETCHACCOUNTPRODUCT_H__
#define __CRRMSGHANDLER4FETCHACCOUNTPRODUCT_H__
#include "CRRMsg.h"
#include "CRRMsgHandlerBase.h"
#include "CRTypes.h"
#include "CRProduct.h"
#include <list>
#include <map>

class CRRMsgHandler4FetchAccountProduct : public CRRMsgHandlerBase{
private:
	struct CRFetchAccountProductParam {
	    utf8_container_type m_containerAccountName; 
	}; 
	struct CRFetchAccountProductResult {
		typedef std::list< CRProduct* > product_list_type;
	    typedef std::map< utf8_type, product_list_type* > name2pl_map_type;
		CRFetchAccountProductResult();
		~CRFetchAccountProductResult();

	private:
		void _clearAll();

	public:
		name2pl_map_type m_mapName2ProductList;
	};

public:
	CRRMsgHandler4FetchAccountProduct();
	virtual ~CRRMsgHandler4FetchAccountProduct();
	
private:
	virtual void accept( const CRRMsgMetaData& rmsgMetaData, const CRRMsgJson* pRMsgJson );

private:
	bool _parseParams( const Json::Value& jsonRoot, CRFetchAccountProductParam& fapParam );
    bool _execute( const CRFetchAccountProductParam& fapParam, Json::Value& valAccountProductList, int& nErrCode );
	void _sendSuccessAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, Json::Value& valAccountProductList );
	void _sendFailedAck( int nCmdSN, const CRRMsgMetaData& rmsgMetaData, int nErrCode );

};



#endif //__CRRMSGHANDLER4FETCHACCOUNTPRODUCT_H__