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
    18,
    36,
    54,
    72,
    90,
    108,
    126,
};

static const uint8_t wall_col_map[144] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 0,
    0, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 0, 0,
    0, 0, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 0, 0, 0,
    0, 0, 0, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2, 5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
};

static uint8_t cast_ray(const game_t *game, int8_t ray_id)
{
    const uint8_t angle = (uint8_t)(((w3d_ent_plug_in_t *)game->entities[0].personal_data)->angle + ray_id - 9) & 127;
    int8_t rdx = COS(angle);
    int8_t rdy = SIN(angle);
    int8_t step_x = (rdx) > 0 ? 1 : -1;
    int8_t step_y = (rdy) > 0 ? 1 : -1;
    uint16_t delta_dist_x = ray_lut[rdx > 0 ? rdx : -rdx];
    uint16_t delta_dist_y = ray_lut[rdy > 0 ? rdy : -rdy];
    uint8_t tile_x = FLOAT_TO_INT(game->entities[0].x);
    uint8_t tile_y = FLOAT_TO_INT(game->entities[0].y);
    int16_t side_dist_x = 0;
    int16_t side_dist_y = 0;
    int8_t side = 0;
    int8_t distance = 0;

    if (step_x > 0)
        side_dist_x = (game->entities[0].x & 0x80) ? delta_dist_x >> 1 : delta_dist_x;
    else
        side_dist_x = (game->entities[0].x & 0x80) ? delta_dist_x >> 1 : 0;
    if (step_y > 0)
        side_dist_y = (game->entities[0].y & 0x80) ? delta_dist_y >> 1 : delta_dist_y;
    else
        side_dist_y = (game->entities[0].y & 0x80) ? delta_dist_y >> 1 : 0;
    side = side_dist_x < side_dist_y; 
    for (; distance < 20; distance++) {
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            tile_x += step_x;
            side = 0;
        } else {
            side_dist_y += delta_dist_y;
            tile_y += step_y;
            side = 1;
        }
        if (tile_x >= game->map.width || tile_y >= game->map.height)
            break;
        if (game->map.map[(tile_y << 5) + (tile_x)] == WALL)
            break;
    }
    if (side == 0)
        distance = (side_dist_x - delta_dist_x);
    else
        distance = (side_dist_y - delta_dist_y);
    if (distance < 0)
        distance = 0;

    return distance;
}

const void draw_background(game_t *game)
{
    uint8_t ray_dist = 0;
    w3d_plug_in_t *raycaster = (w3d_plug_in_t *)game->personal_data;
    move_win(0, 120);
    SHOW_WIN;

    for (uint8_t i = 0; i < 20; i++) {
        ray_dist = cast_ray(game, i);
        if (8 < ray_dist)
            ray_dist = 7;
        if (raycaster->last_rays[i] == (int8_t)ray_dist)
            continue;
        raycaster->last_rays[i] = ray_dist;
        set_bkg_tiles(i, 0, 1, 18, &wall_col_map[wall_shade[ray_dist]]);
    }
}
