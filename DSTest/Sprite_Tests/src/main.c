#include <nds.h>
#include <stdio.h>
#include <string.h>

SpriteEntry OAMCopy[128];

#include <DeS.h>
#include <Store.h>
#include <Dirt.h>
#include <Cart.h>

#define FRAMES_PER_ANIMATION 4

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

typedef struct 
{
	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}Des;

void animateMan(Des *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;

	u8* offset = sprite->frame_gfx + frame * 32*32;

	dmaCopy(offset, sprite->sprite_gfx_mem, 32*32);
}

void initMan(Des *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	sprite->frame_gfx = (u8*)gfx;
}

enum SpriteState {W_JUMP = 0, W_RIGHT = 1, W_DEAD = 2, W_LEFT = 3};

int AnimFrames = 10;
int AnimFramesDone = 0;
int FramesInAir = 0;
int GravityForce = 1.5;
int JumpForce = 1;
int PlayerY = 64;
int PlayerX = 0;
int Speed = 1.5;
int FramesToJump = 50;
int FramesJumpDone = 0;
int FramesAirDone = 0;
int PlayerJumpState;
/*
0 = Is Falling
1 = Is Jumping
2 = Can Jump
3 = In Air
*/
 
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	Des des = {0,0};

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
	vramSetBankB(VRAM_A_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	initMan(&des, (u8*)DeSTiles);
	dmaCopy(DeSPal, SPRITE_PALETTE, 512);

	int i;
	
	// Sprite initialisation
	for(i = 0; i < 256; i++)
		SPRITE_PALETTE[i] = ((u16*)DeSPal)[i];
	for(i = 0; i < 32*16; i++)
		SPRITE_GFX[i] = ((u16*)DeSTiles)[i];
	
		

	setBackdropColorSub(5555000000009999);
	

 
	//consoleInit(0, 0,BgType_Text4bpp, BgSize_T_256x256, 31,0, false, false); 

	//consoleDemoInit();

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

		PlayerX += Speed;

		if(PlayerJumpState == 0){
			Gravity();
		}
		else if(PlayerJumpState == 1){
			AntiGravity();
			des.state = W_JUMP;
		}
		else if(pressed  & KEY_TOUCH){
			if(PlayerJumpState == 2){
				PlayerJumpState = 1;
			}
		}
		else if(FramesInAir != 0){
			if(PlayerJumpState == 4){
				InAir();
			}
		}
		else if(PlayerJumpState == 4){
			InAir();
		}

		/*
		OAMCopy[0].attribute[1] = 0;
		OAMCopy[0].attribute[1] = ATTR1_SIZE_32 |((PlayerX) & 0x01FF);
		OAMCopy[0].attribute[0] = ATTR0_COLOR_256 | ATTR0_SQUARE | ((PlayerY) & 0x00FF);

		OAMCopy[1].attribute[2] = 4;
		OAMCopy[1].attribute[1] = ATTR1_SIZE_32 |((105) & 0x01FF);
		OAMCopy[1].attribute[0] = ATTR0_COLOR_256 | ATTR0_SQUARE | ((104) & 0x00FF);
		*/

		if(PlayerJumpState == 0){
			if(PlayerY >= 100){
				PlayerJumpState = 2;
				des.state = W_RIGHT;
			}
		}
		if(PlayerX >= 256 + 24){
			PlayerX = -24;
		}

		if(des.state == W_JUMP || AnimFramesDone >= AnimFrames){
			des.anim_frame++;
			AnimFramesDone = 0;
		}
		else{
			AnimFramesDone++;
		}

		if(des.anim_frame >= FRAMES_PER_ANIMATION) des.anim_frame = 0;

		animateMan(&des);

		oamSet(&oamMain, 0, PlayerX, PlayerY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
			des.sprite_gfx_mem, -1, false, false, false, false, false);

		oamUpdate(&oamMain);
		
	}
}

void Gravity(){
	PlayerY += GravityForce;
}
void AntiGravity(){
	FramesJumpDone++;
	PlayerY -= JumpForce;
	if(FramesJumpDone >= FramesToJump){
		FramesJumpDone = 0;
		PlayerJumpState = 4;
	}
}
void InAir(){
	FramesAirDone++;
	if(FramesAirDone < FramesInAir){

	}
	else{
		PlayerJumpState = 0;
	}
}