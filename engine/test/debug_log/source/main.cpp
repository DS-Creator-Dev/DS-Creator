#include <DSC>
#include <nds.h>
#include <stdio.h>

using namespace DSC;

class Scene1 : public Scene
{
public:
	void init() override
	{		
		consoleDemoInit();		
	
		iprintf("\n DSC Debug Utility Test \n");
		iprintf(" Press a key to send debug\n messages:\n\n");
		iprintf(" A     - Beep!\n");
		iprintf(" B     - Boop!\n");
		iprintf(" X     - Ping!\n");
		iprintf(" Y     - Pong!\n");
		iprintf(" Touch - Get coords\n");
		iprintf(" L     - Warning\n");
		iprintf(" R     - Error\n");
		
		
		key_down += key_down_hanlder;
	}
	
	static void key_down_hanlder(void* sender, void* _keys);
};

void Scene1::key_down_hanlder(void* sender, void* _keys)
{
	switch((const int)_keys)
	{
		case KEY_A: Debug::log("Beep!"); break;
		case KEY_B: Debug::log("Boop!"); break;
		case KEY_X: Debug::log("Ping!"); break;
		case KEY_Y: Debug::log("Pong!"); break;
		case KEY_TOUCH:
		{
			touchPosition touch;
			touchRead(&touch);
			
			Debug::log("Touch at %i %i", touch.px, touch.py);
			break;
		}
		case KEY_L: Debug::warn("This is a warning!"); break;
		case KEY_R: Debug::error("This is an error!"); break;
		default: break;
	}
}

dsc_launch(Scene1);
