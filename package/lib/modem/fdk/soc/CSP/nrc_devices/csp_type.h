#ifndef __TYPE_H__
#define __TYPE_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL		(void *)0
#else
#define NULL		0
#endif
#endif

#ifndef int8_t
#define int8_t				int8_t
#endif

#ifndef uint8_t
#define uint8_t				uint8_t
#endif

#ifndef int16_t
#define int16_t				int16_t
#endif

#ifndef uint16_t
#define uint16_t			uint16_t
#endif

#ifndef int32_t
#define int32_t				int32_t
#endif

#ifndef uint32_t
#define uint32_t			uint32_t
#endif

#ifndef int64_t
#define int64_t				int64_t
#endif

#ifndef uint64_t
#define uint64_t			uint64_t
#endif

#ifndef ENABLE_
#define ENABLE_				1
#endif

#ifndef DISABLE_
#define DISABLE_ 			0
#endif

#ifndef SET_
#define SET_ 				1
#endif

#ifndef RESET_
#define RESET_				0
#endif




#ifdef __cplusplus
}
#endif

#endif

