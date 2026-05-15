/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** utils
*/
#include "game.h"
#include "game_menu.h"
#include "game_start_screen.h"
#include "game_wolf3d.h"
#include "game_tyrunt.h"
#include "font.h"
#include <stdlib.h>

// definition of globals of the Union
active_game_data_t g_game_data;
active_ent_data_t g_ent_data;


static const void clear_sprite_tiles(void) {
    uint8_t i;
    for (i = 0; i < 40; i++) {
        set_sprite_tile(i, font_BLANK_TILE);
    }
}
static const void (* const init_game_funcs[GAME_ID_COUNT])(game_t *game) = {
    &init_start_screen,
    &init_menu,
    &init_wolf3d,
    &init_tyrunt,
    NULL,
};

const void init_game(game_t *game, game_id id){
    if (id != START_SCREEN)
        fade_out();
    DISPLAY_OFF;
    clear_sprite_tiles();
    reset_bkg();
    reset_win();
    if (id >= GAME_ID_COUNT || init_game_funcs[id] == NULL)
        return;
    init_game_funcs[id](game);
    DISPLAY_ON;
    fade_in();
}

const int8_t point_in_rect(const uint8_t x, const uint8_t y,
    const rectangle_t *rect)
{
    return (x >= rect->x && x < rect->x + rect->width &&
        y >= rect->y && y < rect->y + rect->height);
}
