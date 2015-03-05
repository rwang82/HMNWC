#ifndef __CREVENTDEPOT_H__
#define __CREVENTDEPOT_H__
#include "hmcmn_event_ex.h"
#include "HMTSHelper.h"
#include "hm_cmn_envcfg.h"
#include <map>
#include <functional>  

class CRSRV_API CREventDepot {
public:
	typedef std::function< void() > arg0event_handler_type;
	typedef hmcmn::hmcmn_event_arg0_ex< void > arg0event_obj_type;
	typedef std::map< unsigned int, arg0event_obj_type* > arg0evtid2obj_map_type;
	typedef std::function< void( void*, void* ) > arg2event_handler_type;
	typedef hmcmn::hmcmn_event_arg2_ex< void, void*, void* > arg2event_obj_type;
	typedef std::map< unsigned int, arg2event_obj_type* > arg2evtid2obj_map_type;
	typedef std::function< void( void*, void*, void*, void* ) > arg4event_handler_type;
	typedef hmcmn::hmcmn_event_arg4_ex< void, void*, void*, void*, void* > arg4event_obj_type;
	typedef std::map< unsigned int, arg4event_obj_type* > arg4evtid2obj_map_type;
public:
    CREventDepot();
    ~CREventDepot();

public:
	// arg0
	bool bind( unsigned int uEventId, arg0event_handler_type* pEventHandler );
	void unbind( unsigned int uEventId, const arg0event_handler_type* pEventHandler );
	void fire( unsigned int uEventId );
    // arg2
	bool bind( unsigned int uEventId, arg2event_handler_type* pEventHandler );
	void unbind( unsigned int uEventId, const arg2event_handler_type* pEventHandler );
	void fire( unsigned int uEventId, void* pEventParam1, void* pEventParam2 );
    // arg4
	bool bind( unsigned int uEventId, arg4event_handler_type* pEventHandler );
	void unbind( unsigned int uEventId, const arg4event_handler_type* pEventHandler );
	void fire( unsigned int uEventId, void* pEventParam1, void* pEventParam2, void* pEventParam3, void* pEventParam4 );	
private:
	void _init();
	void _unInit();
	void _deleteAllEventObj();
	//
	arg0event_obj_type* _findArg0EventObj( unsigned int uEventId ) const;
	arg0event_obj_type* _createArg0EventObj( unsigned int uEventId );
	void _deleteAllArg0EventObj();
	//
	arg2event_obj_type* _findArg2EventObj( unsigned int uEventId ) const;
	arg2event_obj_type* _createArg2EventObj( unsigned int uEventId );
	void _deleteAllArg2EventObj();
	//
	arg4event_obj_type* _findArg4EventObj( unsigned int uEventId ) const;
	arg4event_obj_type* _createArg4EventObj( unsigned int uEventId );
	void _deleteAllArg4EventObj();

private:
	HMTSHelper* m_pTSObj;
	arg0evtid2obj_map_type* m_pMapArg0EvtId2Obj;
	arg2evtid2obj_map_type* m_pMapArg2EvtId2Obj;
	arg4evtid2obj_map_type* m_pMapArg4EvtId2Obj;
};

#endif // !__CREVENTDEPOT_H__
