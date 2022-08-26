#pragma once

namespace DSC
{
	class Scene
	{
	public:
		Scene() = default;				
		
		virtual void init() = 0;
		virtual void frame() = 0;
		
		__attribute__((noinline))
		virtual void run();
		
		virtual void on_key_down(int keys);
		virtual void on_key_held(int keys);
		virtual void on_key_up(int keys);		
		
		virtual ~Scene() = default;
	};
}