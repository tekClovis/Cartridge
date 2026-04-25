/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** utils
*/
#include "game.h"
#include "game_menu.h"
#include "font.h"
#include "game_start_screen.h"

static void (* const init_game_funcs[5])(game_t *game) = {
    &init_menu,
    NULL,
    NULL,
    NULL,
    &init_start_screen
};

void printToMap(const game_t *game, uint8_t x, uint8_t y, char string[256])
{
    for (uint8_t i = 0; string[i] && i < 256; i++){
        set_bkg_tile_xy(game->window[0].x + x + i, game->window[0].y + y, ASCII_TO_TILE(string[i]));
    }
}

void init_game(game_t *game, uint8_t id){
    DISPLAY_OFF;
    if (id > 4 || init_game_funcs[id] == NULL)
        return;
    init_game_funcs[id](game);
    DISPLAY_ON;
}