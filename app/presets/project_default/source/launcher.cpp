#include <DSC>
#include <nds.h>
#include <stdio.h>

class DummyScene : public DSC::Scene
{
	void init() override
	{
		consoleDemoInit();
		iprintf("Hello world from DSC!\n");
	}
};

dsc_launch(@{STARTUP_SCENE});