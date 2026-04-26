LCC      = $(GBDKDIR)/bin/lcc
EXEC     = pokopie.gb
GBDKDIR ?= $(HOME)/.local/opt/gbdk-4.5.0

# MBC5 + RAM + BATTERY: -Wl-yt0x1B
# ROM Size 1MB: -Wl-yo16 (64 banks)
LCCFLAGS = -Wa-l -Wl-m -Wl-yt0x1B -Wl-yo16 \
	-Wf--opt-code-speed -Wf--opt-code-size \
	-Wf--max-allocs-per-node5000 \
	-Iinclude

SRC = src/games/utils.c \
	src/games/anims.c \
	src/games/menu/menu.c \
	src/games/menu/init.c \
	src/games/menu/handle_input.c \
	src/games/starting_screen/starting_screen.c \
	src/entities/entities.c \
	src/cartridge.c \
	src/assets/menu/menu_tilemap.c \
	src/assets/menu/menu_tilesets.c \
	src/assets/menu/metamorph.c \
	src/assets/starting_screen/pokopie_tilemap.c \
	src/assets/starting_screen/pokopie_tileset.c	\
	src/assets/font.c

.PHONY: all clean play

all: $(EXEC)

$(EXEC): $(SRC)
	$(LCC) $(LCCFLAGS) -o $@ $(SRC)

clean:
	rm -rf *.o *.lst *.map *.gb *.ihx *.sym *.noi *.asm

play:
	retroarch -L /usr/lib/x86_64-linux-gnu/libretro/gambatte_libretro.so $(EXEC)

re: clean all