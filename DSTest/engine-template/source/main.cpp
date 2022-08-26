#include <nds.h>
#include <stdio.h>
#include <test.h>

#include <DSC>

using namespace DSC;

void on_key_press_1(void*, void*)
{
	iprintf("Action 1\n");
}

void on_key_press_2(void*, void*)
{
	iprintf("Action 2\n");
}

int main(void) 
{
	consoleDemoInit();
	
	iprintf("%i\n", f());
	
	Vector<int> v;
	v.clear();
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	
	Event key_pressed_ev;
	key_pressed_ev += on_key_press_1;
	key_pressed_ev += on_key_press_2;
	
	int 
		
	for(int i=0;i<v.size();i++)
		iprintf("%i ", v[i]);
	
	while(1) 
	{
		swiWaitForVBlank();				
		scanKeys();
		if(keysDown()!=0)
		{
			key_pressed_ev.trigger(nullptr, nullptr);
		}
	}

}
