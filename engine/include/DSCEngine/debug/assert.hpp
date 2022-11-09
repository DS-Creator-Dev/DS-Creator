#pragma once

// calling it nds_assert to differentiate it from stdlib's assert
#define nds_assert(expr) DSC::__assert__(expr, #expr)

namespace DSC
{
	void __assert__(bool condition, const char* message);
}