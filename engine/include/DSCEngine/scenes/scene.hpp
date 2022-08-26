#pragma once

#include "DSCEngine/events/event.hpp"

namespace DSC
{
	class Scene
	{
	public:
		Scene() = default;				
		
		virtual void init();
		virtual void frame();
		
		__attribute__((noinline))
		virtual void run();		
				
		
		Event key_down;
		Event key_held;
		Event key_up;	
		
		virtual ~Scene() = default;
	};
}