#pragma once

#include "DSCEngine/types/hash_map.hpp"

namespace DSC
{	
	/*! \brief Automatic palette manager
	 */
	class PaletteManager
	{
	private:
		static int hashColor(const short& color);
	
		void* pal_offset;		
		int free_space[8];
		
		short records4bpp[16];
		
		HashMap<short, int, hashColor, 128> colors_map;						
	public:
		/*! \brief creates a new PaletteManager instance
			\param palettes_offset  the address of the palette data managed by the instance			
		 */
		PaletteManager(void* palettes_offset);
		
		/*! \brief choose an index for the specified color
			\param color a BGR15 color value
			\return a value V that tells the palette index it has been placed at.
			
			If the color already exists in the palette, it is not added once again and the position of
			the already existing color is returned.
		 */		 
		int reserve1(int color);
		
		/*! \brief loads a 4-bit palette
			\param palette4 address to a stream of 16 unsigned shorts represing the BGR15 color codes 
			\return the id of the palette slot assigned to the given 4-bit palette has been, a number from 0 (0x0) to 15 (0xF)
			
			\details This function does not have the expected effect unless the target palette is a standard palette.
			Do not load 4-bit palettes in extended slots. They may be loaded, but can't be used in the intended ways.			
		 */
		int reserve16(const void* palette4);
		
		
		/*! \brief removes a certain color from the palette
			\param color a BGR15 color value
			
			\details If the color is being used by more than one asset, it is still kept in the palette even after unloading it.
			A color is fully released only after no other resources use it.
			Attempts to unload an inexistent color are simply ignored.
		 */
		void unload1(int color);
		
		/*! \brief removes a 4-bit palette
			\param palette4 address to a stream of 16 unsigned shorts represing the BGR15 color codes 
			
			\details A 4-bit palette is fully released only after no other resources use it. 
			Attempts to unload an inexistent palette are simply ignored.
		 */
		void unload16(const void* palette4);
		
		~PaletteManager();
	};
}