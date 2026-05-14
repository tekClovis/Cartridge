/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"
#include <stdio.h>
#include "../../assets/tyrunt/gobou_sprites.h"

const unsigned char black_obstacle_tiles[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

const unsigned char black_ground_tiles[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
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

    this->entities[0].x = 24;
    this->entities[0].y = 100; 

    SCX_REG = 0;
    SCY_REG = 0;

    for (uint8_t i = 0; i < 40; i++) {
        move_sprite(i, 0, 0);
    }

    set_sprite_data(0, gobou_sprites_TILE_COUNT, gobou_sprites_tiles);
    
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 2);

    set_bkg_data(0, 2, black_ground_tiles);
    for (uint8_t i = 0; i < 32; i++) {
        unsigned char tile_id = 0; 
        set_bkg_tiles(i, 13, 1, 1, &tile_id);
    }

    set_sprite_data(8, 2, black_obstacle_tiles);
    this->entities[1].x = 200; 
    this->entities[1].y = 100;
    set_sprite_tile(4, 8);

    reset_win();
    SHOW_WIN;
    move_win(7, 120);
}

void handle_input_tyrunt(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if ((joypad() & J_A) && data->is_jumping == 0) {
        data->is_jumping = 1;
        data->velocity_y = -6; 
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
        
        if (this->actual_frame % 2 == 0) {
            data->velocity_y += 1; 
        }

        if (this->entities[0].y >= 100) {
            this->entities[0].y = 100;
            data->velocity_y = 0;
            data->is_jumping = 0;
        }
    }
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
    update_obstacle(this);
    SCX_REG += data->speed;

    uint8_t x = this->entities[0].x;
    uint8_t y = this->entities[0].y;

    move_sprite(0, x, y);
    move_sprite(1, x + 8, y);

    char score_str[20];
    sprintf(score_str, "SCORE %d", data->score);
    printToWin(2, 0, score_str);
}