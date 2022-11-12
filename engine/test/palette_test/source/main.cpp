#include <nds.h>
#include <stdio.h>
#include <DSC>

#include "background.h"
#include "palette.h"
#include "roa_magma_texture8.h"

using namespace DSC;

class Scene1 : public Scene
{
private:
	PaletteManager palette_manager = PaletteManager(&VRAM_E_EXT_PALETTE[1][6]);
	Vector<short> colors; // keep track of colors for demonstration purposes	
	Vector<int> pal16; 
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
		
		/*for(int i=1;i<256;i++)
		{
			vramSetBankE(VRAM_E_LCD);
			VRAM_E_EXT_PALETTE[1][6][i-1]=0;
			VRAM_E_EXT_PALETTE[1][6][i]=0x001f;
			vramSetBankE(VRAM_E_BG_EXT_PALETTE);
			for(int j=0;j<3;j++)
				swiWaitForVBlank();			
		}
		
		vramSetBankE(VRAM_E_LCD);
		//VRAM_E_EXT_PALETTE[1][6][255]=0;		
		for(int i=0;i<256;i++)
		{
			VRAM_E_EXT_PALETTE[1][6][i]=0;
		}				
		vramSetBankE(VRAM_E_BG_EXT_PALETTE);
		swiWaitForVBlank();*/
		
		iprintf("\n\n A - add new color\n");
		iprintf(" B - add new 4-bit palette\n");
		iprintf(" X - remove color\n");
		iprintf(" Y - remove 4-bit palette\n");
		iprintf(" L - load from asset (8-bit)\n");
		iprintf(" R - unload from asset (8-bit)\n\n\n");
		
		iprintf(" Check emulator logs for\n feedback");
		
		
		
		key_down += key_down_hanlder;
	}
	
	void add_one_color()
	{
		int color = 0;				
		color = 0x4000 + (rand() & 0x3fff); // pick a random brighter color				
		
		Debug::log("Trying to reserve color %x", color);
		
		vramSetBankE(VRAM_E_LCD);
		int index = palette_manager.reserve1(color);
		vramSetBankE(VRAM_E_BG_EXT_PALETTE);
		
		if(index==-1)
		{
			Debug::log("Can't add colors anymore. Palette is full.");
			return;
		}				
		Debug::log("Color %x placed at index %i", color, index);
		colors.push_back(color);
	}
	
	void remove_one_color()
	{
		if(colors.size()==0) return;
		
		int i = rand()%colors.size();
		int color = colors[i];
		
		vramSetBankE(VRAM_E_LCD);
		palette_manager.unload1(color);
		vramSetBankE(VRAM_E_BG_EXT_PALETTE);
				
		Debug::log("Unloaded color %x.", color, index);		
		colors.remove(color);
	}
	
	void add_4bit_palette()
	{		
		int src_slot = rand() % 16;
		const short* pal = ((const short*)palettePal) + 16*src_slot;
		
		vramSetBankE(VRAM_E_LCD);
		int slot = palette_manager.reserve16(pal);
		vramSetBankE(VRAM_E_BG_EXT_PALETTE);
		
		if(slot==-1)
		{
			Debug::log("Cannot load 4-bit palette. Not enough space");
			return;
		}
		
		Debug::log("Loaded 4-bit palette #%i at slot 0%X", src_slot, slot);
		pal16.push_back(src_slot);
	}
	
	void remove_4bit_palette()
	{
		if(pal16.size()==0) return;
		
		int src_slot = pal16[rand() % pal16.size()];
		const short* pal = ((const short*)palettePal) + 16*src_slot;
				
		vramSetBankE(VRAM_E_LCD);		
		
		palette_manager.unload16(pal);
		vramSetBankE(VRAM_E_BG_EXT_PALETTE);
		
		Debug::log("Unloaded 4-bit palette #%i", src_slot);
		pal16.remove(src_slot);
	}	
	
	const AssetData* asset = &ROA_magma_texture8;
	int times_allocated = 0;
	
	void load_from_asset()
	{		
		vramSetBankE(VRAM_E_LCD);		
		if(palette_manager.try_load(asset).succeeded)
		{
			times_allocated++;
			Debug::log("Asset successfully allocated");
		}	
		else
		{
			Debug::log("Failed to allocate asset");
		}
		vramSetBankE(VRAM_E_BG_EXT_PALETTE);
	}
	
	void unload_from_asset()
	{
		if(times_allocated==0)
		{
			Debug::log("Asset not allocated. Unloading skipped.");
			return;
		}
		vramSetBankE(VRAM_E_LCD);		
		palette_manager.unload(asset);
		vramSetBankE(VRAM_E_BG_EXT_PALETTE);
		times_allocated--;
		Debug::log("Asset successfully deallocated.");
		if(times_allocated>0)
		{
			Debug::log("Asset is still allocated %i times", times_allocated);
		}
	}
	
	static void key_down_hanlder(void* sender, void* _keys);
};

void Scene1::key_down_hanlder(void* sender, void* _keys)
{	
	Scene1* scene = (Scene1*) sender;
	switch((const int)_keys)
	{
		case KEY_A: scene->add_one_color(); break;		
		case KEY_B: scene->add_4bit_palette(); break;		
		case KEY_X: scene->remove_one_color(); break;
		case KEY_Y: scene->remove_4bit_palette(); break;
		case KEY_L: scene->load_from_asset(); break;
		case KEY_R: scene->unload_from_asset(); break;
		default: break;
	}	
}

dsc_launch(Scene1);
