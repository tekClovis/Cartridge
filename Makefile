LCC      = $(GBDKDIR)/bin/lcc
EXEC     = sleeper.gb
GBDKDIR ?= $(HOME)/.local/opt/gbdk-4.5.0

# MBC5 + RAM + BATTERY: -Wl-yt0x1B
# ROM Size 1MB: -Wl-yo16 (64 banks)
LCCFLAGS = -Wa-l -Wl-m -Wl-yt0x1B -Wl-yo16 \
	-Wf--opt-code-speed -Wf--opt-code-size \
	-Wf--max-allocs-per-node5000 \
	-Iinclude

SRC = src/core/core.c \
	src/games/menu/menu.c \
	src/cartridge.c \
	src/assets/menu/menu_tilemap.c \
	src/assets/menu/menu_tilesets.c \

.PHONY: all clean play

all: $(EXEC)

$(EXEC): $(SRC)
	$(LCC) $(LCCFLAGS) -o $@ $(SRC)

clean:
	rm -rf *.o *.lst *.map *.gb *.ihx *.sym *.noi *.asm

play:
	retroarch -L /usr/lib/x86_64-linux-gnu/libretro/gambatte_libretro.so $(EXEC)

re: clean all