/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** snake
*/

#include "game_snake.h"

const unsigned char black_tiles[] = {
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00
};

const unsigned char black_player_tiles[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

const void init_snake(game_t *this)
{
    this->update = &update_snake;
    this->entities[0].x = 24;
    this->entities[0].y = 100;
    this->personal_data = &g_game_data.snake;
    snake_plug_in_t *data = (snake_plug_in_t *)this->personal_data;
    data->score = 0;
    data->speed = 1;
    data->direction = UP;
    data->snake_lenght = 1;
    SCX_REG = 0;
    SCY_REG = 0;
    set_sprite_data(0, 2, black_player_tiles);
    set_bkg_data(0, 2, black_tiles);

    // Sol
    for (uint8_t i = 0; i < 32; i++) {
        unsigned char tile_id = 0; 
        set_bkg_tiles(i, 13, 1, 1, &tile_id);
    }
    set_sprite_tile(0, 0);

    // Obstacles
    set_sprite_data(4, 2, black_player_tiles);
    this->entities[1].x = 200;
    this->entities[1].y = 100;
    set_sprite_tile(2, 4);

    reset_win();
    SHOW_WIN;
    move_win(7, 120);
}

const void update_snake(game_t *this)
{
    move_sprite(0, this->entities[0].x, this->entities[0].y);
    handle_input_snake(this);
}

static const void handle_input_snake(game_t *this)
{
    if ((joypad() & J_SELECT)) {
        HIDE_WIN;
        init_game(this, MENU); 
    }
}
