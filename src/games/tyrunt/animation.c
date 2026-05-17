/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"

void animate_player(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    uint8_t base_tile = 0;
    uint8_t anim_step = 0;

    if (data->is_jumping && data->velocity_y < 0) {
        base_tile = 4;
    }
    if (data->is_jumping && data->velocity_y >= 0) {
        base_tile = 8;
    }
    if (!data->is_jumping) {
        anim_step = (this->actual_frame / 10) % 3;
        base_tile = anim_step * 4;
    }
    set_sprite_tile(0, base_tile);
    set_sprite_tile(1, base_tile + 2);
}

void animate_tylton(game_t *this)
{

    uint8_t anim_step = (this->actual_frame / 15) % 2;

    if (anim_step == 0) {
        set_sprite_tile(8, 16);
        set_sprite_tile(9, 18);
    } else {
        set_sprite_tile(8, 20);
        set_sprite_tile(9, 22);
    }
}
