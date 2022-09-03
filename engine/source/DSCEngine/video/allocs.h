#pragma once

inline short __attribute__((section(".iwram.alloc_ids"))) alloc_ids[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

inline int create_alloc_id()
{
	for(int i=0;i<16;i++)
	{
		if(alloc_ids[i]==0xFFFF) continue;
		int j=0;
		for(;alloc_ids[i] & (1<<j); j++);
		
		alloc_ids[i] |= (1<<j);
		return (i<<4)|j;
	}
	return -1;
}

inline void release_alloc_id(int id)
{
	int i = id>>4;
	int j = id & 0xF;		
	alloc_ids[i] &= ~(1<<j);
}

