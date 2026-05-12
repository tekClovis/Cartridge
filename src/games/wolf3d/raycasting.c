/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** raycasting
*/

#include "game_wolf3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* raycaster_tiles.c */
const uint8_t raycaster_tiles[128] = {
    /* TILE_BLANK = 0 */
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
    /* TILE_WALL_FAR = 1 */
    0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00,
    /* TILE_WALL_MED = 2 */
    0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF,
    /* TILE_WALL_NEAR = 3 */
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF,
    /* TILE_CAP_TOP_MED = 4 */
    0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
    /* TILE_CAP_BOT_MED = 5 */
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF,
    /* TILE_CAP_TOP_NEAR = 6 */
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
    /* TILE_CAP_BOT_NEAR = 7 */
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF,
};

/* tile index defines */
#define TILE_BLANK           font_BLANK_TILE
#define TILE_WALL_FAR        1U
#define TILE_WALL_MED        2U
#define TILE_WALL_NEAR       3U
#define TILE_CAP_TOP_MED     4U
#define TILE_CAP_BOT_MED     5U
#define TILE_CAP_TOP_NEAR    6U
#define TILE_CAP_BOT_NEAR    7U

/* distance → tile lookup */
static const uint8_t wall_shade[8] = {
    0,
    17,
    35,
    53,
    71,
    89,
    107,
    125,
};

static const uint8_t wall_col_map[144] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 0,
    0, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 1, 0,
    0, 0, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 1, 1, 0,
    0, 0, 0, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2, 5, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0,
};

static const int8_t sin_tab[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, -7, -6, -5, -4, -3, -2, -1};

#define COS(angle) sin_tab[((angle) + 4) >> 4]
#define SIN(angle) sin_tab[(angle) & 15 >> 4]

const uint8_t calc_dist(const uint8_t x1, const uint8_t y1, const uint8_t x2, const uint8_t y2)
{
    uint8_t d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

    d = (d >> 3) + (d >> 5) + (d >> 7);
    return d;
}

static uint8_t cast_ray(const game_t *game, uint8_t ray_id)
{
    const uint8_t angle = game->entities[0].angle + (ray_id - 10) * 8;
    const int8_t dir_x = COS(angle);
    const int8_t dir_y = SIN(angle);
    int16_t pos_x = game->entities[0].x;
    int16_t pos_y = game->entities[0].y;

    if ((dir_x == 0) && (dir_y == 0))
        return 8U;

    while (pos_x >= 0 && pos_x < ((int16_t)game->map.width << 3)
        && pos_y >= 0 && pos_y < ((int16_t)game->map.height << 3)) {
        pos_x += dir_x;
        pos_y += dir_y;
        if (game->map.map[(pos_y >> 3) * game->map.width + (pos_x >> 3)] == WALL) {
            return calc_dist(game->entities[0].x >> 3, game->entities[0].y >> 3, pos_x >> 3, pos_y >> 3);
        }
    }
    return 8U;
}

const void draw_background(game_t *game)
{
    uint8_t ray_dist = 0;
    w3d_plug_in_t *raycaster = (w3d_plug_in_t *)game->personal_data;
    move_win(0, 120);
    SHOW_WIN;

    for (uint8_t i = 0; i < 20; i++) {
        ray_dist = cast_ray(game, i);
        if (ray_dist > 7)
            ray_dist = 7;
        if (raycaster->last_rays[i] == (int8_t)ray_dist)
            continue;
        raycaster->last_rays[i] = ray_dist;
        set_bkg_tiles(i, 0, 1, 18, &wall_col_map[wall_shade[ray_dist]]);
    }
}
