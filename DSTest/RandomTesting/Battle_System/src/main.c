#include <nds.h>
#include <stdio.h>
#include <string.h>
#include <maxmod9.h>

SpriteEntry OAMCopy[128];

#include <Store.h>
#include <Dirt.h>
#include <Cart.h>
#include <Numbers.h>
#include <NumbersLong.h>
#include <Actions.h>
#include <Scroll.h>
#include <Scarlet.h>

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

	//Create Objects
	Sprite Player = {0,0};
	Sprite cart = {0,0};
	Sprite playerLifes = {0,0};
	Sprite ActionBlock = {0,0};

	cart.Xpos = 256;
	cart.Ypos = 112;
	
	//Set Up Collision Boxes
	Box PlayerBox;
	PlayerBox.OffsetX = 24;
	PlayerBox.OffsetY = 26; //26
	PlayerBox.Xpos = Player.Xpos + PlayerBox.OffsetX;
	PlayerBox.Ypos = Player.Ypos + PlayerBox.OffsetY;
	PlayerBox.SizeX = 15;
	PlayerBox.SizeY = 40;

	Box EnemyBox;
	EnemyBox.Xpos = cart.Xpos;
	EnemyBox.Ypos = cart.Ypos;
	EnemyBox.SizeX = 16;
	EnemyBox.SizeY = 16;

	Box GroundBox;
	GroundBox.Xpos = 0;
	GroundBox.Ypos = 130;
	GroundBox.SizeX = 256;
	GroundBox.SizeY = 1;

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
	init64(&Player, (u8*)ScarletTiles);
	dmaCopy(ScarletPal, &VRAM_F_EXT_SPR_PALETTE[0][0],ScarletPalLen);

	//Enemy gfx
	init16(&cart, (u8*)CartTiles);
	dmaCopy(CartPal, &VRAM_F_EXT_SPR_PALETTE[1][0],CartPalLen);

	//playerNum gfx
	init8(&playerLifes, (u8*)NumbersTiles);
	dmaCopy(NumbersPal, &VRAM_F_EXT_SPR_PALETTE[3][0],NumbersPalLen);

	//Actions gfx
	init8(&ActionBlock, (u8*)ActionsTiles);
	dmaCopy(ActionsPal, &VRAM_F_EXT_SPR_PALETTE[2][0],ActionsPalLen);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);

	ActionBlock.anim_frame = 1;


		
	//Make the bottom screen a blue color
	setBackdropColorSub(5555000000009999);
	
	//Background
	int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);
	dmaCopy(StoreBitmap, bgGetGfxPtr(bg3), 256*256);
	dmaCopy(StorePal, BG_PALETTE, 256*2);

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

		int FramesDone;

		if(Battle == false){
			cart.Xpos -= Speed;

			ScrollBackground(bg3, 257, 193, BackgroundX, BackgroundY, true);

			if(PlayerJumpState == 0){
				Player = Gravity(Player);
			}
			else if(PlayerJumpState == 1){
				Player = AntiGravity(Player);
				Player.state = W_JUMP;
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

			if(cart.Xpos <= -16){
				cart.Xpos = 256;
			}

			PlayerBox.Xpos = Player.Xpos + PlayerBox.OffsetX;
			PlayerBox.Ypos = Player.Ypos + PlayerBox.OffsetY;

			EnemyBox.Xpos = cart.Xpos + EnemyBox.OffsetX;
			EnemyBox.Ypos = cart.Ypos + EnemyBox.OffsetY;
		
			bool hit;
			hit = false;
			hit = CollisionCheck(PlayerBox, EnemyBox);
		

			if(hit == true){
				PlayerTurn = true;
				Player.Xpos = BattlePlayerX;
				Player.Ypos = BattlePlayerY;
				cart.Xpos = 200;
				cart.Ypos = 112;

				PlayerBox.Xpos = Player.Xpos + PlayerBox.OffsetX;
				PlayerBox.Ypos = Player.Ypos + PlayerBox.OffsetY;
				EnemyBox.Xpos = cart.Xpos + EnemyBox.OffsetX;
				EnemyBox.Ypos = cart.Ypos + EnemyBox.OffsetY;

				Battle = true;
			}

			hit = CollisionCheck(PlayerBox, GroundBox);
			if(hit){
				if(PlayerJumpState == 0){
					PlayerJumpState = 2;
					Player.state = W_RIGHT;
				}
			}

			if(Player.state == W_JUMP || Player.AnimationFrames >= FRAMES_PER_ANIMATION){
				Player.anim_frame++;
				Player.AnimationFrames = 0;
			}
			else{
				Player.AnimationFrames++;
			}

			if(Player.anim_frame >= FRAMES_PER_ANIMATION) Player.anim_frame = 0;

			if(cart.AnimationFrames > FRAMES_PER_ANIMATION){
				cart.anim_frame++;
				cart.AnimationFrames = 0;
			}
			else{
				cart.AnimationFrames++;
			}
			if(cart.anim_frame >= FRAMES_PER_ANIMATION) cart.anim_frame = 0;

		}
		else{
			if(PlayerTurn){
				PlayerBox.Xpos = Player.Xpos + PlayerBox.OffsetX;
				PlayerBox.Ypos = Player.Ypos + PlayerBox.OffsetY;
				EnemyBox.Xpos = cart.Xpos + EnemyBox.OffsetX;
				EnemyBox.Ypos = cart.Ypos + EnemyBox.OffsetY;
				Player = PlayerTurnAction(cart, EnemyBox, pressed, Player);
			}
			else{
				PlayerBox.Xpos = Player.Xpos + PlayerBox.OffsetX;
				PlayerBox.Ypos = Player.Ypos + PlayerBox.OffsetY;
				EnemyBox.Xpos = cart.Xpos + EnemyBox.OffsetX;
				EnemyBox.Ypos = cart.Ypos + EnemyBox.OffsetY;
				cart = EnemyTurnAction(pressed, cart, Player, PlayerBox);
			}
		}

		animate64(&Player);
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

		oamSet(&oamMain, 0, Player.Xpos, Player.Ypos, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, 
			Player.sprite_gfx_mem, -1, false, false, false, PlayerFlipped, false);
		oamSet(&oamMain, 1, cart.Xpos, cart.Ypos, 0, 1, SpriteSize_16x16, SpriteColorFormat_256Color, 
			cart.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 2, 20, 150 - 10, 0, 3, SpriteSize_8x8, SpriteColorFormat_256Color, 
			playerLifes.sprite_gfx_mem, -1, false, false, false, false, false);
		oamSet(&oamMain, 3, 30, 90 - 10, 0, 2, SpriteSize_8x8, SpriteColorFormat_256Color, 
			ActionBlock.sprite_gfx_mem, -1, false, false, false, false, false);

		oamUpdate(&oamMain);

	}
}
