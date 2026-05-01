# Colors
COL_BOLD := \033[1m
COL_RESET := \033[0m
COL_RED := \033[0;31m
COL_GREEN := \033[0;32m
COL_YELLOW := \033[0;33m
COL_BLUE := \033[0;34m

LCC      = $(GBDKDIR)/bin/lcc
EXEC     = pokopie.gb
GBDKDIR ?= $(HOME)/.local/opt/gbdk-4.5.0
ROM_BANKS = 16

# MBC5 + RAM + BATTERY: -Wl-yt0x1B
# ROM Size 256KB: -Wl-yo16 (16 banks)
LCCFLAGS = -Wa-l -Wl-m -Wl-yt0x1B -Wl-yo$(ROM_BANKS) \
	-Wf--opt-code-speed -Wf--opt-code-size \
	-Wf--max-allocs-per-node5000 \
	-Iinclude

WOLD3D_SRC = src/games/wolf3d/raycasting.c \
			 src/games/wolf3d/wolf3d.c \
			 src/games/wolf3d/handle_input.c \
			 src/assets/wolf3d/map.c

TYRUNT_SRC = src/games/tyrunt/tyrunt.c \

SRC = src/games/utils/utils.c \
	src/games/utils/print.c \
	src/games/utils/anims.c \
	src/games/utils/globals.c \
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
	src/assets/font.c \
	$(WOLD3D_SRC) \
	$(TYRUNT_SRC)

OBJ = $(SRC:.c=.o)
LST = $(OBJ:.o=.lst)
ASM = $(OBJ:.o=.asm)
SYM = $(OBJ:.o=.sym)

.SILENT:

all: $(EXEC)

$(EXEC): $(OBJ)
	$(LCC) $(LCCFLAGS) -o $@ $(OBJ)
	@$(MAKE) --no-print-directory rom-usage
	@printf '$(COL_GREEN)[INFO]$(COL_RESET) Build successful: $(COL_BOLD)%s$(COL_RESET)\n' "$@"

rom-usage:
	@if [ ! -f pokopie.map ] || [ ! -f $(EXEC) ]; then \
		printf '$(COL_RED)[ERROR]$(COL_RESET) Missing $(COL_BOLD)pokopie.map$(COL_RESET) or $(COL_BOLD)$(EXEC)$(COL_RESET). Please build the project first.\n'; \
		exit 0; \
	fi; \
	map_used_bytes=$$(awk 'function h2d(h, i, c, v, r){r=0; for(i=1;i<=length(h);i++){c=substr(h,i,1); if(c>="0"&&c<="9")v=c+0; else if(c>="A"&&c<="F")v=10+index("ABCDEF",c)-1; else if(c>="a"&&c<="f")v=10+index("abcdef",c)-1; else v=0; r=r*16+v} return r} /^(_CODE|_HOME|_INITIALIZER|_GSINIT|_GSFINAL|_HEADER[0-9A-Fa-f]+)/{start=h2d($$2); size=h2d($$3); end=start+size; if(end>max)max=end} END{print max+0}' pokopie.map); \
	limit_bytes=$$(( $(ROM_BANKS) * 16384 )); \
	usage_pct=$$(awk "BEGIN { printf \"%.2f\", ($$map_used_bytes * 100) / $$limit_bytes }"); \
	image_bytes=$$(wc -c < $(EXEC)); \
	printf '$(COL_YELLOW)ROM usage (content): $(COL_RESET)%s / %s bytes $(COL_BOLD)(%s%%)$(COL_RESET)\n' "$$map_used_bytes" "$$limit_bytes" "$$usage_pct"; \
	printf '$(COL_YELLOW)ROM image size: $(COL_RESET)%s bytes\n' "$$image_bytes"

%.o: %.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ) $(LST) $(ASM) $(EXEC) $(SYM) *.map *.ihx *.sym *.noi
	@printf '$(COL_BLUE)[INFO]$(COL_RESET) Cleaned build artifacts.\n'

fclean: clean
	rm -rf $(EXEC)
	@printf '$(COL_BLUE)[INFO]$(COL_RESET) Cleaned everything.\n'

play: $(EXEC)
	@printf '$(COL_GREEN)[INFO]$(COL_RESET) Launching game in RetroArch...\n'
	retroarch -L /usr/lib/x86_64-linux-gnu/libretro/gambatte_libretro.so $(EXEC)

re: clean all

.PHONY: all clean play rom-usage