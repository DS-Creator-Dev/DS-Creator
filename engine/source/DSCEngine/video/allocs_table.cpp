#include "allocs_table.h"

void init_allocs_table()
{
	for(int i=0;i<allocs_count-1;i++)
	{
		allocs_table[i] = i+1;
	}
	allocs_table[allocs_count-1] = -1;
}

void add_to_allocs_table(int stamp)
{
	
}

void remove_from_allocs_table(int stamp)
{
	
}