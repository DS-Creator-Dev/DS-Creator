#include "DSCEngine/video/vram_loader.hpp"

#include <nds.h>

using namespace DSC;

void DSC::VramLoader::load(const AssetData* asset, void* dest, short* pal_indices)
{
	if(pal_indices==nullptr || asset->get_color_depth()!=8)
	{
		asset->extract(dest, 0, asset->get_gfx_length());
		return;
	}
	int len = asset->get_gfx_length();
	unsigned char* buffer = new unsigned char[len];
	
	asset->extract(buffer, 0, len);
	
	for(int i=0;i<len;i++)
	{
		if(buffer[i])
			buffer[i] = pal_indices[buffer[i]];
	}		
	
	dmaCopy(buffer, dest, len);	// <-- beware for bugs idk	
		
	delete[] buffer;
}