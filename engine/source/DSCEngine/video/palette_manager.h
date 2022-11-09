#pragma once

namespace DSC
{
	/*! \brief Automatic palette manager
	 */
	class PaletteManager
	{
	private:
		void* pal_offset;
		int pal_size;
		int* free_space;
		
		unsigned short records4bpp[16];
		
	public:
		/*! \brief creates a new PaletteManager instance
			\param palettes_offset  the address of the palettes data managed by the instance
			\param palettes_count   the number of palettes managed by the instance (useful for
									handling extended palettes). This attribute is 1 by default.
									Minimum 1 and maximum 8 palettes are allowed.
		 */
		PaletteManager(void* palettes_offset, int palettes_count = 1);
		
		/*! \brief choose an index for the specified color
			\param color a BGR15 color value
			\return a value V that tells the palette and index it has been placed to.

			\details The value V is computed based on two values: 
			- P_Id  = the id of the palette relative to the palettes managed by this instance
					  (P_Id = 0  refers to the palette at PaletteManager::pal_offset)
			- Index = the index the color occupied in the palette P_Id (0..255).
			
			Therefore, V = P_Id*256 + Index.
			The palette id and palette index can be obtained with simple manipulations on V:
			
			\code{.cpp}
				P_Id  = V / 256 = V >> 8;
				Index = V % 256 = V & 0xFF;
			\endcode
			
			If the color already exists in the palette, it is not added once again and the position of
			the already existing color is returned.
		 */		 
		int reserve1(int color);
		
		/*! \brief loads a 4-bit palette
			\param palette4 address to a stream of 16 unsigned shorts represing the BGR15 color codes 
			\return the id of the palette slot assigned to the given 4-bit palette has been, a number from 0 (0x0) to 15 (0xF)
			
			\details This function does not have the expected effect unless the target palette is a standard palette.
			Do not load 4-bit palettes in extended slots. They may be loaded, but can't be used in the intended ways.
			The function will naively check if the instnaces manages a single palette, because more palettes is 
			a clear sign of extended slots being used.
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