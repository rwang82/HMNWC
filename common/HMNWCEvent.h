//**********************************************************************
// Copyright (c) 2014
// 裕邦智能.
// 文件: HMFSEvent.h
// 内容: 
// 历史:
//	序号	修改时间		修改人		修改内容
//	1		2014-2-19		王宇锋		首次生成
//*********************************************************************
#ifndef __HMNWCEVENT_H__
#define __HMNWCEVENT_H__
#include "hmcmn_event.h"
#include "HMTSHelper.h"
#include "hm_cmn_envcfg.h"
//
HMCMN_NAMESPACE_START
	class hm_cmn_subject;
	class hm_cmn_observer_i;
HMCMN_NAMESPACE_END
//
class HMNWCEvent {
public:
    HMNWCEvent( unsigned int uEventId );
    ~HMNWCEvent();

public:
    void bind( hmcmn::hm_cmn_observer_i* pObserver );
	void unbind(hmcmn::hm_cmn_observer_i* pObserver);
    void fire( void* pEventParam1 = NULL, void* pEventParam2 = NULL );
    unsigned int getEventId() const { return m_uEventId; }

private:
	HMTSHelper m_tsObj;
	hmcmn::hm_event< hmcmn::hm_cmn_subject*, unsigned int, void*, void* > m_eventTrigger;
    unsigned int m_uEventId;
};

#endif //__HMNWCEVENT_H__