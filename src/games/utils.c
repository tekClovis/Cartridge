/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** utils
*/
#include "game.h"
#include "game_menu.h"
#include "game_start_screen.h"
#include "font.h"
#include <stdio.h>
#include <string.h>
#include <gb/cgb.h>

static const void (* const init_game_funcs[5])(game_t *game) = {
    &init_start_screen,
    &init_menu,
    NULL,
    NULL,
    NULL,
};

const void printToMap(const game_t *game, uint8_t x, uint8_t y, char string[256])
{
    int pc = 0;

    for (uint8_t i = 0; string[i]; i++){
        if (string[i] == '\n')
            x = 21;
        if (x + i > 20){
            y++;
            pc = 0;
        }
        set_bkg_tile_xy(game->window[0].x + x + pc, game->window[0].y + y, ASCII_TO_TILE(string[i]));
        pc++;
    }
}

const void printToWin(const game_t *game, uint8_t x, uint8_t y, char string[256])
{
    int pc = 0;

    for (uint8_t i = 0; string[i]; i++){
        if (string[i] == '\n')
            x = 21;
        if (x + i > 20){
            y++;
            pc = 0;
        }
        set_win_tile_xy(game->window[0].x + x + pc, game->window[0].y + y, ASCII_TO_TILE(string[i]));
        pc++;
    }
}

static void clear_sprite_tiles(void) {
    uint8_t i;
    for (i = 0; i < 40; i++) {
        set_sprite_tile(i, 207);
    }
}

const void init_game(game_t *game, game_id id){
    if (id != START_SCREEN)
        fade_out();
    DISPLAY_OFF;
    clear_sprite_tiles();
    if (id > sizeof(game_id) || init_game_funcs[id] == NULL)
        return;
    init_game_funcs[id](game);
    DISPLAY_ON;
    fade_in();
}

