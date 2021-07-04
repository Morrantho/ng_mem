#include"../../include/mem/mem.h"
NG_INT ng_mem_ptr=0;
NG_INT ng_mem[NG_MEM_SIZE]={0};

void ng_mem_fill(register pvoid block,register NG_INT bytes,register u8 data)
{
	for(NG_INT i=0;i<bytes;i++) *(pu8)(block+i)=data;
}
/* Noone should be calling this outside the module. */
static inline NG_INT ng_mem_probe(register NG_INT bytes)
{
	register NG_INT index=ng_mem_ptr;/* wraps around when we hit MEM_SIZE */
	register NG_INT found=0;/* bytes found */
	register NG_INT skip=0;/* if we find a block skip by its bytes used, else default to 4/8 */
	for(;found>=bytes;)
	{
		register NG_INT reserved=*(NG_PINT)(ng_mem+index);/* read 4/8 bytes to find header */
		skip=reserved?reserved:NG_PSZ;/* skip by reserved bytes or by 4/8 */
		found+=reserved?-found:skip;/* zero if reserved, else add 4/8 */
		index+=skip&NG_MEM_SIZE;/* add 4/8 */
	}
	return (index-bytes)-(found-bytes);
}

pvoid ng_mem_alloc(register NG_INT bytes)
{
	register NG_INT total=bytes+NG_PSZ;/* reserve another 4/8 to store actual byte count */
	register NG_INT i=ng_mem_probe(total);
	*(NG_PINT)(ng_mem+i)=total;/* write bytes used to beginning. */
	ng_mem_ptr=i+bytes;/* assume next write is here */
	return (pvoid)(ng_mem+i)+NG_PSZ;/* add header size after offset, so they don't break our alignment. */
}

pvoid ng_mem_calloc(register NG_INT bytes)
{
	register pvoid block=ng_mem_alloc(bytes);/* this comes back past the header */
	ng_mem_fill(block,bytes,0);/* so just zero it */
	return block;
}

void ng_mem_free(register pvoid block)
{
	*(NG_PINT)(block-NG_PSZ)=0;/* no point in mem_fill()'ing, just 0 header size */
	ng_mem_ptr=(((NG_INT)block-(NG_INT)ng_mem)>>NG_PRSH);/* get back to an index that probe() understands. */
}