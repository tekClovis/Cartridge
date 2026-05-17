/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"

void update_obstacle(game_t *this)
{
    manage_spawner(this);
    update_tree(this);
    update_tylton(this);
}

void update_timers(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (data->invincible_timer > 0)
        data->invincible_timer -= 1;
    if (data->slow_timer > 0)
        data->slow_timer -= 1;
}

void update_tyrunt(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    handle_input_tyrunt(this);
    update_player(this);
    animate_player(this);
    update_obstacle(this);
    update_score(this);
    update_bonus(this);
    update_timers(this);
    SCX_REG += data->speed;
}
