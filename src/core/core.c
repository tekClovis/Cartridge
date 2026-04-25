/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** core
*/

#include "core.h"
#include "game_menu.h"
#include "game_start_screen.h"
#include "font.h"
#include <stdio.h>
#include <string.h>

void init_core(core_t *core)
{
    set_bkg_data(sizeof(uint8_t) - font_TILE_COUNT, font_TILE_COUNT, font_tiles);
    core->actual_game = &core->game[4];
    init_game(core->actual_game, 4);
}

void update_core(core_t *core)
{
    core->actual_game->actual_frame += 1;
    core->actual_game->update(core->actual_game);
}