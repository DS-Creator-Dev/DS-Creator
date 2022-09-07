#include "DSCEngine/video/allocator.hpp"
#include "DSCEngine/debug/log.hpp"

#include "allocs.h"
#include "allocs_table.h"

using namespace DSC;

struct alloc_info
{	
	int length;	
	alloc_info* prev;
	alloc_info* next;	
	
	int offset() { return (int)this;}
	
	void write(int length, void* next)
	{		
		this->length = length;		
		this->next = (alloc_info*)next;
	}
	
	void* cut(int rel_offset, int len)
	{
		if(rel_offset==0) 
		{
			auto* alc = at( offset() + len );
			alc->length = this->length - len;
			alc->prev = this->prev;
			alc->next = this->next;
		}
		else if(rel_offset+len==this->length)
		{
			this->length -= len;
		}
		else
		{
			auto* alc = at(offset()+rel_offset+len);			
			
			alc->length = this->length - rel_offset - len;
			alc->prev = this;
			alc->next = this->next;
			
			this->length = rel_offset;									
			this->next = alc;								
		}
				
		return reinterpret_cast<void*>(((int)this)+rel_offset);
	}
	
	static alloc_info* at(int offset)
	{
		return (alloc_info*)offset;
	}
};


DSC::Allocator::Allocator(int offset, int length)
	: base_offset(offset), base_length(length), free_space_head(offset)
{
	if(!allocs_table_inited)
	{
		init_allocs_table();
	}
	alloc_info::at(base_offset)->write(length, nullptr);
	int gen_id = create_alloc_id();
	if(gen_id == 0)
	{
		Debug::error("Allocators limit exceeded");		
	}	
	id = gen_id;
}

int address_stamp(int base, int offset, int length)
{	
	return (((offset-base)>>5)<<16)|(length>>5);
}

void* DSC::Allocator::reserve(int size, int desired_offset)
{
	if(size==0) return nullptr;
	
	size = ((size+31)/32)*32; // round size to its upper nearest multiple of 32
	
	if(desired_offset>=0)
	{				
		for(auto* alc = alloc_info::at(free_space_head); alc; alc = alc->next)
		{
			int del = desired_offset - (int)alc;
			if(del >= 0 && del+size <= alc->length)
			{
				if(!add_to_allocs_table(this->id, 0))
					return nullptr;				
				
				int free_space_next_backup = (int)alloc_info::at(free_space_head)->next;
				
				if(desired_offset == free_space_head)
				{
					if(size<alc->length)
						free_space_next_backup = free_space_head + size;
				}
				
				void* result = alc->cut(del, size);
				
				if((int)result == free_space_head)
				{
					free_space_head = free_space_next_backup;
				}
				
				*allocs_last_stamp() = address_stamp(base_offset, (int)result, size);														
				
				return result;
			}
		}		
		return nullptr;
	}
	else
	{
		for(auto* alc = alloc_info::at(free_space_head); alc; alc = alc->next)
		{
			if(size <= alc->length)
			{
				if(!add_to_allocs_table(this->id, 0))
					return nullptr;
				
				int free_space_next_backup = (int)alloc_info::at(free_space_head)->next;
				if(size < alc->length)
				{
					free_space_next_backup = free_space_head + size;
				}					
				
				void* result = alc->cut(0,size);
				if((int)result == free_space_head)
				{
					free_space_head = free_space_next_backup;
				}
				
				*allocs_last_stamp() = address_stamp(base_offset, (int)result, size);						
				
				return result;
			}
		}
		return nullptr;
	}		
}
		
void DSC::Allocator::release(void* address)
{
	if(address==nullptr) return;
	int offset = (int)address;
	
	if((offset - base_offset)&31) return;
	
	if(offset<base_offset || offset>=base_offset+base_length)
		return;
	
	int size = remove_from_allocs_table(this->id, offset - base_offset);	
	
	if(size==0) 
	{				
		return;
	}
	
	alloc_info* freed = alloc_info::at(offset);
	freed->write(size, nullptr);
	
	if(offset < free_space_head)
	{
		auto* head = alloc_info::at(free_space_head);
		
		freed->next = head;
		if((int)freed + freed->length == (int)head)
		{
			freed->length += head->length;
			freed->next = head->next;			
		}
		
		free_space_head = offset;
		return;
	}
	
	for(auto* alc = alloc_info::at(free_space_head); alc; alc = alc->next)
	{
		if(((int)alc)<((int)freed))
		{
			if(!alc->next)
			{
				alc->next = freed;
				if((int)alc + alc->length == (int)freed) // adjacent segments
				{
					alc->length+=freed->length;
					alc->next = freed->next;
				}
				return;
			}
			else if((int)freed < (int)(alc->next))
			{
				freed->next = alc->next;
				
				if((int)freed + freed->length == (int)alc->next)
				{
					freed->length += alc->next->length;
					freed->next = alc->next->next;
				}				
				
				alc->next = freed;				
				if((int)(alc) + alc->length == (int)freed)
				{
					alc->length += freed->length;
					alc->next = freed->next;
				}
				return;
			}
		}
	}	
	
}

DSC::Allocator::~Allocator()
{
	remove_allocs_by_id(id);
}