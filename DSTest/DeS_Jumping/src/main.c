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

int PlayerY = 64;
int FramesToJump = 40;
int FramesDone = 0;
int PlayerJumpState;
/*
0 = Is Falling
1 = Is Jumping
2 = Can Jump
*/
 
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
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

		swiWaitForVBlank();
		updateOAM();

		scanKeys();

		touchRead(&touch);
		
		int pressed = keysDown();
		int held = keysHeld();

		int FramesDone;

		if(PlayerJumpState == 0){
			Gravity();
		}
		else if(PlayerJumpState == 1){
			AntiGravity();
		}
		else if(pressed  & KEY_TOUCH){
			if(PlayerJumpState == 2){
				PlayerJumpState = 1;
			}
		}

		OAMCopy[0].attribute[2] = 0;
		OAMCopy[0].attribute[1] = ATTR1_SIZE_32 |((0) & 0x01FF);
		OAMCopy[0].attribute[0] = ATTR0_COLOR_256 | ATTR0_SQUARE | ((PlayerY) & 0x00FF);
		if(PlayerJumpState == 0){
			if(PlayerY > 80){
				PlayerJumpState = 2;
			}
		}
		
	}
}

void Gravity(){
	PlayerY++;
}
void AntiGravity(){
	FramesDone++;
	PlayerY--;
	if(FramesDone >= FramesToJump){
		FramesDone = 0;
		PlayerJumpState = 0;
	}
}