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
		iprintf(" Touch - Get coords");
		
		
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
		default: break;
	}
}

dsc_launch(Scene1);
