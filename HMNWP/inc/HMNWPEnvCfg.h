#ifndef __HMNWPENVCFG_H__
#define __HMNWPENVCFG_H__
#include "winsock2.h"
//
#define HMNWP_NAMESPACE_BEGIN namespace hmnwp {
#define HMNWP_NAMESPACE_END };
#define USING_NAMESPACE_HMNWP using namespace hmnwp;
//
#ifdef HMNWP_EXPORTS
#define HMNWP_API __declspec(dllexport)
#else
#define HMNWP_API __declspec(dllimport)
#endif


#endif //__HMNWPENVCFG_H__
