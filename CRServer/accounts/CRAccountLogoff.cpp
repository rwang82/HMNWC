#include "stdafx.h"
#include "CRAccountLogoff.h"

CRAccountLogoff::CRAccountLogoff()
: CRAccountBase( _T(""), _T(""), _T(""), _T("") ){

}

CRAccountLogoff::~CRAccountLogoff() {

}

int CRAccountLogoff::getSortType() {
    return 3;
}




