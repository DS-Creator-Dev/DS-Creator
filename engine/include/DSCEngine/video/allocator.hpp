#pragma once

namespace DSC
{
	class Allocator
	{
	private:
		unsigned char id;
		int base_offset;
		int base_length;		
	public:
		Allocator(int offset, int length);		
		
		void* reserve(int size, int desired_offset = -1);
		
		void release(void* address);		
	};
}