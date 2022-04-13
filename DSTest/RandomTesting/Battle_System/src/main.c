#include <nds.h>
#include <stdio.h>
#include <string.h>
#include <maxmod9.h>

SpriteEntry OAMCopy[128];

#include <DeS.h>
#include <Store.h>
#include <Dirt.h>
#include <Cart.h>
#include <Numbers.h>
#include <NumbersLong.h>
#include <Actions.h>
#include <Scroll.h>

#include "soundbank.h"
#include "soundbank_bin.h"

#include "events.c"

volatile int frame = 0;

enum { CONTINUOUS, SINGLE } TouchType = CONTINUOUS;

void Vblank() {
	frame++;
}


//32x32 Sprites


//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	//Create Objects
	Sprite32 des = {0,0};
	Sprite16 cart = {0,0};
	Sprite8 playerLifes = {0,0};
	Sprite8 ActionBlock = {0,0};
	
	//Set Up Collision Boxes
	box PlayerBox;
	PlayerBox.Xpos = PlayerX;
	PlayerBox.Ypos = PlayerY;
	PlayerBox.SizeX = 32;
	PlayerBox.SizeY = 32;

	box EnemyBox;
	EnemyBox.Xpos = EnemyX;
	EnemyBox.Ypos = EnemyY;
	EnemyBox.SizeX = 16;
	EnemyBox.SizeY = 16;

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
	//Set player gfx
	init32(&des, (u8*)DeSTiles);
	dmaCopy(DeSPal, &VRAM_F_EXT_SPR_PALETTE[0][0],DeSPalLen);

	//Enemy gfx
	init16(&cart, (u8*)CartTiles);
	dmaCopy(CartPal, &VRAM_F_EXT_SPR_PALETTE[1][0],CartPalLen);

	//playerNum gfx
	init8(&playerLifes, (u8*)NumbersTiles);
	dmaCopy(NumbersPal, &VRAM_F_EXT_SPR_PALETTE[2][0],NumbersPalLen);

	//Actions gfx
	init8(&ActionBlock, (u8*)ActionsTiles);
	dmaCopy(ActionsPal, &VRAM_F_EXT_SPR_PALETTE[2][0],ActionsPalLen);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);

	ActionBlock.anim_frame = 1;


		
	//Make the bottom screen a blue color
	setBackdropColorSub(5555000000009999);
	
	//Background
	int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_512x512, 0,0);
	dmaCopy(ScrollBitmap, bgGetGfxPtr(bg3), 512*384);
	dmaCopy(ScrollPal, BG_PALETTE, 512*2);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int keys = 0;
   int sx = 0;
   int sy = 0;
   int width = 512;
   int height = 384;
	
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

		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		touchRead(&touch);
		
		int pressed = keysDown();
		int held = keysHeld();

		int FramesDone;

		if(Battle == false){
			//EnemyX -= Speed;

			ScrollBackground(bg3, 496, 496, BackgroundX, BackgroundY, true);

			if(PlayerJumpState == 0){
				Gravity();
			}
			else if(PlayerJumpState == 1){
				AntiGravity();
				des.state = W_JUMP;
			}
			else if(pressed & KEY_TOUCH || pressed & KEY_A){
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

			if(EnemyX <= -16){
				EnemyX = 256;
			}

			PlayerBox.Xpos = PlayerX;
			PlayerBox.Ypos = PlayerY;

			EnemyBox.Xpos = EnemyX;
			EnemyBox.Ypos = EnemyY;
		
			bool hit;
			hit = false;
			hit = CollisionCheck(PlayerBox, EnemyBox);
		

			if(hit == true){
				PlayerTurn = true;
				PlayerX = 20;
				PlayerY = 100;
				EnemyX = 200;
				EnemyY = 112;

				PlayerBox.Xpos = PlayerX;
				PlayerBox.Ypos = PlayerY;
				EnemyBox.Xpos = EnemyX;
				EnemyBox.Ypos = EnemyY;

				Battle = true;
			}

			if(des.state == W_JUMP || AnimFramesDone >= AnimFrames){
				des.anim_frame++;
				AnimFramesDone = 0;
			}
			else{
				AnimFramesDone++;
			}

			if(des.anim_frame >= FRAMES_PER_ANIMATION) des.anim_frame = 0;

			if(EnemyFramesDone > FRAMES_PER_ANIMATION){
				cart.anim_frame++;
				EnemyFramesDone = 0;
			}
			else{
				EnemyFramesDone++;
			}
			if(cart.anim_frame >= FRAMES_PER_ANIMATION) cart.anim_frame = 0;

		}
		else{
			if(PlayerTurn){
				PlayerBox.Xpos = PlayerX;
				PlayerBox.Ypos = PlayerY;
				EnemyBox.Xpos = EnemyX;
				EnemyBox.Ypos = EnemyY;
				PlayerTurnAction(Health, pressed);
			}
			else{
				PlayerBox.Xpos = PlayerX;
				PlayerBox.Ypos = PlayerY;
				EnemyBox.Xpos = EnemyX;
				EnemyBox.Ypos = EnemyY;
				EnemyTurnAction(Health, pressed);
			}
		}

		animate32(&des);
		animate16(&cart);
//enum SpriteState {W_JUMP = 0, W_RIGHT = 1, W_DEAD = 2, W_LEFT = 3};
		if(Health == 3){
			playerLifes.anim_frame = 0;
		}
		else if(Health == 2){
			playerLifes.anim_frame = 1;
		}
		else if(Health == 1){
			playerLifes.anim_frame = 2;
		}
		else{
			playerLifes.anim_frame = 3;
		}

		if(ActionType == 0){
			ActionBlock.anim_frame = 1;
		}
		else if(ActionType == 1){
			ActionBlock.anim_frame = 0;
		}

		animate8(&playerLifes);

		animate8(&ActionBlock);

		oamSet(&oamMain, 0, PlayerBox.Xpos, PlayerBox.Ypos, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
			des.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 1, EnemyBox.Xpos, EnemyBox.Ypos, 0, 1, SpriteSize_16x16, SpriteColorFormat_256Color, 
			cart.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 2, 20, 150 - 10, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, 
			playerLifes.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 3, 30, 90 - 10, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, 
			ActionBlock.sprite_gfx_mem, -1, false, false, false, false, false);

		oamUpdate(&oamMain);

	}
}
