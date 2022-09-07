#pragma once

namespace DSC::Debug
{		
	__attribute__((target("thumb"))) void log(const char* message, ...);
}