/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"

void manage_spawner(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    uint8_t random_val = DIV_REG;
    int16_t safe_gap = 80 + (random_val % 40);

    if (data->spawn_timer > 0) {
        data->spawn_timer--;
        return;
    }
    if (random_val % 2 == 0) {
        if (this->entities[1].x >= 250) {
            this->entities[1].x = 160;
            data->spawn_timer = safe_gap;
        }
    }
    if (random_val % 2 == 1) {
        if (this->entities[2].x >= 250) {
            this->entities[2].x = 160;
            data->spawn_timer = safe_gap;
        }
    }
}
