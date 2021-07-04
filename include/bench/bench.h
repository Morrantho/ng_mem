#ifndef __NG_BENCH_H__
#define __NG_BENCH_H__
/* Includes */
#include"../dependencies.h"
#include"../typedefs.h"
#include<time.h>
#include<stdarg.h>
/* Lib */
/* These all return time taken in nanoseconds. */
/* Bench tests a single function. */
long ng_bench_test(register pfn fn);
/* Bench tests a single functions N times. */
void ng_bench_test_n(register int tests,register pfn fn);
/* Bench tests N functions in the order passed. */
void ng_bench_test_list(int fns,...);
#endif//__NG_BENCH_H__