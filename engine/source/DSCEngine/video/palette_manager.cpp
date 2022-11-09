#include "palette_manager.h"

#include "DSCEngine/debug/assert.hpp"

using namespace DSC;

namespace
{
	void validate_palette_manager_constructor_input(int palettes_offset, int palettes_count)
	{		
		nds_assert(1<=palettes_count && palettes_count<=8);
		
		__assert__(palettes_offset%512 == 0, "Bad palette offset alignment");
		
		if(0x05000000<=palettes_offset && palettes_offset<=0x05000600)
		{
			__assert__(palettes_count == 1, "Standard palettes must be managed separately");
		}
		else
		{
			__assert__((0x06880000<=palettes_offset && palettes_offset<=0x06887FFF) 		
					|| (0x06890000<=palettes_offset && palettes_offset<=0x06891FFF)
					|| (0x06898000<=palettes_offset && palettes_offset<=0x068A3FFF),
				"Invalid palette offset");
		}
			
	}
}

DSC::PaletteManager::PaletteManager(void* palettes_offset, int palettes_count)
{		
	validate_palette_manager_constructor_input((int)palettes_offset, palettes_count);
	
	pal_offset = palettes_offset;
	pal_size = palettes_count<<8;

	free_space = new int[32*palettes_count];
	nds_assert(free_space != nullptr);
}


DSC::PaletteManager::~PaletteManager()
{
	delete free_space;
}

int DSC::PaletteManager::hashColor(const short& color)
{
	int r = color & 0x1F;
	int g = (color>>5) & 0x1F;
	int b = (color>>10);
	return (r+g+b)&127;
}