#ifndef __CRSRVMISC_H__
#define __CRSRVMISC_H__
//
struct CRRMsgMetaData;
//
void gfnSendFailedAck( const CRRMsgMetaData& rmsgMetaData, int nRMsgAckType, int nCmdSN, int nErrCode );



#endif //__CRSRVMISC_H__