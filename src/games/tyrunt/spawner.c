/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"

static void spawn_bonus(game_t *this)
{
    if (DIV_REG % 600 == 0) {
        this->entities[3].x = 160;
        if (DIV_REG % 2 == 0) {
            this->entities[3].y = 112;
        } else {
            this->entities[3].y = 65;
        }
    }
}

static void manage_bonus(game_t *this)
{
    if (this->entities[3].x >= 250)
        spawn_bonus(this);
}

static uint8_t get_obstacle_to_spawn(game_t *this)
{
    uint8_t primary = 2;
    uint8_t fallback = 1;

    if (DIV_REG % 2 == 0) {
        primary = 1;
        fallback = 2;
    }
    if (this->entities[primary].x >= 250)
        return primary;
    if (this->entities[fallback].x >= 250)
        return fallback;
    return 0;
}

void manage_spawner(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    int16_t safe_gap = 80 + (DIV_REG % 40);
    uint8_t target = 0;

    manage_bonus(this);
    if (data->spawn_timer > 0) {
        data->spawn_timer--;
        return;
    }
    if ((this->entities[1].x < 250 && this->entities[1].x > 80) ||
        (this->entities[2].x < 250 && this->entities[2].x > 80)) {
        return;
    }
    target = get_obstacle_to_spawn(this);
    if (target != 0) {
        this->entities[target].x = 160;
        data->spawn_timer = safe_gap;
    }
}
