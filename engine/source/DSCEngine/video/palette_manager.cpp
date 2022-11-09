#include "palette_manager.h"

#include "DSCEngine/debug/assert.hpp"

using namespace DSC;

namespace
{
	void validate_palette_manager_constructor_input(int palettes_offset)
	{						
		__assert__(palettes_offset%512 == 0, "Bad palette offset alignment");
		
		__assert__((0x05000000<=palettes_offset && palettes_offset<=0x05000600)
				|| (0x06880000<=palettes_offset && palettes_offset<=0x06887FFF) 		
				|| (0x06890000<=palettes_offset && palettes_offset<=0x06891FFF)
				|| (0x06898000<=palettes_offset && palettes_offset<=0x068A3FFF),
			"Invalid palette offset");					
	}
}

DSC::PaletteManager::PaletteManager(void* palettes_offset)
{		
	validate_palette_manager_constructor_input((int)palettes_offset);
	
	pal_offset = palettes_offset;	
	
	// mark index 0 (transparent color) as used 
	// in order to avoid writes to these locations
	free_space[0] = 0b1;	
}

namespace
{
	/*! \brief gets the position of the first unset bit in a number */
	int free_bit_pos(int n, int k = 32)
	{		
		if(n==0xFFFFFFFF) return -1; // full : all bits are set
		if(k==0) return 0;		
		
		k/=2;
		int _0f = (1<<(k-1))-1 + (1<<(k-1)); // build bit-1 masks for the LOW 
		int _f0 = _0f << (k/2);				 // and HIGH parts
		
		if((n & _0f)==_0f)                   // if the LOW part is full
			return k+free_bit_pos(n>>k, k);  // look in the HIGH part
		else 
			return free_bit_pos(n & _0f, k); // otherwise check the LOW part
	}

int DSC::PaletteManager::reserve1(int color)
{
	// if color already exists, increase the color count
	if(colors_map.contains_key(color))
	{
		colors_map[color]++;
		return;
	}		
	
	// if color does not exist, find a free palette index for it
	int p = -1;
	for(int i=0;i<8;i++)	
	{
		p = free_bit_pos(free_space[i]);
		if(p==-1) continue;
		
		p += 32*i;
		break;
	}
	
	// register color to color map
	colors_map[color] = (p<<16) | 1;
	
	return p;
}

void DSC::PaletteManager::unload1(int color)
{
	// if color does not exist, do nothing
	if(!colors_map.contains_key(color))
	{		
		return;
	}
	
	int value = colors_map[color];		
	value--;
	
	// if color isn't in use anymore, remove it
	if((value & 0x0000FFFF)==0)
	{
		colors_map.remove_key(color);
	}			
}

DSC::PaletteManager::~PaletteManager()
{	
}

int DSC::PaletteManager::hashColor(const short& color)
{
	int r = color & 0x1F;
	int g = (color>>5) & 0x1F;
	int b = (color>>10);
	return (r+g+b)&127;
}