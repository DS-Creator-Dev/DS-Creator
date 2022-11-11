#include <nds.h>
#include <stdio.h>
#include <DSC>

#include "roa_dsclogo8.h"



using namespace DSC;

class Scene1 : public Scene
{
private:
	// this holds information about a 32x32@8bpp tiled image
	const AssetData* asset = &ROA_DSCLogo8;
public:

	
	void init() override
	{		
		consoleDemoInit();		
		
		iprintf("\n DSC Test Asset Data \n\n");		
					
		printf(" Asset         = ROA_DSCLogo8\n");
		printf(" Header size   = %i\n", asset->header_size);
		printf(" Stored in     = %s\n", asset->is_file() ? "FILE" : "WRAM");
		printf(" Type          = %s\n", type_to_str(asset->get_type()));
		printf(" \n");
		printf(" Width         = %i\n", asset->width*8);
		printf(" Height        = %i\n", asset->height*8);
		printf(" Type          = %s\n", asset->is_bitmap()?"BITMAP":"TILES");
		printf(" Color depth   = %ibpp\n", asset->get_color_depth());
		printf(" \n");
		printf(" Resource size = %i\n", asset->data_length);
		printf(" Graphics size = %i\n", asset->get_gfx_length());
		printf(" Palette  size = %i\n", asset->get_pal_length());
		
		printf(" \n");
		printf(" \n");
		printf(" \n");
		printf(" TO DO : Image to be displayed\n on top screen...");
		// asset->extract(...)		
	}	
	
	const char* type_to_str(int type)
	{
		switch(type)
		{
			case 0 : return "UNKNOWN";
			case 1 : return "ASSET";
			case 2 : return "FONT";
			default : return "???";
		}
	}
};

dsc_launch(Scene1);
