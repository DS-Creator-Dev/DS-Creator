#include <DSC>
#include <nds.h>
#include <stdio.h>

using namespace DSC;

int frameWait = 0;
bool PressKey = false;
bool doneWithYou = false;

class PlayerSelectRoom : public Scene
{
public:
	void init() override
	{		
		consoleDemoInit();		

		iprintf("\nMy DSC Engine Lib Game.\n");
		iprintf("I have no idea what I'm doing.\n");
		iprintf("It's a great time to learn C++\n");
		iprintf("Just press some buttons.\n");
		iprintf("See what happens... :)\n");		
		
		key_down += key_down_hanlder;
	}
	void frame() override
	{
		if(PressKey == false){
			frameWait++;
			if(frameWait == 500){
				iprintf("Why haven't you pressed anything yet?\n");
			}
			else if(frameWait == 1000){
				iprintf("PRESS BUTTONS!\n");
			}
			else if(frameWait == 1500){
				iprintf("...\n");
			}
			else if(frameWait == 2000){
				iprintf("bruh...\n");
				doneWithYou = true;
			}
		}	
		
		key_down += key_down_hanlder;
	}
	
	static void key_down_hanlder(void* sender, void* _keys);
};

void PlayerSelectRoom::key_down_hanlder(void* sender, void* _keys)
{
	switch((const int)_keys)
	{
		case KEY_A:
		{
			if(doneWithYou == true && PressKey == false){
				iprintf("No. I don't want to talk to you.");
				PressKey = true;
			}
			else if(PressKey == false) iprintf("Thank you!\n");
			PressKey = true;
			break;
		}
		case KEY_B:
		{
			if(doneWithYou == true && PressKey == false){
				iprintf("No. I don't want to talk to you.");
				PressKey = true;
			}
			else if(PressKey == false) iprintf("Thank you!\n");
			PressKey = true;
			break;
		}
		case KEY_X:
		{
			if(doneWithYou == true && PressKey == false){
				iprintf("No. I don't want to talk to you.");
				PressKey = true;
			}
			else if(PressKey == false) iprintf("Thank you!\n");
			PressKey = true;
			break;
		}
		case KEY_Y:
		{
			if(doneWithYou == true && PressKey == false){
				iprintf("No. I don't want to talk to you.");
				PressKey = true;
			}
			else if(PressKey == false) iprintf("Thank you!\n");
			PressKey = true;
			break;
		}
		case KEY_TOUCH:
		{
			if(doneWithYou == true && PressKey == false){
				iprintf("No. I don't want to talk to you.");
				PressKey = true;
			}
			else if(PressKey == false) iprintf("Thank you!\n");
			PressKey = true;
			break;
		}
		case KEY_L:
		{
			if(doneWithYou == true && PressKey == false){
				iprintf("No. I don't want to talk to you.");
				PressKey = true;
			}
			else if(PressKey == false) iprintf("Thank you!\n");
			PressKey = true;
			break;
		}
		case KEY_R:
		{
			if(doneWithYou == true && PressKey == false){
				iprintf("No. I don't want to talk to you.");
				PressKey = true;
			}
			else if(PressKey == false) iprintf("Thank you!\n");
			PressKey = true;
			break;
		}
		case KEY_START:
		{
			if(doneWithYou == true && PressKey == false){
				iprintf("No. I don't want to talk to you.");
				PressKey = true;
			}
			else if(PressKey == false) iprintf("Thank you!\n");
			PressKey = true;
			break;
		}
		case KEY_SELECT:
		{
			if(doneWithYou == true && PressKey == false){
				iprintf("No. I don't want to talk to you.");
				PressKey = true;
			}
			else if(PressKey == false) iprintf("Thank you!\n");
			PressKey = true;
			break;
		}
		default: break;
	}
}

dsc_launch(PlayerSelectRoom);