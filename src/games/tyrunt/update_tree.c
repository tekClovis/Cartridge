/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"

void check_tree_collide(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (collide(this->entities[0].x, this->entities[0].y,
        this->entities[1].x, this->entities[1].y)) {
        data->score = 0;
        data->speed = 1;
        this->entities[1].x = 250;
        SCX_REG -= data->speed;
        move_sprite(4, 0, 0);
        move_sprite(5, 0, 0);
    }
}

void check_tree_score(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (this->entities[1].x == 0 || this->entities[1].x > 250) {
        if (data->score % 10 == 0)
            data->speed += 1;
        this->entities[1].x = 250;
        data->score += 1;
        move_sprite(4, 0, 0);
        move_sprite(5, 0, 0);
    }
}

void update_tree(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (this->entities[1].x >= 250)
        return;
    this->entities[1].x -= data->speed;
    move_sprite(4, this->entities[1].x, this->entities[1].y);
    move_sprite(5, this->entities[1].x + 8, this->entities[1].y);
    check_tree_score(this);
    check_tree_collide(this);
}
