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
    SPRITES_8x16;
    SWITCH_ROM(BANK(menu_tilesets));
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
        this->entities->x = 0;
        this->entities->y = 0;
    }
    this->entities[0].sprite_nb = 2;
    for (int i = 0; i < 2; i++){
        this->entities[0].sprite_ids[i] = i;
        set_sprite_tile(i, i * 2);
        move_sprite(i, 50 + i * 8, 50);
    }
}

static void init_graphiques(game_t *this){
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