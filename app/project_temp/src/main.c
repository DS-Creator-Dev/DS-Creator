#include <nds.h>
#include <stdio.h>
#include <string.h>
#include <maxmod9.h>

SpriteEntry OAMCopy[128];

#include "soundbank.h"
#include "soundbank_bin.h"

#include "events.c"

volatile int frame = 0;

enum { CONTINUOUS, SINGLE } TouchType = CONTINUOUS;

void Vblank() {
	frame++;
}

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	SetUpRooms();
	SetUpRoomBoxes();

	//Touch Position
	touchPosition touch;

    //Setting Video Modes
    videoSetMode(  MODE_0_2D | 
                   DISPLAY_SPR_ACTIVE |		//turn on sprites
                   DISPLAY_BG0_ACTIVE |		//turn on background 0
                   DISPLAY_SPR_1D			//this is used when in tile mode
                    );
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_0_2D);

	//Setting the banks. Does not include the F bank
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_A_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	//Set up oam
	oamInit(&oamMain, SpriteMapping_1D_128, true);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	//Set bank F
	vramSetBankF(VRAM_F_LCD);
	//init16(&Player, (u8*)ScarletMapTiles);
	//dmaCopy(ScarletMapPal, &VRAM_F_EXT_SPR_PALETTE[0][0],ScarletMapPalLen);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);

	//Background
	//int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);
	//dmaCopy(Grass1Bitmap, bgGetGfxPtr(bg3), 256*256);
	//dmaCopy(Grass1Pal, BG_PALETTE, 256*2); //80% Trans on shadows
		
	//Make the bottom screen a blue color
	setBackdropColorSub(5555000000009999);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   int keys = 0;
   int sx = 0;
   int sy = 0;
   int width = 0;
   int height = 0;
//////////////////////////////////////////////////////////////////////////////////////Music
	mmInitDefaultMem((mm_addr)soundbank_bin);
	
	// load the module
	mmLoad( MOD_MYSONG );

	// load sound effects
	//mmLoadEffect( SFX_AMBULANCE );
	//mmLoadEffect( SFX_BOOM );

	// Start playing module
	mmStart( MOD_MYSONG, MM_PLAY_LOOP );

/*
	mm_sound_effect ambulance = {
		{ SFX_AMBULANCE } ,			// id
		(int)(1.0f * (1<<10)),	// rate
		0,		// handle
		255,	// volume
		0,		// panning
	};
*/	
 

	//Loops every frame
	while(1) {

		swiWaitForVBlank();

		scanKeys();

		touchRead(&touch);
		
		int pressed = keysDown();
		int held = keysHeld();
		int released = keysUp();

		//animate16(&Player);
		//oamSet(&oamMain, 0, Player.Xpos, Player.Ypos, 0, 0, SpriteSize_16x16, SpriteColorFormat_256Color, Player.sprite_gfx_mem, -1, false, false, false, PlayerFlipped, false);
		//oamUpdate(&oamMain);
	}
}