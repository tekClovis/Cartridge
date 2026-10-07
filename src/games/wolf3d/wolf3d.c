/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** wolf3d
*/
/**
 * @file wolf3d.c
 * @brief Wolf3D game setup and per-frame update.
 */

#include "game_wolf3d.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** @brief Ray step lookup, (128 << 8) / i, filled by init_wolf3d. */
uint16_t ray_lut[256];

static const void init_graphics(void)
{
    set_bkg_data(0, ray_TILE_COUNT, raycaster_tiles);
    set_sprite_data(0, machop_tiles_TILE_COUNT, machop_tiles_tiles);
    set_sprite_data(machop_tiles_TILE_COUNT, gun_tileset_TILE_COUNT, gun_tileset_tiles);
}

/** @brief Place the HUD window at y = 124 and print the score. */
static const void init_window(game_t *game)
{
    char buffer[32] = {0};

    move_bkg(0, 0);
    game->window[1].x = 0;
    game->window[1].y = 124;
    print_score_life(game);
    move_win(game->window[1].x, game->window[1].y);
    SHOW_WIN;
    printToWin(1, 0, buffer);

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

/** @brief Per-frame update: process input. */
const void update_wolf3d(game_t *this)
{
    handle_input(this);
}

/**
 * @brief Initialise Wolf3D: lookup table, map size, score (500), graphics, entities, HUD, view.
 * @param this Game state.
 */
const void init_wolf3d(game_t *this)
{
    ray_lut[0] = (128u << 8) / 128;
    for (int i = 1; i < 256; i++)
        ray_lut[i] = (128u << 8) / i;
    this->update = &update_wolf3d;
    this->map.size = map_level_1.size;
    this->map.width = map_level_1.width;
    this->map.height = map_level_1.height;
    this->score = 500;
    this->game_over = 0;
    init_graphics();
    init_ent(this);
    init_window(this);
    init_raycasting(this);
}