/******************************************************************************
* This example just benchmarks against stdlib.
* If we can't beat it, then this is pointless.
* Run it on your own system and compare results.	
******************************************************************************/
#include"../include/bench/bench.h"
// #define NG_MEM_SIZE your_size
#include"../include/mem/mem.h"

pvoid test_mem=0;
NG_INT test_bytes=16*NG_MB;
int test_tests=10;

void test1()
{
	test_mem=malloc(test_bytes);
}

void test2()
{
	free(test_mem);
}

void test3()
{
	test_mem=ng_mem_alloc(test_bytes);
}

void test4()
{
	ng_mem_free(test_mem);
}

#define MEM_PTRS 1000000
#define MAX_BYTES 1024
pvoid mem_ptrs[MEM_PTRS]={0};
/******************************************************************************
* Bad function name pun. This function is designed to stress our module
* and provide a fair comparison against stdlib by filling it with
* a million allocations and deallocations of up to a KB in size.
******************************************************************************/
void ramdomize()
{
	srand(time(0));
	for(register int i=0;i<MEM_PTRS;i++)
	{
		register int decision=rand()%10>5?1:0;
		register int bytes=rand()%MAX_BYTES;
		register int index=rand()%MEM_PTRS;
		if(decision)
		{
			mem_ptrs[i]=ng_mem_alloc(bytes);
		}
		else
		{
			if(mem_ptrs[index]) ng_mem_free(mem_ptrs[index]);
		}
	}
}

int main(int argc,char** argv)
{
	ramdomize();
	printf("stdlib:\n");
	for(int i=0;i<test_tests;i++) ng_bench_test_list(2,test1,test2);
	printf("-------------------------------------------------\n");
	printf("our lib:\n");
	for(int i=0;i<test_tests;i++) ng_bench_test_list(2,test3,test4);
	return 0;
}