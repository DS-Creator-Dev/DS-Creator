#include "DSCEngine/events/event.hpp"

DSC::Event::Event()
{
	actions.clear();
}

DSC::Event& DSC::Event::operator += (const EventHandler& e)
{
	actions.push_back(e);
	return *this;
}

DSC::Event& DSC::Event::operator -= (const EventHandler& e)
{
	actions.remove(e);
	return *this;
}

void DSC::Event::trigger(void* sender, void* event_args) const
{
	for(int i=0;i<actions.size();i++)
		actions[i](sender, event_args);
}

