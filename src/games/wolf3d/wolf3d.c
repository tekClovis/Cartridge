/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** wolf3d
*/
#include "game_wolf3d.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint16_t ray_lut[256];

static const void init_graphics(void)
{
    set_bkg_data(0, ray_TILE_COUNT, raycaster_tiles);
}

static const void init_window(game_t *game)
{
    char buffer[32] = {0};

    game->window[0].x = 0;
    game->window[0].y = 0;
    sprintf(buffer, " SCORE %d%d\nHP %d%d",
            (game->score / 10), (game->score % 0x0A),
            (game->entities[0].life / 10), (game->entities[0].life % 0x0A));
    move_win(game->window[0].x, game->window[0].y);
    printToWin(2, 0, buffer);

}

static const void init_ent(game_t *game)
{

    for (int i = 0; i < MAX_ENTITIES; i++){
        g_ent_data.wolf3d.angles[i] = 0;
    }
    init_player(game);
    initialize_ennemies(game);
}

static const void init_raycasting(game_t *this)
{
     for (int i = 0; i < 20; i++){
        g_game_data.wolf3d.last_rays[i] = -1;
        g_game_data.wolf3d.rays[i] = -1;
        g_game_data.wolf3d.side[i] = -1;
        g_game_data.wolf3d.x_tiles_touch[i] = -1;
        g_game_data.wolf3d.y_tiles_touch[i] = -1;
    }
    this->personal_data = &g_game_data.wolf3d;
    draw_background(this);
}

const void update_wolf3d(game_t *this)
{
    handle_input(this);
}

const void init_wolf3d(game_t *this)
{
    ray_lut[0] = (128u << 8) / 128;
    for (int i = 1; i < 256; i++)
        ray_lut[i] = (128u << 8) / i;
    this->update = &update_wolf3d;
    this->map.size = map_level_1.size;
    this->map.width = map_level_1.width;
    this->map.height = map_level_1.height;
    init_graphics();
    init_ent(this);
    init_window(this);
    init_raycasting(this);
}