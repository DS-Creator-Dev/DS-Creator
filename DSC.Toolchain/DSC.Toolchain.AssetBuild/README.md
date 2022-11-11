# AssetBuild

AssetBuild is a utility that converts PNG images to AssetData structures.

## Command structure
```
AssetBuild 
    <filename \"*.(4|8|16)bpp.png\">
    <-wram|-file> 
    <-bitmap|-tiles>    
    <out_header.h> 
    <out_asm.s> 
    [<resource_filename.roa>]
```

Arguments (in this order, do not skip any):
- `<filename \"*.(4|8|16)bpp.png\">`
    
    Path to the PNG image. Its extension must specify the color depth the converter should use (e.g. `"my_image.8bpp.png"` for
    a 256-color image).
    Auto color reducer will be implemented soon. For now, make sure the number of colors doesn't exceed the bit depth you provide.

- `<-wram|-file>` 

    Tells if the resulted asset data will be accessed from memory or from a file (FAT/NITRO).

- `<-bitmap|-tiles>`

    Tells if the image will be converted as a bitmap or as a tile set.
    *(+ TO ADD: metatiles features)*

- `<out_header.h>`

    The path of the output C header file.

- `<out_asm.s>`

    The path of the output C assembly file containing binary resource data.

- `<resource_filename.roa>` - optional

    If `-file` is specified, then this argument represents the ouput file the effective asset data is written to.

    This is be the file that will be loaded from the filesystem.

## Usage example 

To compile an 8-bit PNG into a bitmap asset data that resides in memory, use the command

`AssetBuild path/to/image.8bpp.png -wram -bitmap image.h image.s`

Then, in the C++ code:

```C++
    #include "image.h"

    const DSC::AssetData* my_image = &ROA_image8;

    // use my_image 
```

Project structure:

```
source/main.cpp
source/image.h
source/image.s
Makefile
```

