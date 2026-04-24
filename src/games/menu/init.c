/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** init
*/

#include "game.h"
#include "game_menu.h"
#include "entities.h"
#include "map.h"
#include <gb/gb.h>
#include <stdio.h>


static void init_map(game_t *this)
{
    
    this->map.width = map_menu_width;
    this->map.height = map_menu_height;
    this->map.size = map_menu_size;
}

static void init_window(game_t *this)
{
    this->window[0].x = 6 << 3;
    this->window[0].y = 7 << 3;
    move_bkg(this->window[0].x, this->window[0].y);
}

static void init_entities(game_t *this){
    for (int i = 0; i < 16; i++){
        this->entities[i].sprite_nb = 0;
        this->entities[i].x = 0;
        this->entities[i].y = 0;
    }
    this->entities[0].sprite_nb = 2;
    this->entities[0].x = 32 << 2;
    this->entities[0].y = 32 << 2;
    this->entities[0].x_sprite = 80;
    this->entities[0].y_sprite = 72;
    this->actual_frame = 0;
    for (int i = 0; i < 2; i++){
        this->entities[0].sprite_ids[i] = i;
        this->entities[0].sprite_tile[i] = i * 2;
        set_sprite_tile(i, i * 2);
    }
}

static void init_graphiques(game_t *this){
    (void)this;
    // apply_color_mapping();
    SWITCH_ROM(BANK(metamorph));
    set_sprite_data(0, metamorph_TILE_COUNT, metamorph_tiles);
    SWITCH_ROM(BANK(menu_tilesets)); 
    set_bkg_data(0, menu_tilesets_TILE_COUNT, menu_tilesets_tiles);
    SWITCH_ROM(BANK(menu_tilemap));
    set_bkg_submap(0, 0, 32, 32, map_menu, map_menu_width);
}

void init_menu(game_t *this)
{
    this->update = &update_menu;
    init_map(this);
    init_graphiques(this);
    init_window(this);
    init_entities(this);
}