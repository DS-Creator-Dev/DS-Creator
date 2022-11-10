#include <nds.h>
#include <stdio.h>
#include <DSC>

#include "background.h"
#include "palette.h"

using namespace DSC;

class Scene1 : public Scene
{
private:
	PaletteManager palette_manager = PaletteManager(&VRAM_E_EXT_PALETTE[1][6]);
	Vector<short> colors; // keep track of colors for demonstration purposes	
public:
	void init() override
	{		
		videoSetMode(MODE_5_2D);
		bgExtPaletteEnable();
		
		// hopefully we won't have to manually do stuff like this in the future :
		vramSetBankB(VRAM_B_MAIN_BG_0x06000000);
		
		bgInit(2, BgType_Bmp8, BgSize_B8_256x256, 0, 0);						
		dmaCopy(backgroundBitmap,(void*)0x06000000,256*192);				
		dmaCopy(backgroundPal, BG_PALETTE, backgroundPalLen);
		
		bgInit(1, BgType_Text8bpp, BgSize_T_256x256, 24, 4);
		dmaCopy(paletteTiles,(void*)0x06010000,paletteTilesLen);
		dmaCopy(paletteMap,(void*)0x0600C000,paletteMapLen);
		
		// test BgExt palette
		
		vramSetBankE(VRAM_E_LCD);
		
		dmaCopy(palettePal, &VRAM_E_EXT_PALETTE[1][6], palettePalLen);

		vramSetBankE(VRAM_E_BG_EXT_PALETTE); 				
		
		consoleDemoInit();		
		
		iprintf("\n DSC Palette Manager Test \n");
		
		for(int i=0;i<90;i++)
		{
			swiWaitForVBlank();
		}
		
		vramSetBankE(VRAM_E_LCD);
		
		for(int i=0;i<256;i++)
		{
			VRAM_E_EXT_PALETTE[1][6][i]=0;
		}			

		vramSetBankE(VRAM_E_BG_EXT_PALETTE);
		
		iprintf("\n\n A - add new color\n");
		iprintf(" B - add new 4-bit palette\n");
		iprintf(" X - remove color\n");
		iprintf(" Y - remove 4-bit palette\n\n\n");
		
		iprintf(" Check emulator logs for\n feedback");
		
		
		
		key_down += key_down_hanlder;
	}
	
	void add_one_color()
	{
		int color = 0;		
		if(colors.size()==0)
		{
			color = 0x4000 + (rand() & 0x3fff); // pick a random brighter color
		}			
		
		Debug::log("Trying to reserve color %x", color);
		
		vramSetBankE(VRAM_E_LCD);
		int index = palette_manager.reserve1(color);
		vramSetBankE(VRAM_E_BG_EXT_PALETTE);
		
		Debug::log("Color %x placed at index %i", color, index);
	}
	
	void remove_one_color()
	{
		// TO DO ...
	}
	
	static void key_down_hanlder(void* sender, void* _keys);
};

void Scene1::key_down_hanlder(void* sender, void* _keys)
{	
	Scene1* scene = (Scene1*) sender;
	switch((const int)_keys)
	{
		case KEY_A: scene->add_one_color(); break;		
		case KEY_X: scene->remove_one_color(); break;
		default: break;
	}	
}

dsc_launch(Scene1);
