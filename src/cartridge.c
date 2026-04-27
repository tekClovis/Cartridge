/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** cartride
*/
#include "game.h"
#include <gb/cgb.h>
#include <gb/sgb.h>
#include <string.h>

static const void init(game_t *game)
{
    HIDE_BKG;
    HIDE_WIN;
    HIDE_SPRITES;
    SPRITES_8x16;
    cpu_fast();
    memset(game, 0, sizeof(*game));
    set_bkg_data(sizeof(uint8_t) - font_TILE_COUNT
    , (uint8_t)font_TILE_COUNT, font_tiles);
    init_game(game, WOLF_3D);
    SHOW_BKG;
    SHOW_SPRITES;
}

static const void update(game_t *game)
{
    game->actual_frame++;
    game->update(game);
}

int main(void){
    game_t game;

    init(&game);
    while (1){
        update(&game);
        vsync();
    }
}
