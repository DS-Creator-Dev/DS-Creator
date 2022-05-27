#include <nds.h>
#include <stdio.h>
#include <string.h>

SpriteEntry OAMCopy[128];

#include <DeS.h>
#include <Store.h>
#include <Dirt.h>
#include <Cart.h>

#define FRAMES_PER_ANIMATION 2

#define FRAMES_PER_ANIMATION_ENEMY 2

#define FRAMES_BETWEEN_FRAMES_ENEMY 10

volatile int frame = 0;

enum { CONTINUOUS, SINGLE } TouchType = CONTINUOUS;

void Vblank() {
	frame++;
}


//Player
typedef struct 
{
	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}Des;

void animateDeS(Des *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;

	u8* offset = sprite->frame_gfx + frame * 32*32;

	dmaCopy(offset, sprite->sprite_gfx_mem, 32*32);
}

void initDeS(Des *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	sprite->frame_gfx = (u8*)gfx;
}

//Enemy
typedef struct 
{
	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}Cartrage;

void animateCart(Cartrage *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION_ENEMY;

	u8* offset = sprite->frame_gfx + frame * 16*16;

	dmaCopy(offset, sprite->sprite_gfx_mem, 16*16);
}

void initCart(Cartrage *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	
	sprite->frame_gfx = (u8*)gfx;
}

//Collision Boxes
typedef struct
{
	int Xpos;
	int Ypos;

	int SizeX;
	int SizeY;
}box;

bool CollisionCheck(box r1, box r2){
	return(r1.Xpos < r2.Xpos + r2.SizeX && r1.Xpos + r1.SizeX > r2.Xpos && r1.Ypos < r2.Ypos + r2.SizeY && r1.Ypos + r1.SizeY > r2.Ypos);
}

//Animation States
enum SpriteState {W_JUMP = 0, W_RIGHT = 1, W_DEAD = 2, W_LEFT = 3};

//Enemy's X
int EnemyX = 256;
//Enemy's Y
int EnemyY = 112;
//Keeps track of how many delay frames have been done
int EnemyFramesDone = 0;

//Player's Health/Lives
int Health = 3;
//Where is the ground
int GroundPos = 100;
//How many frames you want between animation frames
int AnimFrames = 10;
//How many frames between animation frames are done
int AnimFramesDone = 0;
//How many frames will the player be in the air
int FramesInAir = 0;
//How many frames has the player been in the air
int FramesAirDone = 0;
//How much force does gravity have
int GravityForce = 2;
//How much force does the player have jumping
int JumpForce = 2;
//The player's Y position
int PlayerY = 64;
//The player's X position
int PlayerX = 0;
//The player's movement speed
int Speed = 2;
//How many frames you want the player to go up
int FramesToJump = 30;
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

	//Create Objects
	Des des = {0,0};
	Cartrage cart = {0,0};
	
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
	initDeS(&des, (u8*)DeSTiles);
	dmaCopy(DeSPal, &VRAM_F_EXT_SPR_PALETTE[0][0],DeSPalLen);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);

	//Set F bank again
	vramSetBankF(VRAM_F_LCD);
	//Enemy gfx
	initCart(&cart, (u8*)CartTiles);
	dmaCopy(CartPal, &VRAM_F_EXT_SPR_PALETTE[1][0],CartPalLen);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
		
	//Make the bottom screen a blue color
	setBackdropColorSub(5555000000009999);
	
	//Background
	int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);
	dmaCopy(StoreBitmap, bgGetGfxPtr(bg3), 256*192);
	dmaCopy(StorePal, BG_PALETTE, 256*2);
 

	//Loops every frame
	while(1) {

		swiWaitForVBlank();

		scanKeys();

		touchRead(&touch);
		
		int pressed = keysDown();
		int held = keysHeld();

		int FramesDone;

		if(Health > 0){
			EnemyX -= Speed;

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
		}
		
		


		//Collision Stuff
		PlayerBox.Xpos = PlayerX;
		PlayerBox.Ypos = PlayerY;

		EnemyBox.Xpos = EnemyX;
		EnemyBox.Ypos = EnemyY;
		
		bool hit;
		hit = false;
		hit = CollisionCheck(PlayerBox, EnemyBox);
		

		if(hit == true){
			Health -= 1;
			if(Health <= 0){
				des.state = W_DEAD;
			}
			else{
				EnemyX = 256;
			}
		}


		if(des.state == W_JUMP || AnimFramesDone >= AnimFrames){
			des.anim_frame++;
			AnimFramesDone = 0;
		}
		else{
			AnimFramesDone++;
		}

		if(des.anim_frame >= FRAMES_PER_ANIMATION) des.anim_frame = 0;

		if(EnemyFramesDone > FRAMES_BETWEEN_FRAMES_ENEMY){
			cart.anim_frame++;
			EnemyFramesDone = 0;
		}
		else{
			EnemyFramesDone++;
		}
		if(cart.anim_frame >= FRAMES_PER_ANIMATION_ENEMY) cart.anim_frame = 0;

		animateDeS(&des);
		animateCart(&cart);

		oamSet(&oamMain, 0, PlayerBox.Xpos, PlayerBox.Ypos, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
			des.sprite_gfx_mem, -1, false, false, false, false, false);

		oamSet(&oamMain, 1, EnemyBox.Xpos, EnemyBox.Ypos, 0, 1, SpriteSize_16x16, SpriteColorFormat_256Color, 
			cart.sprite_gfx_mem, -1, false, false, false, false, false);

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