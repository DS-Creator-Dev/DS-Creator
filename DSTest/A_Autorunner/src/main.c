#include <nds.h>
#include <stdio.h>
#include <string.h>

SpriteEntry OAMCopy[128];

#include <DeS.h>
#include <Store.h>
#include <Dirt.h>
#include <Cart.h>

#define FRAMES_PER_ANIMATION 4

void initOAM(void) {
	int i;

	for(i = 0; i < 128; i++) {
		OAMCopy[i].attribute[0] = ATTR0_DISABLED;
	}	
}

void updateOAM(void) {
	
	memcpy(OAM, OAMCopy, 128 * sizeof(SpriteEntry));
}


volatile int frame = 0;

enum { CONTINUOUS, SINGLE } TouchType = CONTINUOUS;

void Vblank() {
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

//Where is the ground
int GroundPos = 100;
//How many frames you want between animation frames
int AnimFrames = 0;
//How many frames between animation frames are done
int AnimFramesDone = 0;
//How many frames will the player be in the air
int FramesInAir = 26;
//How many frames has the player been in the air
int FramesAirDone = 0;
//How much force does gravity have
int GravityForce = 5;
//How much force does the player have jumping
int JumpForce = 7;
//The player's Y position
int PlayerY = 64;
//The player's X position
int PlayerX = 0;
//The player's movement speed
int Speed = 1;
//How many frames you want the player to go up
int FramesToJump = 26;
//How many of those frames have been done
int FramesJumpDone = 0;
//The state the player is in while jumping/on the ground
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
	initOAM();
   
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
		

	setBackdropColorSub(5555000000009999);
	

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



		if(PlayerJumpState == 0){
			if(PlayerY >= GroundPos){
				PlayerJumpState = 2;
				des.state = W_RIGHT;
				PlayerY = GroundPos;
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