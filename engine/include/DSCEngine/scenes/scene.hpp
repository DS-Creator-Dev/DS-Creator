#pragma once

#include "DSCEngine/events/event.hpp"

namespace DSC
{
	struct SceneCom;
	
	class Scene
	{
	public:
		Scene() = default;				
		
		SceneCom* close();
		
		virtual void init();
		virtual void frame();
		
		__attribute__((noinline))		
		virtual void run();		
						
		Event key_down;
		Event key_held;
		Event key_up;	
		
		virtual ~Scene() = default;
	};
	
	struct SceneCom
	{							
		void next(Scene* new_scene);		
	};	
		
	
	extern Scene* __MAIN_SCENE__;	
	
	extern void init_main_scene();
	
	#ifdef DSC_INTERNAL	
	extern SceneCom __SceneComInstance__;	
	#endif
}

#define dsc_launch(scene_t,...) void DSC::init_main_scene(){DSC::__MAIN_SCENE__=new scene_t(__VA_ARGS__);}