declare var api: any;

var ProName: any;
var ProPath: any;
var MakefileText: string;
var MainCText: string;

MakefileText = `#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

# These set the information text in the nds file
#GAME_TITLE     := My Wonderful Homebrew
#GAME_SUBTITLE1 := built with devkitARM
#GAME_SUBTITLE2 := http://devitpro.org

include $(DEVKITARM)/ds_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
# DATA is a list of directories containing binary files embedded using bin2o
# GRAPHICS is a list of directories containing image files to be converted with grit
# AUDIO is a list of directories containing audio to be converted by maxmod
# ICON is the image used to create the game icon, leave blank to use default rule
# NITRO is a directory that will be accessible via NitroFS
#---------------------------------------------------------------------------------
TARGET   := $(shell basename $(CURDIR))
BUILD    := build
SOURCES  := src
INCLUDES := include
DATA     := data
GRAPHICS := art
AUDIO    := sound
ICON     := #icon.bmp

# specify a directory which contains the nitro filesystem
# this is relative to the Makefile
NITRO    :=

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH := -marm -mthumb-interwork -march=armv5te -mtune=arm946e-s

CFLAGS   := -g -Wall -O3\
            $(ARCH) $(INCLUDE) -DARM9
CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions
ASFLAGS  := -g $(ARCH)
LDFLAGS   = -specs=ds_arm9.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project (order is important)
#---------------------------------------------------------------------------------
LIBS := -lnds9

# automatigically add libraries for NitroFS
ifneq ($(strip $(NITRO)),)
LIBS := -lfilesystem -lfat $(LIBS)
endif
# automagically add maxmod library
ifneq ($(strip $(AUDIO)),)
LIBS := -lmm9 $(LIBS)
endif

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS := $(LIBNDS) $(PORTLIBS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT := $(CURDIR)/$(TARGET)

export VPATH := $(CURDIR)/$(subst /,,$(dir $(ICON)))\
                $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))\
                $(foreach dir,$(DATA),$(CURDIR)/$(dir))\
                $(foreach dir,$(GRAPHICS),$(CURDIR)/$(dir))

export DEPSDIR := $(CURDIR)/$(BUILD)

CFILES   := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES   := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
PNGFILES := $(foreach dir,$(GRAPHICS),$(notdir $(wildcard $(dir)/*.png)))
BINFILES := $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

# prepare NitroFS directory
ifneq ($(strip $(NITRO)),)
  export NITRO_FILES := $(CURDIR)/$(NITRO)
endif

# get audio list for maxmod
ifneq ($(strip $(AUDIO)),)
  export MODFILES	:=	$(foreach dir,$(notdir $(wildcard $(AUDIO)/*.*)),$(CURDIR)/$(AUDIO)/$(dir))

  # place the soundbank file in NitroFS if using it
  ifneq ($(strip $(NITRO)),)
    export SOUNDBANK := $(NITRO_FILES)/soundbank.bin

  # otherwise, needs to be loaded from memory
  else
    export SOUNDBANK := soundbank.bin
    BINFILES += $(SOUNDBANK)
  endif
endif

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
  export LD := $(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
  export LD := $(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

export OFILES_BIN   :=	$(addsuffix .o,$(BINFILES))

export OFILES_SOURCES := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export OFILES := $(PNGFILES:.png=.o) $(OFILES_BIN) $(OFILES_SOURCES)

export HFILES := $(PNGFILES:.png=.h) $(addsuffix .h,$(subst .,_,$(BINFILES)))

export INCLUDE  := $(foreach dir,$(INCLUDES),-iquote $(CURDIR)/$(dir))\
                   $(foreach dir,$(LIBDIRS),-I$(dir)/include)\
                   -I$(CURDIR)/$(BUILD)
export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

ifeq ($(strip $(ICON)),)
  icons := $(wildcard *.bmp)

  ifneq (,$(findstring $(TARGET).bmp,$(icons)))
    export GAME_ICON := $(CURDIR)/$(TARGET).bmp
  else
    ifneq (,$(findstring icon.bmp,$(icons)))
      export GAME_ICON := $(CURDIR)/icon.bmp
    endif
  endif
else
  ifeq ($(suffix $(ICON)), .grf)
    export GAME_ICON := $(CURDIR)/$(ICON)
  else
    export GAME_ICON := $(CURDIR)/$(BUILD)/$(notdir $(basename $(ICON))).grf
  endif
endif

.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).nds $(SOUNDBANK)

#---------------------------------------------------------------------------------
else

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).nds: $(OUTPUT).elf $(NITRO_FILES) $(GAME_ICON)
$(OUTPUT).elf: $(OFILES)

# source files depend on generated headers
$(OFILES_SOURCES) : $(HFILES)

# need to build soundbank first
$(OFILES): $(SOUNDBANK)

#---------------------------------------------------------------------------------
# rule to build solution from music files
#---------------------------------------------------------------------------------
$(SOUNDBANK) : $(MODFILES)
#---------------------------------------------------------------------------------
	mmutil $^ -d -o$@ -hsoundbank.h

#---------------------------------------------------------------------------------
%.bin.o %_bin.h : %.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
# This rule creates assembly source files using grit
# grit takes an image file and a .grit describing how the file is to be processed
# add additional rules like this for each image extension
# you use in the graphics folders
#---------------------------------------------------------------------------------
%.s %.h: %.png %.grit
#---------------------------------------------------------------------------------
	grit $< -fts -o$*

#---------------------------------------------------------------------------------
# Convert non-GRF game icon to GRF if needed
#---------------------------------------------------------------------------------
$(GAME_ICON): $(notdir $(ICON))
#---------------------------------------------------------------------------------
	@echo convert $(notdir $<)
	@grit $< -g -gt -gB4 -gT FF00FF -m! -p -pe 16 -fh! -ftr

-include $(DEPSDIR)/*.d

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------`;

MainCText = `#include <nds.h>
#include <stdio.h>
#include <string.h>
#include <maxmod9.h>

SpriteEntry OAMCopy[128];

#include "soundbank.h"
#include "soundbank_bin.h"

#include "events.c"

volatile int frame = 0;

enum { CONTINUOUS, SINGLE } TouchType = CONTINUOUS;

void Vblank() {
	frame++;
}

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	SetUpRooms();
	SetUpRoomBoxes();

	//Touch Position
	touchPosition touch;

    //Setting Video Modes
    videoSetMode(  MODE_0_2D | 
                   DISPLAY_SPR_ACTIVE |		//turn on sprites
                   DISPLAY_BG0_ACTIVE |		//turn on background 0
                   DISPLAY_SPR_1D			//this is used when in tile mode
                    );
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_0_2D);

	//Setting the banks. Does not include the F bank
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_A_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	//Set up oam
	oamInit(&oamMain, SpriteMapping_1D_128, true);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	//Set bank F
	vramSetBankF(VRAM_F_LCD);
	//init16(&Player, (u8*)ScarletMapTiles);
	//dmaCopy(ScarletMapPal, &VRAM_F_EXT_SPR_PALETTE[0][0],ScarletMapPalLen);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);

	//Background
	//int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);
	//dmaCopy(Grass1Bitmap, bgGetGfxPtr(bg3), 256*256);
	//dmaCopy(Grass1Pal, BG_PALETTE, 256*2); //80% Trans on shadows
		
	//Make the bottom screen a blue color
	setBackdropColorSub(5555000000009999);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   int keys = 0;
   int sx = 0;
   int sy = 0;
   int width = 0;
   int height = 0;
//////////////////////////////////////////////////////////////////////////////////////Music
	mmInitDefaultMem((mm_addr)soundbank_bin);
	
	// load the module
	mmLoad( MOD_MYSONG );

	// load sound effects
	//mmLoadEffect( SFX_AMBULANCE );
	//mmLoadEffect( SFX_BOOM );

	// Start playing module
	mmStart( MOD_MYSONG, MM_PLAY_LOOP );

/*
	mm_sound_effect ambulance = {
		{ SFX_AMBULANCE } ,			// id
		(int)(1.0f * (1<<10)),	// rate
		0,		// handle
		255,	// volume
		0,		// panning
	};
*/	
 

	//Loops every frame
	while(1) {

		swiWaitForVBlank();

		scanKeys();

		touchRead(&touch);
		
		int pressed = keysDown();
		int held = keysHeld();
		int released = keysUp();

		//animate16(&Player);
		//oamSet(&oamMain, 0, Player.Xpos, Player.Ypos, 0, 0, SpriteSize_16x16, SpriteColorFormat_256Color, Player.sprite_gfx_mem, -1, false, false, false, PlayerFlipped, false);
		//oamUpdate(&oamMain);
	}
}`;

(() => {
    let NameObject = document.getElementById("name-input");
    let PathObject = document.getElementById("path-input");

    NameObject?.addEventListener('input', () => {
        //@ts-expect-error
        ProName = NameObject?.value.replaceAll(' ', '_');
        //@ts-expect-error
        NameObject.value = ProName;
    });

    PathObject?.addEventListener('input', () => {
        //@ts-expect-error
        ProPath = PathObject?.value.replaceAll(' ', '_');
        //@ts-expect-error
        PathObject.value = ProPath;
    });

    document.querySelector('#back-btn')?.addEventListener('click', () => {
        window.location.href = '../index.html';
    }),
    document.querySelector('#sample-proj-btn')?.addEventListener('click', () => {
        
    }),
    document.querySelector('#blank-proj-btn')?.addEventListener('click', () => {
        NameObject = document.getElementById("name-input");
        PathObject = document.getElementById("path-input");
        //@ts-expect-error
        ProName = NameObject?.value.replaceAll(' ', '_');
        //@ts-expect-error
        NameObject.value = ProName;
        //@ts-expect-error
        ProPath = PathObject?.value.replaceAll(' ', '_');
        //@ts-expect-error
        PathObject.value = ProPath;
        api.MakeBlankProject(ProName, ProPath, MakefileText, MainCText);
    })
})()