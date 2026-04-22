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

void update_menu(game_t *this)
{
    set_bkg_tiles(0, 0, this->map.width, this->map.height, map_menu);
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

void init_menu(game_t *this)
{
    this->update = &update_menu;
    init_map(this);
    SWITCH_ROM(BANK(menu_tilesets)); 
    set_bkg_data(0, menu_tilesets_TILE_COUNT, menu_tilesets_tiles);
    SWITCH_ROM(BANK(menu_tilemap));
    set_bkg_tiles(0, 0, 32, 32, map_menu);
    init_window(this);
}
