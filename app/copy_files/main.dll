#include <nds.h>
#include <maxmod9.h>
#include <stdio.h>

int main() {

	consoleDemoInit();

	while(1){

		int keys_pressed, keys_released;
		
		swiWaitForVBlank();
		scanKeys();

		keys_pressed = keysDown();
		keys_released = keysUp();

		if ( keys_pressed & KEY_A ) {
			printf("A");
		}
		else if ( keys_pressed & KEY_B ) {
			printf("B");
		}
		else if ( keys_pressed & KEY_Y ) {
			printf("Y");
		}
		else if ( keys_pressed & KEY_X ) {
			printf("X");
		}
		else if ( keys_pressed & KEY_L ) {
			printf("L");
		}
		else if ( keys_pressed & KEY_R ) {
			printf("R");
		}
		else if ( keys_pressed & KEY_RIGHT ) {
			printf("RIGHT");
		}
		else if ( keys_pressed & KEY_LEFT ) {
			printf("LEFT");
		}
		else if ( keys_pressed & KEY_UP ) {
			printf("UP");
		}
		else if ( keys_pressed & KEY_DOWN ) {
			printf("DOWN");
		}
		else if ( keys_pressed & KEY_START ) {
			printf("START");
		}
		else if ( keys_pressed & KEY_SELECT ) {
			printf("SELECT");
		}
		else if ( keys_pressed & KEY_TOUCH ) {
			printf("TOUCH");
		}
	}
	return 0;
}
