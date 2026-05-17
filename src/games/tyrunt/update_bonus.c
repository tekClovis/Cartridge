/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"

void give_bonus(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    uint8_t random_bonus = DIV_REG % 4;

    switch (random_bonus) {
        case 0:
            data->score += 5;
            break;
        case 1:
            data->invincible_timer = 300;
            break;
        case 2:
            data->double_jumps_left = 1;
            break;
        case 3:
            data->slow_timer = 300;
            break;
    }
}

void check_bonus_collide(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (collide(this->entities[0].x, this->entities[0].y,
            this->entities[3].x, this->entities[3].y)) {
        give_bonus(this);
        this->entities[3].x = 250;
        move_sprite(10, 0, 0);
    }
}

void check_bonus_missed(game_t *this)
{
    if (this->entities[3].x == 0 || this->entities[3].x > 250) {
        this->entities[3].x = 250;
        move_sprite(10, 0, 0);
    }
}

void update_bonus(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (this->entities[3].x >= 250)
        return;
    this->entities[3].x -= data->speed;
    move_sprite(10, this->entities[3].x, this->entities[3].y);
    check_bonus_collide(this);
    check_bonus_missed(this);
}
