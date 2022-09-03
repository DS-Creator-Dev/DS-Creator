# Allocators Test 

## Background

Allocators are meant to be the "malloc" of VRAM with some extra helpful features.

- you can choose the memory allocation range (say, 0x0600000-0x06007fff)
- more than 1 allocator may exist at the same time (e.g. one for VRAM BG0, one for SPR etc.)
- you can force allocation at a fixed address (useful for setting the transparent tile at the beginning of the memory segment, but it's not limited to this)
- immune to free of unallocated address
- you are not required to manually delete each address since the allocator automatically frees them when gets out of scope

Due to their flexibility, the allocators have some (imposed) limitations:

- no more than 4096 **total** allocations
- no more than 255 allocators can exist at the same time
- max size of each allocator is 1024KB (VRAM total size is somewhere around 670KB so yeah)
- max size of a single allocated block is 1024KB

The following subfolder contains a test (and debug util) for `DSC::Allocator` class. 

## Build & Run

This test assumes that the Allocator code is portable (especially does not contain any libnds-related code).

Because DS is a 32-bit platform, this test should be compiled under 32-bit for best compatibility (avoiding the
narrowing conversion error caused by 64-bit pointer to int casts).

The `build.bat` file uses the MinGW 32-bit variant of gcc/g++. You can replace it with your own 32-bit compiler,
or you can try running directly the `main.exe` file.

## How to use

Running main.exe gives the following output:

```
Initing test...
Test memory address : 02660048

Creating allocator..
Allocator id   : 1
Allocator base : offset = 0xXXXXXXXX, length = 32768
Allocator head : 0xXXXXXXXX
```

Below that, a 32x32 alphanumeric matrix is displayed. Each letter corresponds to a free (unallocated) segment block.
One cell in the matrix represents 32 bytes of (VRAM) memory (== the size of a 4-bit DS tile).

You are asked to choose one option (e.g. reserve/release an address), then the matrix updates based on your input. 

```
Operation (1=reserse, 2=release, 3=dump memory, 0=exit)
 >>> 1
Length = 128
Reserved address at 02680048 (relative offset: 0x00000000)
Allocator head : 0x026800C8 (rel. 0x00000080)
...

Operation (1=reserse, 2=release, 3=dump memory, 0=exit)
 >>> 1
Length = 256
Reserved address at 026800C8 (relative offset: 0x00000080)
Allocator head : 0x026801C8 (rel. 0x00000180)
...

Operation (1=reserse, 2=release, 3=dump memory, 0=exit)
 >>> 1
Length = 512
Reserved address at 026801C8 (relative offset: 0x00000180)
Allocator head : 0x026803C8 (rel. 0x00000380)
...

Operation (1=reserse, 2=release, 3=dump memory, 0=exit)
 >>> 2
Offset (rel.) = 384
Freeing 026801C8
...

Operation (1=reserse, 2=release, 3=dump memory, 0=exit)
 >>> 2
Offset (rel.) = 0
Freeing 02680048

```

Leads to the final result:

```
01 |aaaa________bbbbbbbbbbbbbbbbbbbb
02 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
03 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
04 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
05 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
06 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
07 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
08 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
09 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
10 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
11 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
12 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
13 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
14 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
15 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
16 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
17 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
18 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
19 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
20 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
21 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
22 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
23 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
24 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
25 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
26 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
27 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
28 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
29 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
30 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
31 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
32 |bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
```

Explanation:

1. 128 bytes are allocated
1. The next 256 bytes are allocated
1. The next 512 bytes are allocated
1. We are freeing the 512 bytes block at relative address 384 (=128+256). The freed memory collates to the adjacent huge unallocated segment (the "b"s block)
1. We are freeing the 128 bytes block at relative address 0 (leads to the small "a"s block)
1. The "_"s block is the still alloced 256 bytes of memory 

Observation: This test uses relative offsets instead of actual addresses because the test buffer allocation depends on the runtime. On the actual DS, full addresses are used:

```
DSC::Allocator alc(VRAM, 0x8000); 
u16* tileset = alc.reserve(32*100); // "malloc": make enough room for 100 4-bit tiles

...

alc.release(tileset); // "free": tileset pointer
```

## To do: check the fixed reserve feature
