/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** core
*/

#include "core.h"
#include "game_menu.h"
#include <stdio.h>
#include <string.h>

static void (* const init_game_funcs[4])(game_t *game) = {
    &init_menu,
    NULL,
    NULL,
    NULL
};

void init_game(game_t *game, uint8_t id){
    if (id >= 4 || init_game_funcs[id] == NULL)
        return;
    init_game_funcs[id](game);
}

void init_core(core_t *core)
{
    core->actual_game = &core->game[0];
    init_game(core->actual_game, 0);
}

void update_core(core_t *core)
{
    core->actual_game->actual_frame += 1;
    core->actual_game->update(core->actual_game);
}