/*!
 * \file event.hpp
 */

#pragma once

#include "DSCEngine/types/vector.hpp"

namespace DSC
{
	/*!
	 * \brief Function type to be execute when event fires
	 *
	 *
	 */
	typedef void (*EventHandler)(void*, void*);
	
	/*!
	 * \brief Class responsible with event registration and execution
	 *
	 *
	 */
	class Event
	{
	private:
		Vector<EventHandler> actions;
		
	public:
		/*!
		 * \brief Creates a new Event instance
		 */		 
		Event();
		
		/*!
		 * \brief Adds a new event handler to this event
		 * \param [in] e event handler
		 * \returns this Event instance
		 */		
		Event& operator += (const EventHandler& e);
		
		/*!
		 * \brief Removes an event handler from this event
		 * \param [in] e event handler
		 * \returns this Event instance
		 */
		Event& operator -= (const EventHandler& e);
		
		/*!
		 * \brief Fires the event
		 * \param [in] sender the object which fires the event
		 * \param [in] event args (can be anything)
		 */
		void trigger(void* sender, void* args) const;		
	};
}