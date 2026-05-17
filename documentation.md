# POKOPIE - Game Boy Cartridge Project Documentation

## Table of Contents
1. [Project Overview](#project-overview)
2. [Architecture](#architecture)
3. [Directory Structure](#directory-structure)
4. [Build System](#build-system)
5. [Game Modules](#game-modules)
6. [Core Systems](#core-systems)
7. [Asset Pipeline](#asset-pipeline)
8. [Development Guide](#development-guide)

---

## Project Overview

**POKOPIE** is a Game Boy Color (GBC) cartridge project developed as an EPITECH project for 2026. It is a multi-game ROM compilation containing several independent games and a menu system to navigate between them.

## Summary

**POKOPIE** is a sophisticated Game Boy cartridge featuring a menu-driven multi-game system with persistent high-score storage. The architecture uses polymorphic game states, a flexible entity system, and optimized graphics rendering to fit within the Game Boy's hardware constraints. The codebase is modular, making it easy to add new games or features while maintaining compatibility with the cartridge hardware and emulator ecosystem.

### Project Specifications
- **Target Platform**: Game Boy / Game Boy Color (8-bit)
- **ROM Size**: 256 KB (16 banks of 16 KB each)
- **Cartridge Type**: MBC5 + RAM + Battery (0x1B header)
- **Save System**: 8 KB external SRAM (for high scores)
- **Language**: C (compiled with GBDK 4.5.0 / SDCC)
- **Emulator**: Emulicious for testing

### Included Games
1. **Starting Screen** - Introductory animation
2. **Menu** - Game selection interface with high score display
3. **Wolf3D** - 3D first-person raycasting game with enemy AI
4. **Tyrunt** - 2D platformer with obstacles, bonuses, and score system
5. **Snake** - Classic top-down snake game (add-on)
6. **Game 3** - Placeholder for future game


### Key Features
- Persistent high-score storage using battery-backed SRAM
- Multi-game architecture with dynamic game switching
- Entity system for sprite management (up to 16 entities)
- Raycasting engine for 3D graphics
- Animation and collision detection systems
- Menu-driven game selection with score preview

---

## Architecture

### High-Level Design

```
┌─────────────────────────────────────────┐
│      Main Cartridge Loop (cartridge.c)  │
│                                         │
│  init() -> vsync loop -> update()       │
└──────────────────┬──────────────────────┘
                   │
        ┌──────────┴──────────┐
        │                     │
   ┌────▼────────┐     ┌──────▼──────┐
   │ Game System │     │  Save System │
   └────┬────────┘     └──────────────┘
        │
   ┌────┴─────────────────┬─────────┬────────────┐
   │                      │         │            │
┌──▼───────┐  ┌──────────▼──┐  ┌───▼────┐  ┌───▼────┐
│   Menu   │  │  Wolf3D     │  │ Tyrunt │  │ Screen │
└──────────┘  └─────────────┘  └────────┘  └────────┘
```

### Core Concepts

#### Game State Machine
The cartridge uses a polymorphic game state system:
- Each game implements two functions: `init_game()` and `update_game()`
- The main loop calls the current game's `update()` function each frame
- Games transition via `init_game(game, NEW_GAME_ID)`

#### Entity System
- Maximum 16 entities per game
- Each entity has position, sprite data, and animation state
- Pluggable data structure via `active_game_data_t` union for game-specific data
- Separate display functions: `draw_ent8()` and `draw_ent16()` for sprite sizes

#### Memory Architecture
- **WRAM**: 8 KB work RAM (0xC000-0xDFFF) - general purpose
- **SRAM**: 8 KB external RAM (0xA000-0xBFFF) - battery-backed for saves
- **VRAM**: 8 KB video RAM (0x8000-0x9FFF) - tile and sprite data
- **OAM**: 160 bytes - sprite attributes

---

## Directory Structure

```
cartridge/
├── Makefile                 # Build configuration and rules
├── documentation.md         # This file
├── pokopie.gb              # Compiled ROM binary
├── include/                # Header files
│   ├── entities.h          # Entity structure and unions
│   ├── font.h              # Font tile data
│   ├── game.h              # Core game structure and interfaces
│   ├── game_menu.h         # Menu-specific declarations
│   ├── game_start_screen.h # Starting screen declarations
│   ├── game_tyrunt.h       # Tyrunt game declarations
│   ├── game_wolf3d.h       # Wolf3D game declarations (includes raycasting)
│   ├── map.h               # Map/tilemap structures
│   └── window.h            # Window (overlay) management
│
├── rawAssets/              # Source assets (before compilation)
│   ├── menu/               # Menu tilemaps
│   ├── start/              # Starting screen tilemaps
│   ├── utils/              # Utility assets
│   └── wolf3d/             # Wolf3D raycasting map
│
└── src/                    # Source code
    ├── cartridge.c         # Main cartridge entry point
    ├── entities/           # Entity system implementation
    │   └── entities.c
    ├── save/               # Save system (high scores)
    │   ├── save.c
    │   └── save.h
    ├── assets/
    │   ├── font.c
    │   ├── menu/           # Menu assets (tilesets, tilemaps)
    │   ├── starting_screen/# Starting screen assets
    │   └── wolf3d/         # Wolf3D assets (maps, tilesets)
    └── games/              # Game implementations
        ├── menu/           # Main menu
        │   ├── init.c      # Menu initialization
        │   ├── menu.c      # Menu update and rendering
        │   └── handle_input.c
        ├── starting_screen/# Opening animation
        │   └── starting_screen.c
        ├── Snake/
        │   └── snake.c
        ├── tyrunt/         # Platformer game
        │   ├── init.c
        │   ├── tyrunt.c    # Main game loop
        │   ├── handle_input.c
        │   ├── animation.c
        │   ├── spawner.c   # Obstacle spawning system
        │   ├── score.c     # Score management
        │   ├── update_player.c
        │   ├── update_tree.c
        │   ├── update_tylton.c (enemy)
        │   ├── update_bonus.c
        │   ├── utils.c
        │   └── assets/     # Tyrunt graphics (sprites, tilesets)
        ├── wolf3d/         # 3D raycasting game
        │   ├── init.c      # Game initialization (not used)
        │   ├── wolf3d.c    # Main game loop
        │   ├── handle_input.c
        │   ├── raycasting.c# Core raycasting engine
        │   ├── game_over.c # Game over screen
        │   ├── utils.c
        │   ├── entities/   # Entity-specific (player, enemies)
        │   │   ├── player.c
        │   │   └── ennemy.c
        │   └── assets/     # Wolf3D graphics
        └── utils/          # Shared utilities
            ├── utils.c     # Misc utilities
            ├── print.c     # Text rendering to map/window
            ├── anims.c     # Animation helpers
            └── anims.lst
```

---

## Build System

### Makefile Overview

The project uses a Makefile to build the ROM using GBDK (GameBoy Developers Kit).

#### Key Build Variables
```makefile
LCC         = $(GBDKDIR)/bin/lcc      # GBDK compiler
EXEC        = pokopie.gb              # Output binary
GBDKDIR     = $(HOME)/.local/opt/gbdk-4.5.0
ROM_BANKS   = 16                       # 16 * 16KB = 256KB

# MBC5 + RAM + BATTERY: -Wl-yt0x1B
# This header configures the cartridge type in the ROM
```

#### Compilation Flags
- `-Wl-yt0x1B`: MBC5 with RAM and battery (for SRAM persistence)
- `-Wl-yo16`: 16 ROM banks (256 KB total)
- `-Wl-ya1 -Wm-yoA`: SRAM configuration
- `-Wf--opt-code-speed -Wf--opt-code-size`: Optimization balance

#### Build Targets

| Target | Description |
|--------|-------------|
| `make all` | Build pokopie.gb (default) |
| `make clean` | Remove .o, .lst, .asm, .sym files (keep ROM) |
| `make fclean` | Remove all build artifacts including ROM |
| `make play` | Build and launch in RetroArch |
| `make rom-usage` | Show ROM space utilization stats |

#### Build Process

1. **Compile C source files** → `.o` object files
2. **Special save handling**: `save.o` compiled with `-Wf-ba0` (bank 0 only)
3. **Link all objects**: `lcc ... -o pokopie.gb $(OBJ) src/save/save.o`
4. **Generate map file**: `pokopie.map` (symbol table and memory map)
5. **Calculate ROM usage** and display statistics

#### ROM Usage Example
```
ROM usage (content): 27187 / 262144 bytes (10.37%)
ROM image size: 262144 bytes
```

---

## Game Modules

### 1. Starting Screen (`src/games/starting_screen/`)
- **Purpose**: Opening animation/logo
- **Transitions to**: Menu
- **Key Function**: `update_starting_screen()`
- **Features**:
  - Animated sprite movement
  - Fade in/out effects
  - Auto-advance to menu

### 2. Menu (`src/games/menu/`)
- **Purpose**: Game selection interface with high-score display
- **Files**:
  - `init.c`: Initialize menu entities and layout
  - `menu.c`: Menu rendering and game stat display
  - `handle_input.c`: Arrow key navigation and game selection
- **Features**:
  - Selection rectangles for 3 games (Wolf3D, Tyrunt, Game 3)
  - High score display for each game (read from SRAM)
  - Window overlay showing selected game info
  - Menu animation loop

### 3. Wolf3D (`src/games/wolf3d/`)
- **Purpose**: 3D first-person raycasting game with enemy AI
- **Key Files**:
  - `raycasting.c`: Core raycasting rendering engine
  - `wolf3d.c`: Main game loop and game state management
  - `entities/player.c`: Player movement and collision
  - `entities/ennemy.c`: Enemy AI and pathfinding
  - `handle_input.c`: Player controls (WASD/arrows)
  - `game_over.c`: Game over screen and high score saving

#### Raycasting Engine Details
- **Resolution**: 20 rays per frame (narrow but fast)
- **Data Structures**: `w3d_plug_in_t` stores:
  - `last_rays[]`: Previous frame ray distances
  - `rays[]`: Current ray distances
  - `side[]`: Hit side (N/S/E/W)
  - `x_tiles_touch[]`, `y_tiles_touch[]`: Map collision points
- **Map Format**: Tile-based walkable/solid distinction
- **Enemy System**: Multiple Machop/Geodude entities with AI

#### Graphics
- 17-tile raycasting column set
- 8-tile Machop sprite tileset
- 8-tile gun/weapon tileset
- Real-time rendering each frame

#### High Score Persistence
- High score saved to SRAM when game ends
- Read from persistent storage on menu return

### 4. Tyrunt (`src/games/tyrunt/`)
- **Purpose**: 2D platformer with obstacles and bonus collection
- **Key Files**:
  - `tyrunt.c`: Main game loop and physics
  - `init.c`: Game initialization and entity setup
  - `update_player.c`: Player movement, jumping, collision
  - `spawner.c`: Random obstacle generation
  - `update_tree.c`: Tree obstacle behavior
  - `update_tylton.c`: Enemy AI behavior
  - `update_bonus.c`: Bonus/powerup effects
  - `animation.c`: Sprite animations
  - `score.c`: Score tracking and updates

#### Game Mechanics
- **Player**: Gobou character with jump, double-jump, invincibility frames
- **Obstacles**: Trees, Tylton enemies with movement patterns
- **Bonuses**: Score multipliers, speed boosts, invincibility
- **Physics**: Gravity, velocity, collision detection
- **Timers**: Invincibility duration, slow effects, spawn rates

#### Data Structure (tyrunt_plug_in_t)
```c
typedef struct {
    int8_t velocity_y;           // Vertical velocity (falling/jumping)
    uint8_t is_jumping;          // Jump state
    uint16_t score;              // Current game score
    uint8_t speed;               // Player speed multiplier
    int16_t spawn_timer;         // Obstacle spawn countdown
    uint16_t invincible_timer;   // Invincibility frame count
    uint8_t double_jumps_left;   // Remaining mid-air jumps
    uint16_t slow_timer;         // Slow effect duration
    uint8_t last_displayed_bonus;// Animation state
} tyrunt_plug_in_t;
```

### 5. Snake (`src/games/Snake/`)
- **Purpose**: Classic top-down Snake game where the player grows by eating apples and avoids collisions.
- **Key Files**:
  - `snake.c`: Main game loop and logic
  - `snake.asm`: Compiled asset/object data (generated)
  - `snake.lst`: Linker/listing output
  - `include/game_snake.h`: Game-specific declarations (input/mode identifiers)

#### Gameplay
- Grid-based playfield with wrap/no-wrap modes
- Apple spawning, snake growth, self-collision detection
- Increasing speed / difficulty over time
- Controls: D-pad for direction; `A` to pause/select

#### Integration Notes
- Implement `init_game()` and `update_game()` following the game's interface in `include/game.h`.
- Add `src/games/Snake/snake.c` to the Makefile `OBJ` list so it's compiled and linked into the ROM.
- Register the new game in the menu selection code (`src/games/menu/menu.c` / `handle_input.c`) so it appears in the menu.
- High-score persistence: update `src/save/save.c` / `save.h` to allocate an extra slot in the `high_scores[]` array (currently `uint16_t high_scores[3]`) or migrate to a dynamic layout to accommodate the Snake score.

#### Assets
- Prefer compact tilesets (8x8) and reuse existing font tiles where possible to save VRAM.

#### Notes
- Because the current save system defaults to 3 slots, include a migration or clear routine when expanding slots to avoid corrupt reads.


---

## Core Systems

### Save System (`src/save/`)

#### High-Score Storage
- **Location**: External SRAM at address `0xA000` (6 bytes)
- **Data**: `uint16_t high_scores[3]` (one per game)
- **Persistence**: Battery-backed cartridge RAM
- **Initialization**: Corrupted saves (> 999) auto-reset on boot

#### Save Access Pattern
```c
// Before reading/writing SRAM:
SWITCH_RAM(0);      // Select SRAM bank 0
ENABLE_RAM;         // Enable external RAM
// ... read/write high_scores[i] ...
DISABLE_RAM;        // Disable external RAM
```

#### Limitations
- 3 high scores maximum (one per major game)
- No player names or timestamps
- Emulator must support SRAM saves (Emulicious does)

### Entity System (`src/entities/`)

#### Entity Structure
```c
typedef struct entities_s {
    uint16_t x;              // X position (sub-pixel precision)
    uint16_t y;              // Y position
    uint8_t x_sprite;        // Sprite X offset
    uint8_t y_sprite;        // Sprite Y offset
    uint8_t sprite_ids[4];   // Sprite object IDs (8x16 uses 4)
    uint8_t sprite_tile[4];  // Tile indices for each sprite
    uint8_t direction;       // Facing direction (0-3)
    uint8_t animation;       // Current animation frame
    uint8_t sprite_nb;       // Number of sprite objects
    uint8_t life;            // Health/life points
    void *personal_data;     // Pointer to game-specific data
} entities_t;
```

#### Display Functions
- `draw_ent16()`: Draw 16x16 sprite (4 tiles in 2x2 grid)
- `draw_ent8()`: Draw 8x8 sprite (single tile)

#### Game-Specific Data Union
```c
typedef union {
    uint8_t data[MAX_PLUG_IN_BYTES];  // 128 bytes raw
    w3d_plug_in_t wolf3d;             // Wolf3D-specific data
    tyrunt_plug_in_t tyrunt;          // Tyrunt-specific data
} active_game_data_t;
```

### Graphics & Rendering

#### Tile System
- **VRAM**: 384 tiles (8 KB limit)
- **Tile Size**: 8x8 pixels
- **Tilemaps**: 32x32 tiles (256x256 pixels)
- **Backgrounds**: Two background layers (BKG + WIN)
- **Sprites**: 40 hardware sprites max (8x8 or 8x16)

#### Rendering Functions
- `set_bkg_data()`: Load tile patterns into VRAM
- `set_sprite_data()`: Load sprite patterns
- `move_bkg()`: Scroll background layer
- `move_win()`: Position window overlay

#### Font System
- 209-tile font set compiled into `font.asm`
- Text rendered using tile map approach
- Functions: `printToMap()`, `printToWin()`

### Input System

#### Joypad Macros
```c
joypad() & J_UP         // D-pad up
joypad() & J_DOWN       // D-pad down
joypad() & J_LEFT       // D-pad left
joypad() & J_RIGHT      // D-pad right
joypad() & J_A          // A button
joypad() & J_B          // B button
joypad() & J_START      // Start button
joypad() & J_SELECT     // Select button
```

#### Per-Game Input Handlers
- Menu: `handle_input()` (menu.c)
- Wolf3D: `handle_input()` (wolf3d/handle_input.c)
- Tyrunt: `handle_input_tyrunt()` (tyrunt/handle_input.c)

### Window System (`include/window.h`)

#### Window Structure
```c
typedef struct {
    uint8_t x;      // Window X position (0-7)
    uint8_t y;      // Window Y position (0-143)
    // Additional data...
} window_t;
```

- Maximum 2 windows per game
- Used for UI overlays, score display, menus
- Window Y typically at bottom (y=120-144)

---

## Asset Pipeline

### Asset Types

#### Tilemaps (`*.tilemap` files)
- Source format: XML-based tilemap data
- Compiled to: `.asm` + `.c` files
- Linked into ROM as tile pattern arrays
- **Tools**: Likely GBDK asset converter or custom tool

#### Tilesets
- Define visual appearance of tiles
- 8-tile sets for different game areas
- Examples:
  - `menu_tilesets.c` - Menu UI graphics
  - `pokopie_tileset.c` - Start screen graphics
  - `gun_tileset.c` - Wolf3D weapon graphics
  - `machop_tiles.c` - Wolf3D enemy sprite

#### Font Data
- 209-tile font set in `src/assets/font.c`
- Pre-rendered 8x8 ASCII glyphs
- Loaded at boot: `set_bkg_data(209, font_TILE_COUNT, font_tiles)`

### Asset Compilation

The build system compiles assets into object files:
```
rawAssets/*.tilemap → tool → src/assets/*.asm → lcc → .o
```

Key observation: `save.o` is compiled specially with `-Wf-ba0` flag to ensure it stays in SRAM bank 0.

---

## Development Guide

### Adding a New Game

1. **Create Game Module**
   ```
   src/games/mygame/
   ├── init.c         # Initialization function
   ├── mygame.c       # Main update loop
   └── handle_input.c # Input handling
   ```

2. **Create Header**
   ```c
   // include/game_mygame.h
   #ifndef GAME_MYGAME_H_
   #define GAME_MYGAME_H_
   #include "game.h"
   
   const void init_mygame(game_t *this);
   const void update_mygame(game_t *this);
   
   #endif
   ```

3. **Define Game-Specific Data** (optional)
   ```c
   // in include/game.h, extend active_game_data_t
   typedef struct {
       // game-specific variables
   } mygame_plug_in_t;
   ```

4. **Implement Game Functions**
   ```c
   const void init_mygame(game_t *this) {
       // Initialize sprites, map, state
       this->update = &update_mygame;
   }
   
   const void update_mygame(game_t *this) {
       // Main game loop
       handle_input(this);
       // Update physics, enemies, etc.
       // Render to screen
   }
   ```

5. **Register in Menu**
   - Add to `game_names[]` in `src/games/menu/menu.c`
   - Add selection rectangle in `infos_rect[]`
   - Update `game_id_e` enum if needed

6. **Update Makefile**
   ```makefile
   MYGAME_SRC = src/games/mygame/*.c
   SRC += $(MYGAME_SRC)
   ```

### Memory Management Tips

- **RAM**: ~5 KB available after OS reserves
- **SRAM**: Carefully manage 8 KB for saves
- **ROM**: ~27 KB used (10.4% of 256 KB)
- Monitor with: `make rom-usage`

### Graphics Pipeline

1. **Create Asset** (tilemap, spritesheet)
2. **Convert to C** using GBDK tools
3. **Add to src/assets/**
4. **Load in Game Init**:
   ```c
   set_bkg_data(offset, COUNT, data);
   set_sprite_data(offset, COUNT, data);
   ```
---
### Emulator Testing

#### Emulicious
- **Debugger**: Step through code, inspect memory
- **SRAM Viewer**: Check save state persistence
- **Profiler**: Identify performance bottlenecks
- **Breakpoints**: Set conditional breaks on errors

#### RetroArch
- **Accessibility**: Faster but fewer debug features
- **Compatibility**: Good for final testing
- **Launch**: `make play`

### Memory Map Reference

| Address | Size | Purpose |
|---------|------|---------|
| 0x0000-0x00FF | 256 B | Restart vectors |
| 0x0100-0x014F | 80 B | Cartridge header |
| 0x0150-0x7FFF | 32 KB | ROM bank 0 (fixed) |
| 0x4000-0x7FFF | 16 KB × 15 | Switchable ROM banks |
| 0x8000-0x9FFF | 8 KB | Video RAM (VRAM) |
| 0xA000-0xBFFF | 8 KB | External RAM (SRAM, battery-backed) |
| 0xC000-0xDFFF | 8 KB | Work RAM (WRAM) |
| 0xFE00-0xFEFF | 256 B | OAM (sprite attributes) |
| 0xFF00-0xFFFF | 256 B | I/O and HRAM |

---
