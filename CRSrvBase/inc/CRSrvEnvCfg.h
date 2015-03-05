#ifndef __CRSRVENVCFG_H__
#define __CRSRVENVCFG_H__

//
#define CRSRV_NAMESPACE_BEGIN namespace crsrv {
#define CRSRV_NAMESPACE_END };
#define USING_NAMESPACE_CRSRV using namespace crsrv;
//
#ifdef CRSRV_EXPORTS
#define CRSRV_API __declspec(dllexport)
#else
#define CRSRV_API __declspec(dllimport)
#endif //CRSRV_EXPORTS



#endif //__CRSRVENVCFG_H__