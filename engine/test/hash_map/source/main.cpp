#include <nds.h>
#include <stdio.h>
#include <DSC>

using namespace DSC;

class Scene1 : public Scene
{
private:
	static int hash_function(const int& x) {return x%64;}
	HashMap<int, int, hash_function, 64> hm;
public:
	void init() override
	{		
		consoleDemoInit();			
		iprintf("\n DSC HashMap test \n");								
					
		iprintf("Adding keys\n");
		add_key(1,2);
		add_key(2,5);
		add_key(3,7);		
		add_key(2,8);		
		add_key(105,10);
		
		iprintf("Accessing keys\n");
		nds_assert(hm[1]==2);
		nds_assert(hm[2]==8);
		nds_assert(hm[3]==7);
		
		iprintf("Removing keys\n");
		remove_key(1); 
		nds_assert(!hm.contains_key(1));
		remove_key(105); 
		nds_assert(!hm.contains_key(105));		
				
		iprintf("OK\n\n");
				
		last_test();						
	}
	
	void last_test() const
	{
		iprintf("The program should terminate with an error attempting to access an inexistent key in the const context\n");
		
		if(hm[420]==0)
			iprintf("Failed\n");
	}
	
	void add_key(int k, int v)
	{
		iprintf("Ading k=%i, v=%i\n",k,v);
		if(hm.contains_key(k))
		{
			Debug::log("For key %i, modifying value from %i to %i", k, hm[k], v);
			hm[k] = v;
		}
		else 
		{
			Debug::log("Creating key %i with value %i", k, v);
			hm[k] = v;
		}
	}
		
		
	void remove_key(int k)
	{
		iprintf("Removing key %i\n",k);
		hm.remove_key(k);		
	}
};

dsc_launch(Scene1);
