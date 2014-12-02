#include "stdafx.h"
#include "CRAccountBase.h"

CRAccountBase::CRAccountBase( const tstring_type& tstrAccountName, 
		const tstring_type& tstrPassword, 
		const tstring_type& tstrPhoneNum, 
		const tstring_type& tstrEMail )
: m_tstrAccountName( tstrAccountName )
, m_tstrPassword( tstrPassword )
, m_tstrPhoneNum( tstrPhoneNum )
, m_tstrEMail( tstrEMail ){

}

