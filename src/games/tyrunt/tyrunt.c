/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"
#include <stdio.h>
#include "../../assets/tyrunt/gobou_spritesheet.h"

// Sol texturé
const unsigned char textured_ground_tiles[] = {
    0xFF, 0xBD, 0xFF, 0xDB, 0xFF, 0xE7, 0xFF, 0xBD,
    0xFF, 0xDB, 0xFF, 0xE7, 0xFF, 0xBD, 0xFF, 0xDB
};

// Un nuage
const unsigned char cloud_tiles[] = {
    0x00,0x00, 0x00,0x00, 0x0E,0x0E, 0x1F,0x1F, 0x3F,0x3F, 0x7F,0x7F, 0xFF,0xFF, 0x00,0x00,
    0x00,0x00, 0x30,0x30, 0x70,0x70, 0xF8,0xF8, 0xFC,0xFC, 0xFE,0xFE, 0xFF,0xFF, 0x00,0x00
};

// Rocher
const unsigned char rock_tiles[] = {
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x18,0x18, 0x3C,0x3C, 0x7E,0x66, 0xFF,0xDB, 0xFF,0xFF,
    0xFF,0xC3, 0xFF,0xBD, 0xFF,0xFF, 0xFF,0x7E, 0xFF,0xFF, 0x7E,0x3C, 0x3C,0x18, 0x00,0x00
};

void init_tyrunt(game_t *this)
{
    this->update = &update_tyrunt;

    this->personal_data = &g_game_data.tyrunt;
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    data->velocity_y = 0;
    data->is_jumping = 0;
    data->score = 0;
    data->speed = 1;

    SCX_REG = 0;
    SCY_REG = 0;

    for (uint8_t i = 0; i < 40; i++) {
        move_sprite(i, 0, 0);
        set_sprite_prop(i, 0);
    }

    // Gobou
    set_sprite_data(0, gobou_spritesheet_TILE_COUNT, gobou_spritesheet_tiles);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 2);
    this->entities[0].x = 24;
    this->entities[0].y = 104; 

    // Sol
    set_bkg_data(0, 1, textured_ground_tiles);
    for (uint8_t i = 0; i < 32; i++) {
        unsigned char tile_id = 0; 
        set_bkg_tiles(i, 13, 1, 1, &tile_id);
        set_bkg_tiles(i, 14, 1, 1, &tile_id);
    }

    // Nuages
    set_bkg_data(1, 2, cloud_tiles);
    unsigned char cloud_map[2] = {1, 2};
    set_bkg_tiles(3, 3, 2, 1, cloud_map);
    set_bkg_tiles(14, 5, 2, 1, cloud_map);
    set_bkg_tiles(24, 2, 2, 1, cloud_map);

    // Rocher
    set_sprite_data(12, 2, rock_tiles);
    this->entities[1].x = 200; 
    this->entities[1].y = 104;
    set_sprite_tile(4, 12);

    reset_win();
    SHOW_WIN;
    move_win(7, 120);
}

void handle_input_tyrunt(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if ((joypad() & J_A) && data->is_jumping == 0) {
        data->is_jumping = 1;
        data->velocity_y = -5; 
    }

    if ((joypad() & J_SELECT)) {
        HIDE_WIN;
        init_game(this, MENU); 
    }
}

void update_player(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (data->is_jumping) {
        this->entities[0].y += data->velocity_y;
        
        if (this->actual_frame % 4 == 0) {
            data->velocity_y += 1; 
        }

        if (this->entities[0].y >= 104) {
            this->entities[0].y = 104;
            data->velocity_y = 0;
            data->is_jumping = 0;
        }
    }
}

void animate_player(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    uint8_t base_tile = 0;
    uint8_t anim_step = 0;

    if (data->is_jumping) {
        if (data->velocity_y < 0) {
            base_tile = 4;
        } 
        else {
            base_tile = 8;
        }
    } else {
        anim_step = (this->actual_frame / 10) % 3;
        base_tile = anim_step * 4;
    }
    set_sprite_tile(0, base_tile);
    set_sprite_tile(1, base_tile + 2);
}

void update_obstacle(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    this->entities[1].x -= data->speed;

    if (this->entities[1].x == 0 || this->entities[1].x > 200) {
        this->entities[1].x = 200;
        data->score += 1;
        
        if (data->score % 5 == 0) {
            data->speed += 1; 
        }
    }

    move_sprite(4, this->entities[1].x, this->entities[1].y);

    if (this->entities[0].x + 12 > this->entities[1].x && 
        this->entities[0].x < this->entities[1].x + 6 &&
        this->entities[0].y + 16 > this->entities[1].y) {
        
        data->score = 0;
        data->speed = 1;
        this->entities[1].x = 200;
        SCX_REG -= data->speed; 
    }
}

void update_tyrunt(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    handle_input_tyrunt(this);
    update_player(this);
    animate_player(this);
    update_obstacle(this);
    SCX_REG += data->speed;

    uint8_t x = this->entities[0].x;
    uint8_t y = this->entities[0].y;

    move_sprite(0, x, y);
    move_sprite(1, x + 8, y);

    char score_str[20];
    sprintf(score_str, "SCORE %d    ", data->score);
    printToWin(2, 0, score_str);
}