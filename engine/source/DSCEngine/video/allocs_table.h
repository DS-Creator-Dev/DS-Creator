#pragma once

extern const int allocs_count;
extern __attribute__((section(".iwram.alloc_buffer"))) int allocs_table[];


void init_allocs_table();

bool push_to_allocs_table(void* address);

void add_to_allocs_table(int stamp);

void remove_from_allocs_table(int stamp);

