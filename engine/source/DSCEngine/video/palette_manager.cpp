#include "palette_manager.h"

#include "DSCEngine/debug/assert.hpp"

DSC::PaletteManager::PaletteManager(void* palettes_offset, int palettes_count)
{
	nds_assert(1<=palettes_count && palettes_count<=8);
	pal_offset = palettes_offset;
	pal_size = palettes_count<<8;		
}