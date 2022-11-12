# About DSC Test Modules

A test module is a type of ROM compiled with DSCEngine that does not adhere to the usual Scene model. Instead, it 
executes a bunch of predefined functions and tells for each function whether it has passed or has failed.

A function fails when it raises a fatal error (a type of error that would block the entire execution under normal circumstances).
It is possible to specify that the function _must_ throw a fatal so therefore it would fail if it exists with no error.

## Compiling a test module

First, we need a special TESTMOD build of DSC Engine. We can obtain that by following these steps:

- `cd /path/to/engine`
- `set_build testmod # config Makefile for TESTMOD build`
- `make clean & make # each make command after this will compile as TESTMOD`

The operation succeeds if a message saying "TESTMOD activated" is displayed. 
To compile the normal version of DSC, use these commands:

- `set_build normal # config Makefile for NORMAL build`
- `make clean & make # continue compiling the usual Scene model build`

Compiling the TESTMOD build produces a new `libdscengine_testmod.a` static library. 

**IMPORTANT! `libdscengine.a` AND `libdscengine_testmod.a` ARE NOT INTERCHANGEABLE.**

Then, return to this testmod template and `make` it. (Adjust `%LIBDSC%` path if necessary.)

## DSC Test Module file structure

```C++
#include <DSC>

using namespace DSC;

// each test function is a void() without arguments
void test_that_passes()
{
	nds_assert(2+2==4);
}

void test_that_passes_with_fatal_expected()
{
	nds_assert(2+2==5); // this raises a fatal error if the condition is false
}

void test_that_fails()
{
	nds_assert(0==1);
}

void DSC::testmod_init() // mandatory! can't compile without this
{
    // we need to register the test functions
	testmod_register(test_that_passes);
	testmod_register(test_that_passes_with_fatal_expected, /*expects_fatal = */ true);
	testmod_register(test_that_fails);
}
```

After running the NDS file, the results are shown in the emulator's console.

```
[EMU|LOG] << This is a DSC Test Module
[EMU|LOG] << -------------------------------
[EMU|LOG] << # Passed "test_that_passes" (1)
[EMU|ERR] << Assertion failed : 2+2==5
[EMU|LOG] << The execution stopped
[EMU|LOG] << -------------------------------
[EMU|LOG] << # Passed "test_that_passes_with_fatal_expected" (2)
[EMU|ERR] << Assertion failed : 0==1
[EMU|LOG] << The execution stopped
[EMU|LOG] << -------------------------------
[EMU|LOG] << # Failed "test_that_fails" (3)
[EMU|LOG] << -------------------------------
[EMU|LOG] << Test Module terminated
[EMU|LOG] << Passed 2 tests out of 3
```