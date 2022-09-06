#include "DSCEngine/resources/readonly_data.hpp"

#include <nds.h>


DSC::ReadOnlyData::ReadOnlyData(int header_size) : header_size(header_size) { }

void DSC::ReadOnlyData::extract(void* destination)
{
	if(!is_file)
	{		
		// perform 16-bit r/w
		short* src = reinterpret_cast<short*>(data_source);
		if(src == nullptr)
		{
			src = (short*)(((int)this)+header_size);
		}		
		
		short* dst = reinterpret_cast<short*>(destination);
		for(int i=0;i<data_length/2;i++)
			dst[i] = src[i]; // maybe __asm this line if gcc optimizes it to memset (<=> byte-to-byte copy)
	}
	else
	{
		char* filename = data_source;
		
		// discussion FAT/NITRO...
	}
}