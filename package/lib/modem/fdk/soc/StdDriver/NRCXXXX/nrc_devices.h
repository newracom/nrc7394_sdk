#ifndef __NRC_DEVICES_H__
#define __NRC_DEVICES_H__

#ifdef __cplusplus
extern "C"{
#endif




#if defined (NRC7394)
#include "nrc7394.h"

#elif defined(NRC5292)
#include "nrc5292.h"

#elif defined(NRC5293)
#include "nrc5293.h"

#else
#error Not supported Model
#endif





#ifdef __cplusplus
}
#endif

#endif

