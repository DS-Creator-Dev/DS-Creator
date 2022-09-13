#include <DSC>
#include <nds.h>
#include <stdio.h>

class DummyScene : public DSC::Scene
{
	void init() override
	{
		consoleDemoInit();
		iprintf("Hello world from DSC!\n");
		Debug::log("hi");
	}
};

dsc_launch(DummyScene);