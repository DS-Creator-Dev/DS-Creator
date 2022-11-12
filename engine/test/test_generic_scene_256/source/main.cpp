#include <DSC>
#include "roa_magma_texture8.h"

using namespace DSC;

class Scene1 : public GenericScene256
{
public:
	void init() override
	{				
		GenericScene256::init();
		
		require_bitmap(MAIN_BG3, &ROA_magma_texture8);
	}	
	
	void frame() override
	{
		
	}	
};

dsc_launch(Scene1);
