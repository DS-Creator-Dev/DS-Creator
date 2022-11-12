#include "DSCEngine/video/measure.hpp"

using namespace DSC;

Measure& DSC::Measure::_4bpp() { color_depth = 4; return *this;}
Measure& DSC::Measure::_8bpp() { color_depth = 8; return *this;}
Measure& DSC::Measure::_16bpp() { color_depth = 16; return *this;}
Measure& DSC::Measure::metatile(int tw, int th) { tile_w = tw, tile_h = th; return *this;}

int DSC::Measure::tiles(int count) const
{
	return count * 8*tile_w * 8*tile_h * color_depth / 8;
}

int DSC::Measure::tiles(int rows_count, int cols_count) const
{
	return tiles(rows_count * cols_count);
}
	
int DSC::Measure::bitmap(int width, int height) const
{
	return width * height * color_depth / 8;
}
	
int DSC::Measure::tiles_count(int size) const
{
	return size * 8 / (color_depth * 8 * tile_w * 8 * tile_h);
}
