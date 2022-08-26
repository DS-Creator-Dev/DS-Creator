#include "DSCEngine/scenes/scene.hpp"

#include <nds.h>

void DSC::Scene::init() { }

void DSC::Scene::frame() { }

__attribute__((noinline))
void DSC::Scene::run()
{
	while(1)
	{
		swiWaitForVBlank();
				
		scanKeys();		
		
		int keys_down_vals = keysDown();
		if(keys_down_vals)
		{
			key_down.trigger(this, (void*)keys_down_vals);
		}
		
		int keys_held_vals = keysHeld();
		if(keys_held_vals)
		{
			key_held.trigger(this, (void*)keys_held_vals);
		}
		
		int keys_up_vals = keysUp();
		if(keys_up_vals)
		{
			key_up.trigger(this, (void*)keys_up_vals);
		}	
		
		frame();		
	}	
}
