#include <nds.h>
#include <stdio.h>
#include <DSC>

using namespace DSC;

class Scene1 : public Scene
{
public:
	void init() override
	{		
		consoleDemoInit();		
	
		iprintf("\n DSC Debug Utility Test \n");
		iprintf(" Press a key to send debug\n messages:\n\n");
		iprintf(" A     - assert(1<2);\n");
		iprintf(" B     - assert(2+2==5);\n");
				
		
		key_down += key_down_hanlder;
	}
	
	static void key_down_hanlder(void* sender, void* _keys);
};

void Scene1::key_down_hanlder(void* sender, void* _keys)
{
	Debug::log("Key down detected");
	switch((const int)_keys)
	{
		case KEY_A: nds_assert(1<2); break;		
		case KEY_B: nds_assert(2+2==5); break;		
		default: break;
	}	
}

dsc_launch(Scene1);
