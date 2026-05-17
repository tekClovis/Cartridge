/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"

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
    move_sprite(0, this->entities[0].x, this->entities[0].y);
    move_sprite(1, this->entities[0].x + 8, this->entities[0].y);
}
