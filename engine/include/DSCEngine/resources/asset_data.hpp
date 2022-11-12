#pragma once

#include "DSCEngine/resources/readonly_data.hpp"

namespace DSC
{
	class AssetData : public ReadOnlyData
	{
	public:
		__attribute__ ((packed))
		short width;                    /// asset width  (divided by 8)
		__attribute__ ((packed))
		short height;                   /// asset height (divided by 8)		
		
		AssetData();
		~AssetData() = delete;
		
		int get_color_depth() const;
		bool is_bitmap() const;
		
		
		int get_gfx_length() const;
		int get_pal_length() const;
		int get_pal_count() const;
		void extract_gfx(void* destination) const;
		void extract_palette(void* destination) const;		
		
		static const int ROA_IS_BITMAP;
		static const int ROA_COLOR_DEPTH;
	};
}