/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** menu
*/
#include "game.h"
#include "game_menu.h"
#include <string.h>
#include "map.h"
#include <gb/gb.h>

// static const palette_color_t menu_bg_palette[4] = {
//     RGB8(250, 242, 215), RGB8(196, 175, 112), RGB8(102, 112, 74), RGB8( 26,  34,  40)
// };

// static const palette_color_t menu_sprite_palette[4] = {
//     RGB8(255, 232, 204), RGB8(240, 173, 108), RGB8(142,  84,  84), RGB8( 25,  20,  23)
// };

// static void apply_color_mapping(void)
// {
//     // Swap middle shades for stronger contrast on DMG palettes.
//     BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_DARK_GRAY, DMG_LITE_GRAY, DMG_BLACK);
//     OBP0_REG = DMG_PALETTE(DMG_WHITE, DMG_DARK_GRAY, DMG_LITE_GRAY, DMG_BLACK);
//     OBP1_REG = DMG_PALETTE(DMG_WHITE, DMG_BLACK, DMG_DARK_GRAY, DMG_LITE_GRAY);

//     if (DEVICE_SUPPORTS_COLOR) {
//         set_bkg_palette(0, 1, menu_bg_palette);
//         set_sprite_palette(0, 1, menu_sprite_palette);
//     }
// }

static void handleInput(game_t *this){
    (void)this;
    switch (joypad())
    {
        case J_UP:
            break;
        case J_DOWN:
            break;
        case J_LEFT:
            break;
        case J_RIGHT:
            break;
        case J_A:
            break;
        case J_B:
            break;
        default:
            break;
    }
}

void update_menu(game_t *this)
{
    handleInput(this);
    SWITCH_ROM(BANK(menu_tilemap));
    set_bkg_tiles(0, 0, 32, 32, map_menu);
    SWITCH_ROM(BANK(menu_tilesets));
    draw_ent16(this->entities[0]);
}

static void init_map(game_t *this)
{
    
    this->map.width = map_menu_width;
    this->map.height = map_menu_height;
    this->map.size = map_menu_size;
}

static void init_window(game_t *this)
{
    this->window[0].x = 0;
    this->window[0].y = 0;
    this->window[1].x = 0;
    this->window[1].y = 0;
}

static void init_entities(game_t *this){
    for (int i = 0; i < 16; i++){
        this->entities[i].sprite_nb = 0;
        this->entities[i].x = 0;
        this->entities[i].y = 0;
    }
    this->entities[0].sprite_nb = 2;
    this->entities[0].x = 80;
    this->entities[0].y = 72;
    for (int i = 0; i < 2; i++){
        this->entities[0].sprite_ids[i] = i;
        set_sprite_tile(this->entities[0].sprite_ids[i], this->entities[0].sprite_ids[i] * 2);
    }
}

static void init_graphiques(game_t *this){
    (void)this;
    // apply_color_mapping();
    SPRITES_8x16;
    SWITCH_ROM(BANK(metamorph));
    set_sprite_data(0, metamorph_TILE_COUNT, metamorph_tiles);
    SWITCH_ROM(BANK(menu_tilesets)); 
    set_bkg_data(0, menu_tilesets_TILE_COUNT, menu_tilesets_tiles);
    SWITCH_ROM(BANK(menu_tilemap));
    set_bkg_tiles(0, 0, 32, 32, map_menu); 
}

void init_menu(game_t *this)
{
    this->update = &update_menu;
    init_map(this);
    init_window(this);
    init_graphiques(this);
    init_entities(this);
}