/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"

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
