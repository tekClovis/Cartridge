/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** raycasting
*/

#include "game_wolf3d.h"
#include <stdio.h>
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
const uint8_t wall_shade[] = {
    TILE_WALL_FAR,   /* dist 7+ */
    TILE_WALL_FAR,
    TILE_WALL_MED,   /* dist 4-5 */
    TILE_WALL_MED,
    TILE_WALL_NEAR,  /* dist 1-2 */
    TILE_WALL_NEAR,
    TILE_WALL_NEAR,
    TILE_WALL_NEAR,
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

const uint8_t calc_dist(const uint8_t x1, const uint8_t y1, const uint8_t x2, const uint8_t y2)
{
    uint8_t d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

    d = (d >> 3) + (d >> 5) + (d >> 7);
    return d;
}

static uint8_t cast_ray(const game_t *game, uint8_t ray_id)
{
    const uint8_t angle = ray_id;
    const int8_t dir_x = COS(angle);
    const int8_t dir_y = SIN(angle);
    int16_t pos_x = game->entities[0].x;
    int16_t pos_y = game->entities[0].y;

    // Calculate our exact step increment (Scaled by Cos/Sin)
    int16_t step_x = COS(angle); 
    int16_t step_y = SIN(angle); 

    uint8_t distance = 0;

    while (distance < 9) {
        // ray_x_sub += step_x;
        // ray_y_sub += step_y;
        
        // // Shift back down to calculate exactly which tile we are standing in
        // uint16_t tile_x = ray_x_sub >> (5); 
        // uint16_t tile_y = ray_y_sub >> (5);
        
        // if (map_level_1.map[(tile_y << 5) + tile_x] == WALL) {
        //     return distance;
        // }
        distance++;
    }
    return distance;
}

const void draw_background(game_t *game)
{
    uint8_t ray_dist = 0;
    // uint8_t frame_buffer[20 * 18];

    // move_win(0, 128);
    // reset_bkg();
    for (uint8_t i = 0; i < 20; i++) {
        ray_dist = cast_ray(game, i);
        if (8 < ray_dist)
            ray_dist = 7;
        // for (uint8_t j = 0; j < 18; j++)
        //     frame_buffer[(j << 4) + i] = wall_col_map[(ray_dist << 4) + j];
        // set_bkg_tiles(i, 0, 1, 18, wall_col_map + (ray_dist << 4));
    }
}
