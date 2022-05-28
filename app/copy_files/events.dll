#include <stdio.h>
#include <nds.h>

//Animation Frame Variables
#define FRAMES_PER_ANIMATION 3
//Animation States
enum SpriteState {W_Walk_Up = 0, W_Walk_Down = 1, W_Walk_Right = 2, W_Walk_Left = 3};

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
bool CanMoveLeft = true;
bool CanMoveDown = true;
bool CanMoveRight = true;
bool CanMoveUp = true;
 
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

bool HitABox;

//Areas
bool inGrassland = true;
bool inDesert;
bool inBeach;
//Where the player is in the current area
int AreaGrassland = 1;
int AreaDesert;
int AreaBeach;
//Space || ONLY USE EVEN NUMBERS
int SpaceRoomChange = 2;

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

	int Size;
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

typedef struct
{
	int Area;
	/*
	0 = Grassland
	1 = Desert
	3 = Beach
	4 = ?
	5 = ?
	6 = ?
	7 = ?
	*/

	int Room;

	bool ExitDown;
	bool ExitLeft;
	bool ExitRight;
	bool ExitUp;
	/*
	true = can exit that way
	false = can not exit that way
	*/

	int roomToLeft;
	int roomToRight;
	int roomToUp;
	int roomToDown;
}Room;

//Rooms
Room GrassArea1;
Room GrassArea2;
Room GrassArea3;
Room GrassArea4;
Room GrassArea5;
Room GrassArea6;
Room GrassArea7;
Room GrassArea8;
Room GrassArea9;
Room GrassArea10;
Room GrassArea11;
Room GrassArea12;
Room GrassArea13;
Room GrassArea14;
Room GrassArea15;

//Room Collision
Box Grass1Box1;
Box Grass1Box2;
Box Grass1Box3;
Box Grass1Box4;
Box Grass1Box5;

Box Grass2Box1;
Box Grass2Box2;
Box Grass2Box3;
Box Grass2Box4;
Box Grass2Box5;
Box Grass2Box6;

//Events
void SetUpRoomBoxes(){
	int times = 8 * 3;
	//Grassland
	Grass1Box1.SizeX = 256;
	Grass1Box1.SizeY = times;
	Grass1Box2.Xpos = 256 - times;
	Grass1Box2.SizeX = times;
	Grass1Box2.SizeY = 192;
	Grass1Box3.SizeX = 8 * 24;
	Grass1Box3.SizeY = times;
	Grass1Box3.Ypos = 168;
	Grass1Box4.SizeX = times;
	Grass1Box4.SizeY = 8 * 9;
	Grass1Box5.SizeX = times;
	Grass1Box5.SizeY = 8 * 8;
	Grass1Box5.Ypos = 8 * 16;
	
	Grass2Box1.SizeX = 8 * 24;
	Grass2Box1.SizeY = 8 * 3;
	Grass2Box2.SizeX = 16;
	Grass2Box2.SizeY = 256;
}

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

void SetUpRooms(void){
	//Grassland
	GrassArea1.Room = 1;
	GrassArea1.ExitDown = true;
	GrassArea1.ExitLeft = true;
	GrassArea1.roomToDown = 2;
	GrassArea1.roomToLeft = 0;

	GrassArea2.Room = 2;
	GrassArea2.ExitDown = true;
	GrassArea2.ExitUp = true;
	GrassArea2.ExitRight = true;
	GrassArea2.roomToDown = 3;
	GrassArea2.roomToUp = 1;
	GrassArea2.roomToRight = 4;
	
	GrassArea3.Room = 3;
	GrassArea3.ExitDown = true;
	GrassArea3.ExitUp = true;
	GrassArea3.roomToDown = 5;
	GrassArea3.roomToUp = 2;
	
	GrassArea4.Room = 4;
	GrassArea4.ExitUp = true;
	GrassArea4.ExitLeft = true;
	GrassArea4.roomToUp = 10;
	GrassArea4.roomToLeft = 2;
	
	GrassArea5.Room = 5;
	GrassArea5.ExitUp = true;
	GrassArea5.ExitRight = true;
	GrassArea5.roomToUp = 3;
	GrassArea5.roomToRight = 6;
	
	GrassArea6.Room = 6;
	GrassArea6.ExitDown = true;
	GrassArea6.ExitLeft = true;
	GrassArea6.ExitRight = true;
	GrassArea6.roomToLeft = 5;
	GrassArea6.roomToDown = 7;
	GrassArea6.roomToRight = 9;
	
	GrassArea7.Room = 7;
	GrassArea7.ExitDown = true;
	GrassArea7.ExitUp = true;
	GrassArea7.roomToUp = 6;
	GrassArea7.roomToDown = 8;
	
	GrassArea8.Room = 8;
	GrassArea8.ExitUp = true;
	GrassArea8.roomToUp = 7;
	
	GrassArea9.Room = 9;
	GrassArea9.ExitLeft = true;
	GrassArea9.roomToLeft = 6;
	
	GrassArea10.Room = 10;
	GrassArea10.ExitDown = true;
	GrassArea10.ExitRight = true;
	GrassArea10.roomToDown = 4;
	GrassArea10.roomToRight = 11;
	
	GrassArea11.Room = 11;
	GrassArea11.ExitDown = true;
	GrassArea11.ExitLeft = true;
	GrassArea11.roomToDown = 12;
	GrassArea11.roomToLeft = 10;
	
	GrassArea12.Room = 12;
	GrassArea12.ExitDown = true;
	GrassArea12.ExitUp = true;
	GrassArea12.roomToDown = 13;
	GrassArea12.roomToUp = 11;
	
	GrassArea13.Room = 13;
	GrassArea13.ExitUp = true;
	GrassArea13.ExitRight = true;
	GrassArea13.roomToUp = 12;
	GrassArea13.roomToRight = 14;
	
	GrassArea14.Room = 14;
	GrassArea14.ExitDown = true;
	GrassArea14.ExitLeft = true;
	GrassArea14.roomToLeft = 13;
	GrassArea14.roomToDown = 15;
	
	GrassArea15.Room = 15;
	GrassArea15.ExitUp = true;
	GrassArea15.ExitRight = true;
	GrassArea15.roomToUp = 14;
	GrassArea15.roomToRight = 0;
}

Sprite ChangeScene(Sprite player, Room room){
	if(player.Xpos == -16){
		if(room.ExitLeft){
			player.Xpos = 256 - 16 - SpaceRoomChange; //40, 26
			AreaGrassland = room.roomToLeft;
		}
	}
	else if(player.Xpos == 256){
		if(room.ExitRight){
			player.Xpos = 0;
			AreaGrassland = room.roomToRight;
		}
	}
	if(player.Ypos == -16){
		if(room.ExitUp){
			player.Ypos = 192 - 16; //24
			AreaGrassland = room.roomToUp;
		}
	}
	else if(player.Ypos == 192){
		if(room.ExitDown){
			player.Ypos = 0;
			AreaGrassland = room.roomToDown;
		}
	}

	return player;
}

Sprite WallCollisionType1(bool hit, Sprite Player, Box WallBox){
	if(hit){
		if(Player.Ypos < WallBox.Ypos + 10){
			Player.Ypos -= 2;
		}
		else if(Player.Ypos > WallBox.Ypos + WallBox.SizeY - 10){
			Player.Ypos += 2;
		}
		else{
			if(Player.Xpos < WallBox.Xpos + 10){
				Player.Xpos -= 2;
			}
			else if(Player.Xpos > WallBox.Xpos + WallBox.SizeX - 10){
				Player.Xpos += 2;
			}
		}
	}

	return Player;
}

Sprite WallCollisionType2(bool hit, Sprite Player, Box WallBox){
	if(hit){				
		if(Player.Xpos < Grass1Box3.Xpos + 10){
			Player.Xpos -= 2;
		}
		else if(Player.Xpos > Grass1Box3.Xpos + Grass1Box3.SizeX - 10){
			Player.Xpos += 2;
		}
		else{
			if(Player.Ypos < Grass1Box3.Ypos + 10){
				Player.Ypos -= 2;
			}
			else if(Player.Ypos > Grass1Box3.Ypos + Grass1Box3.SizeY - 10){
				Player.Ypos += 2;
			}
		}
	}

	return Player;
}