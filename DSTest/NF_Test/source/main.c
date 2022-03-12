#include <stdio.h>
#include <nds.h>
#include <string.h>
#include <nf_lib.h>

void initOAM(void) {
	int i;

	for(i = 0; i < 128; i++) {
		//OAMCopy[i].attribute[0] = ATTR0_DISABLED;
	}	
}

void updateOAM(void) {
	//memcpy(OAM, OAMCopy, 128 * sizeof(SpriteEntry));
}


volatile int frame = 0;

enum { CONTINUOUS, SINGLE } TouchType = CONTINUOUS;

void Vblank() {
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
	//Set Up Night Fox's Lib
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);	
	consoleDemoInit();

	NF_SetRootFolder("nitrofiles");

	NF_Set2D(0, 0);
	NF_Set2D(1, 0);	

	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	NF_InitSpriteSys(1);

	NF_LoadSpriteGfx("sprite/personaje", 0, 64, 64);
	NF_LoadSpritePal("sprite/personaje", 0);

	NF_VramSpriteGfx(1, 0, 0, false);
	NF_VramSpritePal(1, 0, 0);

	srand(time(NULL));

	NF_CreateSprite( 
		1,
		0,
		0,
		0,
		0,
		0
	);


	touchPosition touch;

	initOAM();

 
	while(1) {

		swiWaitForVBlank();
		updateOAM();

		scanKeys();

		touchRead(&touch);
		
		int pressed = keysDown();
		int held = keysHeld();

		int FramesDone;

		//Jumping
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