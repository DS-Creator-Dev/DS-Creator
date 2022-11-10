#include "DSCEngine/video/palette_manager.hpp"

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
	
	for(int i=0;i<8;i++) free_space[i]=0;
	for(int i=0;i<16;i++) records4bpp[i]=0;
	
	// mark index 0 (transparent color) as used 
	// in order to avoid writes to these locations
	free_space[0] = 0b1;	
}

namespace
{
	/*! \brief gets the position of the first unset bit in a number */
	int free_bit_pos(int n, int k = 32)
	{		
		if((unsigned)n==0xFFFFFFFF) return -1; // full : all bits are set
		if(k==0) return 0;		
		
		k/=2;
		int _0f = (1<<(k-1))-1 + (1<<(k-1)); // build bit-1 masks for the LOW 
		//int _f0 = _0f << (k/2);				 // and HIGH parts
		
		if((n & _0f)==_0f)                   // if the LOW part is full
			return k+free_bit_pos(n>>k, k);  // look in the HIGH part
		else 
			return free_bit_pos(n & _0f, k); // otherwise check the LOW part
	}
}

int DSC::PaletteManager::reserve1(int color)
{
	// if color already exists, increase the color count
	if(colors_map.contains_key(color))
	{
		colors_map[color]++;
		return colors_map[color]>>16;
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
	
	if(p==-1) return -1; // all slots full :((	
	
	// register color to color map & reserve the space for it
	colors_map[color] = (p<<16) | 1;			
	free_space[p/32] |= 1<<(p&31);
	
	// write color to position
	((short*)pal_offset)[p] = color;
	
	
	return p;
}

void DSC::PaletteManager::unload1(int color)
{
	// if color does not exist, do nothing
	if(!colors_map.contains_key(color))
	{		
		return;
	}
	
	int value = colors_map[color] - 1;	
	
	// if color isn't in use anymore, remove it
	if((value & 0x0000FFFF)==0)
	{
		colors_map.remove_key(color);
		int p = value>>16;
		free_space[p/32] &= ~(1<<(p&31)); 
		
		// reset color
		((short*)pal_offset)[p] = 0;
	}			
}

int DSC::PaletteManager::get_pal16(short* colors, int chksum)
{
	int p=-1;
	for(int i=0;i<16;i++)
	{
		if((records4bpp[i]>>8)==chksum)
		{
			// double check if this is the palette we are looking for			
			bool found = true;			
			short* pal = &((short*)pal_offset)[16*i];
			for(int j=1;j<16 && found;j++)
			{
				found = colors[j] == pal[j];
			}		
			
			if(found)
			{
				p=i; break;
			}			
		}
	}
	return p;
}

int DSC::PaletteManager::get_chksum(short* colors)
{
	int chksum = 0;		
	for(int i=1; i<16; chksum+=colors[i++]);	
	chksum = (chksum>>6)&0x7F; // random narrowing to byte
	if(chksum==0) chksum=1;
	return chksum;
}


int DSC::PaletteManager::reserve16(const void* palette4)
{
	short* colors = (short*)palette4;
	
	// compute palette checksum to identify it faster
	int chksum = get_chksum(colors);		
	
	// first check if the palette already exists
	int p = get_pal16(colors, chksum);
	
	if(p>=0) // palette exists
	{
		records4bpp[p]++;		
		return p;
	}
	
	short* free_space16 = (short*)free_space;
	
	for(int i=0;i<16;i++)
	{
		if(free_space16[i]==0 || free_space16[i]==1) // we can allow slot color 0 to be occupied
		{
			p = i;
			break;
		}
	}
	
	if(p<0) return -1;
	
	// register palette
	records4bpp[p] = (chksum<<8) | 1;
	free_space16[p] |= 0xFFFE;
	
	// finally, write palette to its location
	short* pal = &((short*)pal_offset)[16*p];
	for(int i=1;i<16;i++)	
		pal[i] = colors[i];	
		
	return p;	
}

void DSC::PaletteManager::unload16(const void* palette4)
{
	short* colors = (short*)palette4;
	
	// compute palette checksum to identify it faster
	int chksum = get_chksum(colors);	
	
	// first check if the palette already exists
	int p = get_pal16(colors, chksum);
	
	if(p==-1) return; // palette does not exist, do nothing
	
	records4bpp[p]--;
	
	if((records4bpp[p]&0xFF)==0) // palette no longer used
	{
		records4bpp[p] = 0;
		
		short* free_space16 = (short*)free_space;
		free_space16[p] &= ~0xFFFE;
		
		// reset palette
		short* pal = (short*)((int)pal_offset + 16*p*sizeof(short));			
		
		// https://gist.github.com/NotImplementedLife/91517a5fca90f53a7fd91c5b2e54c34d		
		const int zero=0;
		for(int i=1;i<16;i++)			
			// pal[i] = 0; <-- leaves uncleared artifacts at pal[1]
			__asm("STRH %[_0], [%[dest]]"				
				: : [dest] "r" (&pal[i]), [_0] "r" (zero));
		
		return;
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