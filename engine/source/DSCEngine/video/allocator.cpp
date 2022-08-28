#include "DSCEngine/video/allocator.hpp"
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
		this->prev = (alloc_info*)prev;
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
	: base_offset(offset), base_length(length)
{
	alloc_info::at(base_offset)->write(length, nullptr);
	id = 0; // <---
}

int address_stamp(int allocator_id, int base, int offset)
{
	return ((offset-base)<<8)|allocator_id;
}

void* DSC::Allocator::reserve(int size, int desired_offset)
{
	if(size==0) return nullptr;
	
	size = (size+31)/32; // round size to its upper nearest multiple of 32
	
	if(desired_offset>=0)
	{				
		for(auto* alc = alloc_info::at(base_offset); alc; alc = alc->next)
		{
			int del = desired_offset - (int)alc;
			if(del >= 0 && del+size <= alc->length)
			{
				void* result = alc->cut(del, size);
				
				int stamp = address_stamp(id, base_offset, (int)result);
				
				add_to_allocs_table(stamp);
				
				return result;
			}
		}		
		return nullptr;
	}
	else
	{
		for(auto* alc = alloc_info::at(base_offset); alc; alc = alc->next)
		{
			if(size <= alc->length)
			{
				void* result = alc->cut(0,size);
				
				int stamp = address_stamp(id, base_offset, (int)result);
				
				remove_from_allocs_table(stamp);
				
				return result;
			}
		}
		return nullptr;
	}		
}
		
void DSC::Allocator::release(void* address)
{
	if(address==nullptr) return;
}



