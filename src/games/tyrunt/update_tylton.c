/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"

void check_tylton_collide(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (data->invincible_timer > 0)
        return;
    if (collide(this->entities[0].x, this->entities[0].y,
            this->entities[2].x, this->entities[2].y)) {
        data->score = 0;
        data->speed = 1;
        this->entities[2].x = 250;
        SCX_REG -= data->speed;
        move_sprite(8, 0, 0);
        move_sprite(9, 0, 0);
        trigger_game_over(this);
    }
}

void check_tylton_score(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (this->entities[2].x == 0 || this->entities[2].x > 250) {
        this->entities[2].x = 250;
        data->score += 1;
        move_sprite(8, 0, 0);
        move_sprite(9, 0, 0);
    }
}

void update_tylton(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    uint8_t current_tylton_speed = data->speed;

    if (this->entities[2].x >= 250)
        return;
    if (this->actual_frame % 3 == 0) {
        current_tylton_speed += 1;
    }
    this->entities[2].x -= current_tylton_speed;
    move_sprite(8, this->entities[2].x, this->entities[2].y);
    move_sprite(9, this->entities[2].x + 8, this->entities[2].y);
    check_tylton_score(this);
    check_tylton_collide(this);
    animate_tylton(this);
}
