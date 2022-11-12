#pragma once

#include "DSCEngine/scenes/scene.hpp"
#include "DSCEngine/resources/asset_data.hpp"

namespace DSC
{
	/*! \brief general-purpose scene with 256KB BG-Main VRAM
		\details Size limits:
		- 256 KB for main backgrounds
		-  64 KB for main objects
		-   8    extended palettes for each main background
		-  16    extended palettes for main objects
		- 128 KB for sub backgrounds
		- 128 KB for sub objects
		-  16    extended palettes for each sub backgrounds
		-  16    extended palettes for sub objects
	 */
	class GenericScene256 : public Scene
	{
	private:
		struct __privates__;
		__privates__* privates;
		
		void set_banks();
		void solve_map_requirements();
	public:
		GenericScene256();
		virtual void init() override;
		virtual void frame() override;
		
		__attribute__((noinline))
		virtual void run() override;
		
		
		void require_tiledmap_4bpp(int id, int px_width, int px_height, int number_of_tiles);
		void require_tiledmap_8bpp(int id, int px_width, int px_height, int number_of_tiles);
		
		void require_tiledmap(int id, int px_width, int px_height, AssetData* tileset);
		
		void require_bitmap(int id, int px_width, int px_height);
		void require_bitmap(int id, DSC::AssetData* bitmap);
		
		void require_bitmap_16bpp(int id, int px_width, int px_height);
		void require_bitmap_16bpp(int id, DSC::AssetData* bitmap);
		
		static const int MAIN_BG0;
		static const int MAIN_BG1;
		static const int MAIN_BG2;
		static const int MAIN_BG3;
		
		static const int SUB_BG0;
		static const int SUB_BG1;
		static const int SUB_BG2;
		static const int SUB_BG3;
	};
}