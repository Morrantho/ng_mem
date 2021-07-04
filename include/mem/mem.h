#ifndef __NG_MEM_H__
#define __NG_MEM_H__
/* Includes */
#include"../dependencies.h"
#include"../typedefs.h"
/* Pre */
#define NG_TO_KB(N,F) N*F
#define NG_TO_MB(N,F) F*NG_TO_KB(N,F)
#define NG_TO_GB(N,F) F*NG_TO_MB(N,F)
#define NG_KB NG_TO_KB(1,1024)
#define NG_MB NG_TO_MB(1,1024)
#define NG_GB NG_TO_GB(1,1024)
/* Pointer sizes */
#ifdef __x86_64__
	#define NG_PSZ 8/* 4/8 pointer size */
	#define NG_PRSH 3/* 3/2 right shift */
	#define NG_INT u64/* 32/64 unsigned int/long long */
	#define NG_PINT pu64/* 32/64 pointer-to-int */
#else
	#define NG_PSZ 4/* 4/8 pointer size */
	#define NG_PRSH 2/* 3/2 right shift */
	#define NG_INT u32/* 32/64 unsigned int/long long */
	#define NG_PINT pu32/* 32/64 pointer-to-int */
#endif
/* Set a default if they didn't give us one before including */
#ifndef NG_MEM_SIZE
#define NG_MEM_SIZE NG_MB*16
#endif
/* Vars */
extern NG_INT ng_mem_ptr;
extern NG_INT ng_mem[NG_MEM_SIZE];
/* Lib */
void ng_mem_fill(register pvoid block,register NG_INT bytes,register u8 data);
static inline NG_INT ng_mem_probe(register NG_INT bytes);
pvoid ng_mem_alloc(register NG_INT bytes);
pvoid ng_mem_calloc(register NG_INT bytes);
void ng_mem_free(register pvoid block);
#endif//__NG_MEM_H__