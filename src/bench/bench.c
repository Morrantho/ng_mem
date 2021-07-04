#include"../../include/bench/bench.h"

long ng_bench_test(register pfn fn)
{
	struct timespec t1,t2;
	clock_gettime(CLOCK_MONOTONIC,&t1);
	fn();
	clock_gettime(CLOCK_MONOTONIC,&t2);
	return t2.tv_nsec-t1.tv_nsec;
}

void ng_bench_test_n(register int tests,register pfn fn)
{
	register long avg=0;
	register long sum=0;
	register long t=0;
	for(register int i=0;i<tests;i++)
	{
		t=ng_bench_test(fn);
		printf("Test: %i %luns\n",i,t);
		sum+=t;
	}
	avg=sum/tests;
	printf("Test Average: %luns\n",avg);
}

void ng_bench_test_list(int fns,...)
{
	register long avg=0;
	register long sum=0;
	register long t=0;
	va_list args;
	va_start(args,fns);
	for(int i=0;i<fns;i++)
	{
		pfn fn=va_arg(args,pfn);
		t=ng_bench_test(fn);
		printf("Test: %i %luns\n",i,t);
		sum+=t;
	}
	va_end(args);
	avg=sum/fns;
	printf("Test Average: %luns\n",avg);
}