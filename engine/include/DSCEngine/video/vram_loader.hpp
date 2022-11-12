#pragma once

#include "DSCEngine/resources/asset_data.hpp"

namespace DSC
{
	class VramLoader
	{
	public:
		static void load(const AssetData* asset, void* dest, short* pal_indices = nullptr);
	};
}