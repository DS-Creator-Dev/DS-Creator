#pragma once

namespace DSC
{
	/*! \brief Helper class to deal with graphics size computations
	 */
	class Measure
	{
	private:
		int color_depth = 4;
		int tile_w = 1;
		int tile_h = 1;
	public:
		/*! \brief chain function to set color depth to 4 bpp
			\return the current instance with modified settings
		 */
		Measure& _4bpp();
		
		/*! \brief chain function to set color depth to 8 bpp
			\return the current instance with modified settings
		 */
		Measure& _8bpp();
		
		/*! \brief chain function to set color depth to 16 bpp
			\return the current instance with modified settings
		 */
		Measure& _16bpp();
		
		/*! \brief chain function to set meta tile size
			\param tw meta tile width (e.g. for 32x16px tiles, tw equals 4)
			\param th meta tile height (e.g. for 32x16px tiles, th equals 2)
			\return the current instance with modified settings
		 */
		Measure& metatile(int tw, int th);
		
		/*! \brief computes the size of a number of tiles given the measure settings
			\param count the number of tiles
			\return size of a graphics with the given number of tiles and the defined settings
			
			\details In computing the tiles size, the color depth and metatile data are taken into account.
			By default, tiles are 8x8px with 4bpp color-depth
		 */
		int tiles(int count) const;
			
		/*! \brief computes the size of a matrix of tiles given the measure settings
			\param rows_count number of rows in the tiles matrix
			\param cols_count number of columns in the tiles matrix
			\return size of a graphics with the given number of tiles and the defined settings
			
			\details In computing the tiles size, the color depth and metatile data are taken into account.
			By default, tiles are 8x8px with 4bpp color-depth
		 */			
		int tiles(int rows_count, int cols_count) const;
		
		/*! \brief computes the size of a bitmap given the measure settings
			\param width bitmap's width in pixels
			\param height bitmap's height in pixels
			\return size of a bitmap with the given size and the defined color depth
		 */		
		int bitmap(int width, int height) const;
		
		/*! \brief finds how many tiles can fit in memory block of a certain size, given the measure settings
			\param size the memory block size
			\return maximum number of tiles whose size are at most the specified size
		 */
		int tiles_count(int size) const;
	};
}
