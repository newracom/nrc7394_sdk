#ifndef __DRV_TYPE_H__
#define __DRV_TYPE_H__

//typedef unsigned char BOOL;
#include <stdint.h>


#if defined ( __GNUC__ )
#define __RAM_FUNC	__attribute__((section(".ramfunc")))
#elif defined (__ICCARM__)
#define __RAM_FUNC __ramfunc
#endif


#if 0
typedef unsigned __int8		INT8U;
typedef __int8 				INT8S;
typedef unsigned __int16 	INT16U;
typedef __int16 			INT16S;
typedef unsigned __int32 	INT32U;
typedef __int32 			INT32S;
typedef unsigned __int64 	INT64U;
typedef __int64 			INT64S;

typedef int				INT;
typedef unsigned int	UINT;
#endif

#if 1
#ifndef int8_t
#define int8_t			int8_t
#endif
#ifndef uint8_t
#define uint8_t			uint8_t
#endif

#ifndef int16_t
#define int16_t			int16_t
#endif
#ifndef uint16_t
#define uint16_t		uint16_t
#endif

#ifndef int32_t
#define int32_t			int32_t
#endif
#ifndef uint32_t
#define uint32_t		uint32_t
#endif

#ifndef int64_t
#define int64_t			int64_t
#endif
#ifndef uint64_t
#define uint64_t		uint64_t
#endif
#endif

#ifndef NULL
#ifndef __cplusplus
#define NULL ((void *)0)
#else   /* C++ */
#define NULL 0
#endif  /* C++ */
#endif


#ifndef ENABLE_
#define ENABLE_			1
#endif

#ifndef DISABLE_
#define DISABLE_		0
#endif

#ifndef SET_
#define SET_			1
#endif

#ifndef RESET_
#define RESET_			0
#endif

#ifndef TRUE_
#define TRUE_			1
#endif

#ifndef FALSE_
#define FALSE_			0
#endif


#ifndef OK_
#define OK_				0
#endif

#ifndef FAIL_
#define	FAIL_			1
#endif

#if defined(EXCLUDE_FDK_MAC) && !defined(UCODE)
#include <FreeRTOS.h>
#include <task.h>
#define malloc pvPortMalloc
#define free vPortFree
#define calloc pvPortCalloc
#define ATTR_NC		__attribute__((section(".sfc_code_nc")))
#ifdef __RAM_FUNC
#undef __RAM_FUNC
#endif
#define __RAM_FUNC ATTR_NC
#endif //defined(EXCLUDE_FDK_MAC)

#endif

