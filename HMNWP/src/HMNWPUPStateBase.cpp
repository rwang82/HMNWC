#include "stdafx.h"
#include "HMNWPUPStateBase.h"
#include <assert.h>
HMNWP_NAMESPACE_BEGIN

void HMNWPUPStateBase::parseRawData( const unsigned char* pRawBuf, unsigned int uLenRawBuf, ENUMRAWBUFTYPE eRawBufType, unsigned int& uLenEat ) {
	switch ( eRawBufType )
	{
	case hmnwp::ERAWBUF_TYPE_UNKNOWN:
	{
		assert( false );
		uLenEat = uLenRawBuf;
		return;
	}
		break;
	case hmnwp::ERAWBUF_TYPE_NOTIN:
	{
		uLenEat = uLenRawBuf;
		return;
	}
		break;
	case hmnwp::ERAWBUF_TYPE_BODYIN_ONLY:
	{
		_parseRawData_BODYIN_ONLY( pRawBuf, uLenRawBuf, uLenEat );
		return;
	}
		break;
	case hmnwp::ERAWBUF_TYPE_TAILIN_ONLY:
	{
		_parseRawData_TAILIN_ONLY( pRawBuf, uLenRawBuf, uLenEat );
		return;
	}
		break;
	case hmnwp::ERAWBUF_TYPE_ALLIN:
	{
		_parseRawData_ALLIN( pRawBuf, uLenRawBuf, uLenEat );
		return;
	}
		break;
	case hmnwp::ERAWBUF_TYPE_HEADIN_ONLY:
	{
		_parseRawData_HEADIN_ONLY( pRawBuf, uLenRawBuf, uLenEat );
		return;
	}
		break;
	default:
		assert( false );
		break;
	}

}

void HMNWPUPStateBase::_parseRawData_BODYIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat ) {
	assert( false );
	uLenEat = uLenRawBuf;
}

void HMNWPUPStateBase::_parseRawData_TAILIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat ) {
	assert( false );
	uLenEat = uLenRawBuf;
}

void HMNWPUPStateBase::_parseRawData_ALLIN( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat ) {
	assert( false );
	uLenEat = uLenRawBuf;
}

void HMNWPUPStateBase::_parseRawData_HEADIN_ONLY( const unsigned char* pRawBuf, unsigned int uLenRawBuf, unsigned int& uLenEat ) {
	assert( false );
	uLenEat = uLenRawBuf;
}


HMNWP_NAMESPACE_END


