#include <stdio.h>
#include <nds.h>

//Animation Frame Variables
#define FRAMES_PER_ANIMATION 4
//Animation States
enum SpriteState {W_JUMP = 0, W_RIGHT = 1, W_DEAD = 2, W_LEFT = 3};

//Keeps track of how many delay frames have been done
int EnemyFramesDone = 0;

//Player's Battle X Position
int BattlePlayerX = 20;
//Player's Battle Y Position
int BattlePlayerY = 90;

//Player's Health/Lives
int Health = 3;
//Is th the player flipped?
bool PlayerFlipped = false;
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
	int Xpos;
	int Ypos;

	int AnimationFrames;

	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;

	int Health;
}Sprite;

typedef struct
{
	int Xpos;
	int Ypos;

	int SizeX;
	int SizeY;

	int OffsetX;
	int OffsetY;
}Box;

//Events
Sprite Gravity(Sprite object){
	object.Ypos += GravityForce;

	return object;
}

Sprite AntiGravity(Sprite object){
	FramesJumpDone++;
	object.Ypos -= JumpForce;
	if(FramesJumpDone >= FramesToJump){
		FramesJumpDone = 0;
		PlayerJumpState = 4;
	}

	return object;
}

void InAir(){
	FramesAirDone++;
	if(FramesAirDone < FramesInAir){

	}
	else{
		PlayerJumpState = 0;
	}
}

Sprite MoveActor(int Xpos, int Ypos, Sprite object){
	bool Go_Right;
	bool Go_Left;
	bool Go_Up;
	bool Go_Down;

	Go_Right = false;
	Go_Left = false;
	Go_Up = false;
	Go_Down = false;
	
	if(object.Xpos < Xpos){
		Go_Right = true;
	}
	else if(object.Xpos > Xpos){
		Go_Left = true;
	}

	if(object.Ypos < Ypos){
		Go_Down = true;
	}
	else if(object.Ypos > Ypos){
		Go_Up = true;
	}

	if(Go_Right){
		object.Xpos++;
	}
	else if(Go_Left){
		object.Xpos--;
	}

	if(Go_Down){
		object.Ypos++;
	}
	else if(Go_Up){
		object.Ypos--;
	}

	return object;
}

Sprite PlayerTurnAction(Sprite enemy, Box enemyBox, int pressed, Sprite objectMoving){
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
				objectMoving = MoveActor(enemy.Xpos - enemyBox.OffsetX, BattlePlayerY, objectMoving);
			}
		
			if(objectMoving.Xpos == enemy.Xpos - enemyBox.OffsetX){
				DoneMove = true;
			}

			if(DoneMove){
				objectMoving = MoveActor(BattlePlayerX, BattlePlayerY, objectMoving);
			}

			if(objectMoving.Xpos == BattlePlayerX & objectMoving.Ypos == BattlePlayerY){
				if(enemy.Health <= 0){
					enemy.Health = 5;
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

	return objectMoving;
}

Sprite EnemyTurnAction(int pressed, Sprite This, Sprite Player, Box playerBox){

	if(!DoneMove){
		This = MoveActor(Player.Xpos, This.Ypos, This);
	}
		
	if(This.Xpos == Player.Xpos + playerBox.OffsetX){
		Health--;
		DoneMove = true;
	}

	if(DoneMove){
		This = MoveActor(200, This.Ypos, This);
	}

	if(This.Xpos == 200){
		if(Health <= 0){
			Player.Ypos = 10;
			Health = 3;
			This.Health = 5;
			Battle = false;
		}
		else{
			PlayerTurn = true;
		}

	}

	return This;
}


void animate64(Sprite *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;

	u8* offset = sprite->frame_gfx + frame * 64*64;

	dmaCopy(offset, sprite->sprite_gfx_mem, 64*64);
}

void init64(Sprite *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);
	
	sprite->frame_gfx = (u8*)gfx;
}

void animate32(Sprite *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;

	u8* offset = sprite->frame_gfx + frame * 32*32;

	dmaCopy(offset, sprite->sprite_gfx_mem, 32*32);
}

void init32(Sprite *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	sprite->frame_gfx = (u8*)gfx;
}

void animate16(Sprite *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;

	u8* offset = sprite->frame_gfx + frame * 16*16;

	dmaCopy(offset, sprite->sprite_gfx_mem, 16*16);
}

void init16(Sprite *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	
	sprite->frame_gfx = (u8*)gfx;
}

void animate8(Sprite *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;

	u8* offset = sprite->frame_gfx + frame * 8*8;

	dmaCopy(offset, sprite->sprite_gfx_mem, 8*8);
}

void init8(Sprite *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_8x8, SpriteColorFormat_256Color);
	
	sprite->frame_gfx = (u8*)gfx;
}

bool CollisionCheck(Box r1, Box r2){
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

Sprite HurtEnemy(Sprite enemy, int damage){
	enemy.Health -= damage;

	return enemy;
}