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

void printToMap(uint8_t x, uint8_t y, char string[255])
{
    for (uint8_t i = 0; string[i] != '\0'; i++){
        set_bkg_tile_xy(x + i, y, ASCII_TO_TILE(string[i]));
    }
}

void init_game(game_t *game, uint8_t id){
    if (id >= 5 || init_game_funcs[id] == NULL)
        return;
    init_game_funcs[id](game);
}