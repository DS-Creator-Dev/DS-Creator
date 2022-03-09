#include <nds.h>
#include <stdio.h>
#include <string.h>

SpriteEntry OAMCopy[128];

#include "DeS.h"
#include "Store.h"
#include "Dirt.h"

//---------------------------------------------------------------------------------
void initOAM(void) {
//---------------------------------------------------------------------------------
	int i;

	for(i = 0; i < 128; i++) {
		OAMCopy[i].attribute[0] = ATTR0_DISABLED;
	}	
}

//---------------------------------------------------------------------------------
void updateOAM(void) {
//---------------------------------------------------------------------------------
	
	memcpy(OAM, OAMCopy, 128 * sizeof(SpriteEntry));
}


volatile int frame = 0;

enum { CONTINUOUS, SINGLE } TouchType = CONTINUOUS;

//---------------------------------------------------------------------------------
void Vblank() {
//---------------------------------------------------------------------------------
	frame++;
}
 
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	int min_x  = 4096 , min_y  = 4096, max_x  = 0, max_y   = 0;
	int min_px = 4096 , min_py = 4096, max_px = 0 , max_py = 0;
	touchPosition touch;

	// put the main screen on the bottom lcd
	//lcdMainOnBottom();

	initOAM();
   
   //set the video mode
    videoSetMode(  MODE_0_2D | 
                   DISPLAY_SPR_ACTIVE |		//turn on sprites
                   DISPLAY_BG0_ACTIVE |		//turn on background 0
                   DISPLAY_SPR_1D			//this is used when in tile mode
                    );

	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	int i;
	
	// Sprite initialisation
	for(i = 0; i < 256; i++)
		SPRITE_PALETTE[i] = ((u16*)DeSPal)[i];

	for(i = 0; i< 32*16; i++)
		SPRITE_GFX[i] = ((u16*)DeSTiles)[i];

 
	//consoleInit(0, 0,BgType_Text4bpp, BgSize_T_256x256, 31,0, false, false); 

	consoleDemoInit();

	int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);

	dmaCopy(StoreBitmap, bgGetGfxPtr(bg3), 256*192);
	dmaCopy(StorePal, BG_PALETTE, 256*2);

 
	while(1) {
		int TOUCH_X;
		int TOUCH_Y;

		swiWaitForVBlank();
		updateOAM();

		scanKeys();

		touchRead(&touch);
		
		int pressed = keysDown();
		int held = keysHeld();

		if ( TouchType == SINGLE && !(pressed & KEY_TOUCH) ) continue;

		if ( !(held & KEY_TOUCH) || touch.rawx == 0 || touch.rawy == 0) continue;

		if ( touch.rawx > max_x)		max_x = touch.rawx;
		if ( touch.rawy > max_y)		max_y = touch.rawy;
		if ( touch.px > max_px)	max_px = touch.px;
		if ( touch.py > max_py)	max_py = touch.py;

		if ( touch.rawx < min_x)		min_x = touch.rawx;
		if ( touch.rawy < min_y)		min_y = touch.rawy;
		if ( touch.px < min_px)	min_px = touch.px;
		if ( touch.py < min_py)	min_py = touch.py;

		TOUCH_X = touch.px;
		TOUCH_Y = touch.py;

		iprintf("\x1b[12;12H(%d,%d)      ",TOUCH_X,TOUCH_Y);

		OAMCopy[0].attribute[2] = 0;
		OAMCopy[0].attribute[1] = ATTR1_SIZE_32 |((TOUCH_X - 16) & 0x01FF);
		OAMCopy[0].attribute[0] = ATTR0_COLOR_256 | ATTR0_SQUARE | ((TOUCH_Y -16) & 0x00FF);
	}
}

