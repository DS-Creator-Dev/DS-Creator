#include "DSCEngine/scenes/generic_scene_256.hpp"

#include "DSCEngine/video/measure.hpp"
#include "DSCEngine/video/palette_manager.hpp"
#include "DSCEngine/video/vram_loader.hpp"

#include "DSCEngine/debug/assert.hpp"
#include "DSCEngine/debug/error.hpp"

using namespace DSC;

namespace
{
	struct BackgroundRequirement
	{
		bool enabled = false;
		bool is_bitmap;
		int color_depth;		
		int width;
		int height;
		int data_length;
		const AssetData* src_asset = nullptr;
	};
}

struct DSC::GenericScene256::__privates__
{
	BackgroundRequirement bg_requirements[8];
	
	PaletteManager main_palette = PaletteManager(BG_PALETTE);
};

DSC::GenericScene256::GenericScene256()
{
	privates = new __privates__();
}

void DSC::GenericScene256::init()
{
	set_banks();
}

__attribute__((noinline))
void DSC::GenericScene256::run()
{
	solve_map_requirements();
	load_assets();
	Scene::run();	
}

void DSC::GenericScene256::solve_map_requirements_main()
{
	int izone = 0;
	int imap_base = 0;
	
	int* tile_base = new int[4];
	int* map_base = new int[4];	
	
	int bmp_cnt = 0;
	
	// solve main
	for(int i=0;i<4;i++)
	{
		BackgroundRequirement& req = privates->bg_requirements[i];		
		
		if(!req.enabled) continue;
		
		if(imap_base>=32)
		{
			fatal("Map base exceeded for main BG%i",i);
		}		
		
		map_base[i] = imap_base;
		
		if(!req.is_bitmap) // is it tilemap? then, update the map base index
		{
			// get the number of 2KB blocks that would fit the map data for this bg			
			int map_blocks = Measure()
				.map_size(req.width, req.height) 
				.fit()
				.blocks(2)
				.kilobytes();
				
			imap_base+=map_blocks; // suppose we have already allocated this bg
		}					
		else
		{
			nds_assert(i>=2, "Backgrounds 0,1 cannot be bitmaps");			
			bmp_cnt++;
		}
		
		// get the number of zones required for the background data (tileset/bitmap)
		int gfx_blocks = MeasureValue(req.data_length)		
			.fit()
			.blocks(16)
			.kilobytes();
			
		tile_base[i] = izone;
		izone+=gfx_blocks;		
	}	
	
	// get the "offset" zone - the tile base right after all the map data (1 zone == 8 map blocks)
	int ozone = MeasureValue(imap_base).fit().blocks(8).value();
	if(ozone + izone > 16) // exceeded 256KB limit?
	{
		fatal("Main backgrounds data does not fit in allocated VRAM");
	}
			
	for(int i=0;i<4;i++) tile_base[i] += ozone;
	
	if(bmp_cnt==2)
	{
		videoSetMode(MODE_5_2D);
	}
	else if(bmp_cnt==1)
	{
		if(privates->bg_requirements[2].is_bitmap)
			videoSetMode(MODE_5_2D);
		else
			videoSetMode(MODE_3_2D);
	}	
	else videoSetMode(MODE_0_2D);
	
	// init backgrounds	
	for(int i=0;i<4;i++)
	{
		BackgroundRequirement& req = privates->bg_requirements[i];
		if(req.enabled)
		{
			int config = validate_bg_size(req.width, req.height, req.color_depth, req.is_bitmap);
			BgType bg_type = (BgType)((config>>16)&0xFFFF);
			BgSize bg_size = (BgSize)(config & 0xFFFF);
			bgInit(i, bg_type, bg_size, tile_base[i], map_base[i]);	
		}
	}		
}

void DSC::GenericScene256::solve_map_requirements_sub()
{
	// same as above but I'm too tired to do it
}

void DSC::GenericScene256::load_assets()
{
	for(int i=0;i<8;i++)
	{
		BackgroundRequirement& req = privates->bg_requirements[i];
		if(req.enabled && req.src_asset!=nullptr)
		{
			PaletteAllocationResult palloc = privates->main_palette.try_load(req.src_asset);
			if(!palloc.succeeded)
			{
				fatal("Palette allocation failed");
			}
			VramLoader::load(req.src_asset, bgGetGfxPtr(i), palloc.indices);
		}
	}
}

void DSC::GenericScene256::solve_map_requirements()
{	
	solve_map_requirements_main();
	solve_map_requirements_sub();
}


void DSC::GenericScene256::require_tiledmap_4bpp(int id, int px_width, int px_height, int number_of_tiles)
{
	nds_assert(0<=id && id<8);
	privates->bg_requirements[id] = 
	{
		enabled      : true,
		is_bitmap    : false,
		color_depth  : 4,
		width        : px_width,
		height       : px_height,
		data_length  : Measure()._4bpp().tiles(number_of_tiles),
		src_asset    : nullptr
	};
}

void DSC::GenericScene256::require_tiledmap_8bpp(int id, int px_width, int px_height, int number_of_tiles)
{
	nds_assert(0<=id && id<8);
	privates->bg_requirements[id] = 
	{
		enabled      : true,
		is_bitmap    : false,
		color_depth  : 8,
		width        : px_width,
		height       : px_height,
		data_length  : Measure()._8bpp().tiles(number_of_tiles),
		src_asset    : nullptr
	};
}

void DSC::GenericScene256::require_tiledmap(int id, int px_width, int px_height, const AssetData* tileset)
{
	nds_assert(tileset!=nullptr);	
	nds_assert(!tileset->is_bitmap());
	
	int color_depth = tileset->get_color_depth();
	nds_assert(color_depth == 4 || color_depth == 8);
	
	privates->bg_requirements[id] = 
	{
		enabled      : true,
		is_bitmap    : false,
		color_depth  : color_depth,
		width        : px_width,
		height       : px_height,
		data_length  : Measure()._8bpp().bitmap(px_width, px_height),
		src_asset    : tileset
	};	
}

void DSC::GenericScene256::require_bitmap(int id, int px_width, int px_height)
{
	nds_assert(0<=id && id<8);
	privates->bg_requirements[id] = 
	{
		enabled      : true,
		is_bitmap    : true,
		color_depth  : 8,
		width        : px_width,
		height       : px_height,
		data_length  : Measure()._8bpp().bitmap(px_width, px_height),
		src_asset    : nullptr
	};
}

void DSC::GenericScene256::require_bitmap(int id, const AssetData* bitmap)
{
	nds_assert(bitmap!=nullptr);	
	nds_assert(bitmap->is_bitmap());
	
	require_bitmap(id, 8*bitmap->width, 8*bitmap->height);
	privates->bg_requirements[id].src_asset = bitmap;
}

void DSC::GenericScene256::require_bitmap_16bpp(int id, int px_width, int px_height)
{
	nds_assert(0<=id && id<8);
	privates->bg_requirements[id] = 
	{
		enabled      : true,
		is_bitmap    : true,
		color_depth  : 16,
		width        : px_width,
		height       : px_height,
		data_length  : Measure()._16bpp().bitmap(px_width, px_height),
		src_asset    : nullptr
	};
}

void DSC::GenericScene256::require_bitmap_16bpp(int id, const AssetData* bitmap)
{
	nds_assert(bitmap!=nullptr);
	nds_assert(bitmap->is_bitmap());
	
	require_bitmap_16bpp(id, 8*bitmap->width, 8*bitmap->height);
	privates->bg_requirements[id].src_asset = bitmap;
}

DSC::GenericScene256::~GenericScene256()
{
	delete privates;
}

#include <nds.h>

int DSC::GenericScene256::validate_bg_size(int w, int h, int color_depth, bool is_bitmap)
{	
	nds_assert((w&(w-1))==0, "Map width must be a power of 2");
	nds_assert((h&(h-1))==0, "Map height must be a power of 2");
	
	nds_assert(128<=w && w<=1024);
	nds_assert(128<=h && h<=1024);
	
	int type;
	int size;
	bool ok  = false;
	
	// this looks terrible but I have no ideas how to make it cleaner
	// no (ex)rotation backgrounds yet!!!!!!!!!!!!!!!!
	if(is_bitmap)
	{				
		if(color_depth==8)
		{
			type = BgType_Bmp8;
			ok |= (w== 128 && h== 128); if(ok) { size = BgSize_B8_128x128;  goto __validate_bg_size__success; }
			ok |= (w== 256 && h== 256); if(ok) { size = BgSize_B8_256x256;  goto __validate_bg_size__success; }
			ok |= (w== 512 && h== 256); if(ok) { size = BgSize_B8_512x256;  goto __validate_bg_size__success; }
			ok |= (w== 512 && h== 512); if(ok) { size = BgSize_B8_512x512;  goto __validate_bg_size__success; }
			ok |= (w== 512 && h==1024); if(ok) { size = BgSize_B8_512x1024; goto __validate_bg_size__success; }
			ok |= (w==1024 && h== 512); if(ok) { size = BgSize_B8_1024x512; goto __validate_bg_size__success; }
		}
		else if(color_depth==16)
		{
			type = BgType_Bmp16;
			ok |= (w== 128 && h== 128); if(ok) { size = BgSize_B16_128x128; goto __validate_bg_size__success; }
			ok |= (w== 256 && h== 256); if(ok) { size = BgSize_B16_256x256; goto __validate_bg_size__success; }
			ok |= (w== 512 && h== 256); if(ok) { size = BgSize_B16_512x256; goto __validate_bg_size__success; }
			ok |= (w== 512 && h== 512); if(ok) { size = BgSize_B16_512x512; goto __validate_bg_size__success; }
		}
	}
	else
	{
		if(color_depth!=16)
		{
			type = color_depth==4 ? BgType_Text4bpp : BgType_Text8bpp;
			ok |= (w== 256 && h== 256); if(ok) { size = BgSize_T_256x256;  goto __validate_bg_size__success; }
			ok |= (w== 256 && h== 512); if(ok) { size = BgSize_T_256x512;  goto __validate_bg_size__success; }
			ok |= (w== 512 && h== 256); if(ok) { size = BgSize_T_512x256;  goto __validate_bg_size__success; }
			ok |= (w== 512 && h== 512); if(ok) { size = BgSize_T_512x512;  goto __validate_bg_size__success; }
		}
	}	
	
	fatal("Invalid map size (%i,%i) for %i-bpp %s", w, h, color_depth, is_bitmap ? "bitmap" : "tiled map");	
	
	return -1;
	
	__validate_bg_size__success:
	return size | (type<<16);
	
}

void DSC::GenericScene256::set_banks()
{
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_B_MAIN_BG_0x06020000);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	vramSetBankE(VRAM_E_MAIN_SPRITE);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
	vramSetBankG(VRAM_G_BG_EXT_PALETTE_SLOT23);
	vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
	vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
}

 const int DSC::GenericScene256::MAIN_BG0 = 0;
 const int DSC::GenericScene256::MAIN_BG1 = 1;
 const int DSC::GenericScene256::MAIN_BG2 = 2;
 const int DSC::GenericScene256::MAIN_BG3 = 3;

 const int DSC::GenericScene256::SUB_BG0 = 4;
 const int DSC::GenericScene256::SUB_BG1 = 5;
 const int DSC::GenericScene256::SUB_BG2 = 6;
 const int DSC::GenericScene256::SUB_BG3 = 7;