/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** wolf3d
*/
#include "game_wolf3d.h"

static const void init_graphics(void)
{
    set_bkg_data(0, ray_TILE_COUNT, raycaster_tiles);
}

static const void init_window(game_t *game)
{
    game->window[0].x = 0;
    game->window[0].y = 0;
    move_win(game->window[0].x, game->window[0].y);
}

static const void init_ent(game_t *game)
{
    for (uint8_t i = 0; i < game->map.size; i++) {
        if (game->map.map[i] == SPAWN) {
            game->entities[0].x = (i % game->map.width) << 3;
            game->entities[0].y = (i / game->map.width) << 3;
            break;
        }
    }
    game->entities[0].angle = 8;
}

void update_wolf3d(game_t *this)
{
    handle_input(this);
    draw_background(this);
}

void init_wolf3d(game_t *this)
{
    this->update = &update_wolf3d;
    this->map = map_level_1;
    init_graphics();
    init_ent(this);
    init_window(this);
}