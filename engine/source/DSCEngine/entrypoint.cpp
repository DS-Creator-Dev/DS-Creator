#define DSC_INTERNAL
#include "DSC"

#include "entrypoint.hpp"
#include <nds.h>

using namespace DSC;

volatile int __entrypoint_r13;
volatile int __entrypoint_r14;
volatile int __entrypoint_r15;

int main()
{
	
	init_main_scene();
	
	__entrypoint_capture();
	
	while(__MAIN_SCENE__)
	{
		__MAIN_SCENE__->init();
		__MAIN_SCENE__->run();
	}	
	
	while(1) swiWaitForVBlank();
	return 0;
}