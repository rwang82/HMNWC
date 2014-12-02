#ifndef __CRRMSGHANDLERDEPOT_H__
#define __CRRMSGHANDLERDEPOT_H__
#include "CRTypes.h"
#include <map>
#include <functional>
#include "json/json.h"
#include "CRRMsgHandlerBase.h"
//
class CRRMsgHandlerDepot {
public:
	typedef std::map< int, CRRMsgHandlerBase* > cmdtype2handler_map_type;
public:
	CRRMsgHandlerDepot();
	virtual ~CRRMsgHandlerDepot();

public:
	bool regRMsgHandler( int cmdType, CRRMsgHandlerBase* pRMsgHandler );
	CRRMsgHandlerBase* getRMsgHandler( int cmdType ) const;

private:
	bool _hasRMsgHandler( int cmdType ) const;
	void _clearAllRMsgHandler();

private:
	cmdtype2handler_map_type m_mapCmd2Handler;
};


#endif //__CRRMSGHANDLERDEPOT_H__