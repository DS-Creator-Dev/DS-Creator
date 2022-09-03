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
	
		iprintf("This is Scene 1\n");
		
		key_down += key_down_hanlder;
	}
	
	static void key_down_hanlder(void* sender, void* _keys);
};

class Scene2 : public Scene
{
public:
	void init() override
	{
		consoleDemoInit();		
	
		iprintf("This is Scene 2\n");
		
		key_down += key_down_hanlder;
	}
	
	static void key_down_hanlder(void* sender, void* _keys);
};

void Scene1::key_down_hanlder(void* sender, void* _keys)
{
	reinterpret_cast<Scene*>(sender)->close()->next(new Scene2());
}

void Scene2::key_down_hanlder(void* sender, void* _keys)
{
	reinterpret_cast<Scene*>(sender)->close()->next(new Scene1());
}

dsc_launch(Scene1);
