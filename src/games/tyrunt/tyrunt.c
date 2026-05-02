/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"

void init_tyrunt(game_t *this)
{
    this->update = &update_tyrunt;

    this->entities[0].x = 30;
}

void handle_input_tyrunt(game_t *this)
{
    (void)this;
}

void update_tyrunt(game_t *this)
{
    handle_input_tyrunt(this);
}
