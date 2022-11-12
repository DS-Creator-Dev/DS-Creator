#include <DSC>

using namespace DSC;

void test_that_passes()
{
	nds_assert(2+2==4);
}

void test_that_passes_with_fatal_expected()
{
	nds_assert(2+2==5);
}

void test_that_fails()
{
	nds_assert(0==1);
}

void DSC::testmod_init()
{
	testmod_register(test_that_passes);
	testmod_register(test_that_passes_with_fatal_expected, true);
	testmod_register(test_that_fails);
}