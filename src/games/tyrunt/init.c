/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"
#include "../../assets/tyrunt/gobou_spritesheet.h"
#include "../../assets/tyrunt/tylton_spritesheet.h"
#include "../../assets/tyrunt/tree_sprite.h"

const unsigned char textured_ground_tiles[] = {
    0xFF, 0xBD, 0xFF, 0xDB, 0xFF, 0xE7, 0xFF, 0xBD,
    0xFF, 0xDB, 0xFF, 0xE7, 0xFF, 0xBD, 0xFF, 0xDB
};

const unsigned char cloud_tiles[] = {
    0x00,0x00, 0x00,0x00, 0x0E,0x0E, 0x1F,0x1F, 0x3F,0x3F, 0x7F,0x7F, 0xFF,0xFF, 0x00,0x00,
    0x00,0x00, 0x30,0x30, 0x70,0x70, 0xF8,0xF8, 0xFC,0xFC, 0xFE,0xFE, 0xFF,0xFF, 0x00,0x00
};

static void init_mudkip(game_t *this)
{
    set_sprite_data(0, gobou_spritesheet_TILE_COUNT, gobou_spritesheet_tiles);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 2);
    this->entities[0].x = 24;
    this->entities[0].y = 104; 
}

static void init_ground(void)
{
    unsigned char tile_id = 0;

    set_bkg_data(0, 1, textured_ground_tiles);
    for (uint8_t i = 0; i < 32; i++) { 
        set_bkg_tiles(i, 13, 1, 1, &tile_id);
        set_bkg_tiles(i, 14, 1, 1, &tile_id);
    }
}

static void init_tylton(game_t *this)
{
    set_sprite_data(16, tylton_spritesheet_TILE_COUNT, tylton_spritesheet_tiles);
    set_sprite_tile(8, 16);
    set_sprite_tile(9, 18);
    this->entities[2].x = 250;
    this->entities[2].y = 70;
    move_sprite(8, 0, 0);
    move_sprite(9, 0, 0);
}

static void init_tree(game_t *this)
{
    set_sprite_data(12, tree_sprite_TILE_COUNT, tree_sprite_tiles);
    this->entities[1].x = 250;
    this->entities[1].y = 104;
    set_sprite_tile(4, 12);
    set_sprite_tile(5, 14);
}

static void init_clouds(void)
{
    unsigned char cloud_map[2] = {1, 2};

    set_bkg_data(1, 2, cloud_tiles);
    set_bkg_tiles(3, 3, 2, 1, cloud_map);
    set_bkg_tiles(14, 5, 2, 1, cloud_map);
    set_bkg_tiles(24, 2, 2, 1, cloud_map);
}

static void init_game_data(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    data->velocity_y = 0;
    data->is_jumping = 0;
    data->score = 0;
    data->speed = 1;
    data->spawn_timer = 0;
    SCX_REG = 0;
    SCY_REG = 0;
    for (uint8_t i = 0; i < 40; i++) {
        move_sprite(i, 0, 0);
        set_sprite_prop(i, 0);
    }
    reset_win();
    SHOW_WIN;
    move_win(7, 120);
}

void init_tyrunt(game_t *this)
{
    tyrunt_plug_in_t *data = NULL;

    this->update = &update_tyrunt;
    this->personal_data = &g_game_data.tyrunt;
    init_game_data(this);
    init_mudkip(this);
    init_ground();
    init_clouds();
    init_tree(this);
    init_tylton(this);
}
