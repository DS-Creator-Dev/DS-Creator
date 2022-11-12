#include "DSCEngine/scenes/generic_scene_256.hpp"
#include "DSCEngine/debug/assert.hpp"
#include "DSCEngine/video/measure.hpp"

using namespace DSC;

namespace
{
	struct BackgroundRequirement
	{
		bool is_bitmap;
		int color_depth;		
		int width;
		int height;
		int data_length;
		AssetData* src_asset = nullptr;
	};
}

struct DSC::GenericScene256::__privates__
{
	BackgroundRequirement bg_requirements[8];	
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
	Scene::run();	
}

void DSC::GenericScene256::solve_map_requirements()
{
	// ...
}


void DSC::GenericScene256::require_tiledmap_4bpp(int id, int px_width, int px_height, int number_of_tiles)
{
	nds_assert(0<=id && id<8);
	privates->bg_requirements[id] = 
	{
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
		is_bitmap    : false,
		color_depth  : 8,
		width        : px_width,
		height       : px_height,
		data_length  : Measure()._8bpp().tiles(number_of_tiles),
		src_asset    : nullptr
	};
}

void DSC::GenericScene256::require_tiledmap(int id, int px_width, int px_height, AssetData* tileset)
{
	nds_assert(tileset!=nullptr);	
	nds_assert(!tileset->is_bitmap());
	
	int color_depth = tileset->get_color_depth();
	nds_assert(color_depth == 4 || color_depth == 8);
	
	privates->bg_requirements[id] = 
	{
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
		is_bitmap    : true,
		color_depth  : 8,
		width        : px_width,
		height       : px_height,
		data_length  : Measure()._8bpp().bitmap(px_width, px_height),
		src_asset    : nullptr
	};
}

void DSC::GenericScene256::require_bitmap(int id, DSC::AssetData* bitmap)
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
		is_bitmap    : true,
		color_depth  : 16,
		width        : px_width,
		height       : px_height,
		data_length  : Measure()._16bpp().bitmap(px_width, px_height),
		src_asset    : nullptr
	};
}

void DSC::GenericScene256::require_bitmap_16bpp(int id, DSC::AssetData* bitmap)
{
	nds_assert(bitmap!=nullptr);
	nds_assert(bitmap->is_bitmap());
	
	require_bitmap_16bpp(id, 8*bitmap->width, 8*bitmap->height);
	privates->bg_requirements[id].src_asset = bitmap;
}

#include <nds.h>

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

 const int MAIN_BG0 = 0;
 const int MAIN_BG1 = 1;
 const int MAIN_BG2 = 2;
 const int MAIN_BG3 = 3;

 const int SUB_BG0 = 4;
 const int SUB_BG1 = 5;
 const int SUB_BG2 = 6;
 const int SUB_BG3 = 7;