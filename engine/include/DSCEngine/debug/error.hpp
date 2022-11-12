#pragma once

#include "DSCEngine/debug/log.hpp"
#include "DSCEngine/testmod.hpp"

#include <nds.h>

namespace DSC
{
	/*! \brief Stops execution with a fatal error
		See DSC::Debug::log() for more details
	 */	
	template<typename... Args> void fatal(const char* message, Args... args)
	{		
		DSC::Debug::error(message, args...);
		DSC::Debug::log("The execution stopped");
		
		if(!IS_TESTMOD)
		{
			while(1)
			{
				swiWaitForVBlank();
			}
		}		
		else
		{
			testmod_fatal_raise();
			testmod_return();
		}		
	}
}