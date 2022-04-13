#include <stdio.h>
#include <nds.h>

//Animation Frame Variables
#define FRAMES_PER_ANIMATION 2
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
 
int BackgroundX = 0;
int BackgroundY = 0;

bool PlayerTurn = false;
bool Battle = false;

int EnemyHealth = 5;
bool playerAction = false;
bool enemyAction = false;
bool DoneMove = false;

int ActionType = 0;
/*
0 = Attack
1 = Heal
*/

//Objects
typedef struct 
{
	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}Sprite32;

typedef struct 
{
	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}Sprite16;

typedef struct 
{
	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}Sprite8;

typedef struct
{
	int Xpos;
	int Ypos;

	int SizeX;
	int SizeY;
}box;

//Events
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

void MoveActor(int Xpos, int Ypos, bool isPlayer){
	bool Go_Right;
	bool Go_Left;
	bool Go_Up;
	bool Go_Down;

	Go_Right = false;
	Go_Left = false;
	Go_Up = false;
	Go_Down = false;
	
	if(isPlayer){
		if(PlayerX < Xpos){
			Go_Right = true;
		}
		else if(PlayerX > Xpos){
			Go_Left = true;
		}

		if(PlayerY < Ypos){
			Go_Down = true;
		}
		else if(PlayerY > Ypos){
			Go_Up = true;
		}

		if(Go_Right){
			PlayerX++;
		}
		else if(Go_Left){
			PlayerX--;
		}

		if(Go_Down){
			PlayerY++;
		}
		else if(Go_Up){
			PlayerY--;
		}
	}
	else{
		if(EnemyX < Xpos){
			Go_Right = true;
		}
		else if(EnemyX > Xpos){
			Go_Left = true;
		}

		if(EnemyY < Ypos){
			Go_Down = true;
		}
		else if(EnemyY > Ypos){
			Go_Up = true;
		}

		if(Go_Right){
			EnemyX++;
		}
		else if(Go_Left){
			EnemyX--;
		}

		if(Go_Down){
			EnemyY++;
		}
		else if(Go_Up){
			EnemyY--;
		}
	}
}

void PlayerTurnAction(int health, int pressed){
	if(playerAction == false){
		if(pressed & KEY_A){
			playerAction = true;
			DoneMove = false;
		}
		else if(pressed & KEY_LEFT){
			if(ActionType == 0){
				ActionType = 1;
			}
			else if(ActionType == 1){
				ActionType = 0;
			}
		}
		else if(pressed & KEY_RIGHT){
			if(ActionType == 0){
				ActionType = 1;
			}
			else if(ActionType == 1){
				ActionType = 0;
			}
		}
	}

	if(playerAction){
		if(ActionType == 0){
			if(!DoneMove){
				MoveActor(EnemyX, 100, true);
			}
		
			if(PlayerX == EnemyX){
				EnemyHealth--;
				DoneMove = true;
			}

			if(DoneMove){
				MoveActor(20, 100, true);
			}

			if(PlayerX == 20 & PlayerY == 100){
				if(EnemyHealth <= 0){
					EnemyHealth = 5;
					Battle = false;
				}
				else{
					enemyAction = true;
				}

				PlayerTurn = false;
				playerAction = false;
				DoneMove = false;
			
			}
		}
		else if(ActionType == 1){
			Health += 3;
			PlayerTurn = false;
			playerAction = false;
			DoneMove = false;
			enemyAction = true;
		}
	}
}

void EnemyTurnAction(int health, int pressed){
	if(enemyAction){
		if(!DoneMove){
			MoveActor(PlayerX, 112, false);
		}
		
		if(EnemyX == PlayerX){
			Health--;
			DoneMove = true;
		}

		if(DoneMove){
			MoveActor(200, 112, false);
		}

		if(EnemyX == 200 & EnemyY == 112){
			if(Health <= 0){
				PlayerY = 10;
				Health = 3;
				EnemyHealth = 5;
				Battle = false;
			}
			else{
				PlayerTurn = true;
			}

			enemyAction = false;
		}
	}
}

void animate32(Sprite32 *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;

	u8* offset = sprite->frame_gfx + frame * 32*32;

	dmaCopy(offset, sprite->sprite_gfx_mem, 32*32);
}

void init32(Sprite32 *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	sprite->frame_gfx = (u8*)gfx;
}

void animate16(Sprite16 *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;

	u8* offset = sprite->frame_gfx + frame * 16*16;

	dmaCopy(offset, sprite->sprite_gfx_mem, 16*16);
}

void init16(Sprite16 *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	
	sprite->frame_gfx = (u8*)gfx;
}

void animate8(Sprite8 *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;

	u8* offset = sprite->frame_gfx + frame * 8*8;

	dmaCopy(offset, sprite->sprite_gfx_mem, 8*8);
}

void init8(Sprite8 *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_8x8, SpriteColorFormat_256Color);
	
	sprite->frame_gfx = (u8*)gfx;
}

bool CollisionCheck(box r1, box r2){
	return(r1.Xpos < r2.Xpos + r2.SizeX && r1.Xpos + r1.SizeX > r2.Xpos && r1.Ypos < r2.Ypos + r2.SizeY && r1.Ypos + r1.SizeY > r2.Ypos);
}

void ScrollBackground(int BackgroundId, int BackgroundWidth, int BackgroundHeight, int X, int Y, bool ScrollWithDPad){
	int keys;

	if(ScrollWithDPad){
		keys = keysHeld();

      	if(keys & KEY_UP) X--;
      	if(keys & KEY_DOWN) X++;
      	if(keys & KEY_LEFT) X--;
      	if(keys & KEY_RIGHT) X++;

      	if(X < 0) X = 0;
      	if(X >= BackgroundWidth - 256) X = BackgroundWidth - 1 - 256;
      	if(Y < 0) Y = 0;
      	if(Y >= BackgroundHeight - 192) Y = BackgroundHeight - 1 - 192;

      	swiWaitForVBlank();

      	bgSetScroll(BackgroundId, X, Y);

	  	bgUpdate();
	}
	else{

	}
}