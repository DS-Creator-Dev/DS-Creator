#pragma once

#include "DSCEngine/types/vector.hpp"

namespace DSC
{
	typedef void (*EventHandler)(void*, void*);
	
	class Event
	{
	private:
		Vector<EventHandler> actions;
		
	public:
		Event();
		Event& operator += (const EventHandler& e);
		Event& operator -= (const EventHandler& e);
		void trigger(void*, void*) const;		
	};
}