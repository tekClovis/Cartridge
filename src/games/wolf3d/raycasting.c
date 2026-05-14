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
const uint8_t raycaster_tiles[272] = {
        /* TILE_BLANK = 0 */
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
        /* TILE_WALL_NEAR = 1 */
    0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00,
        /* TILE_WALL_MED = 2 */
    0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF,
        /* TILE_CAP_TOP_MED =  3*/
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0xFF,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF,
        /* TILE_CAP_BOT_MED = 4 */
    0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0xFF,0xFF, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00,
        /* TILE_CAP_TOP_FLAT = 5 */
    0xFF,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF,
        /* TILE_CAP_BOT_FLAT = 6 */
    0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0x00,0xFF, 0xFF,0xFF,
    // right side rays
        /* TILE_WALL_MED_RIGHT = 7 */
    0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF,
        /* TILE_CAP_TOP_MED = 8 */
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0xFF,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF,
        /* TILE_CAP_BOT_MED = 9 */
    0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0xFF,0xFF, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00,
        /* TILE_CAP_TOP_FLAT = 10 */
    0xFF,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF,
        /* TILE_CAP_BOT_FLAT = 11 */
    0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0x01,0xFF, 0xFF,0xFF,
    // left side rays
        /* TILE_WALL_MED = 12 */
    0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF,
        /* TILE_CAP_TOP_MED = 13 */
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0xFF,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF,
        /* TILE_CAP_BOT_MED = 14 */
    0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0xFF,0xFF, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00, 0xFF,0x00,
        /* TILE_CAP_TOP_FLAT = 15 */
    0xFF,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF,
        /* TILE_CAP_BOT_FLAT = 16 */
    0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0x80,0xFF, 0xFF,0xFF,
};

/* distance → tile lookup */
static const uint8_t wall_shade[14] = {
    0,
    18,
    36,
    54,
    72,
    90,
    108,
    126,
    144,
    162,
    180,
    198,
    216,
    234,
};

static const uint8_t wall_col_map[256] = {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
    3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 0,
    0, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 1, 0,
    0, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 0,
    0, 0, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 1, 1, 0,
    0, 0, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 0,
    0, 0, 0, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 1, 1, 1, 0,
    0, 0, 0, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 1, 0,
    0, 0, 0, 0, 5, 2, 2, 2, 2, 2, 2, 2, 6, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 3, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 5, 2, 2, 2, 2, 2, 6, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 3, 2, 2, 2, 2, 2, 4, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 5, 2, 2, 2, 6, 1, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 3, 2, 2, 2, 4, 1, 1, 1, 1, 1, 1, 0,
};

static int16_t ray_diff(int8_t a, int8_t b)
{
    return (int16_t)a - (int16_t)b;
}

static const void display_col(w3d_plug_in_t *raycaster, int i)
{
    uint8_t buffer[18];
    int8_t normalized_dist = raycaster->rays[i] > 13 ? 13 : raycaster->rays[i];

    if (i == 0)
        return set_bkg_tiles(i, 0, 1, 18, &wall_col_map[wall_shade[normalized_dist]]);
    if (raycaster->side[i - 1] != raycaster->side[i] && raycaster->side[i] == raycaster->side[i - 1]) {
        for (uint8_t j = 0; j < 18; j++){
            if (wall_col_map[wall_shade[normalized_dist] + j] < 2)
                buffer[j] = wall_col_map[wall_shade[normalized_dist] + j];
            else
                buffer[j] = wall_col_map[wall_shade[normalized_dist] + j] + 10;
        }
    } else if (raycaster->side[i + 1] != raycaster->side[i] && raycaster->side[i] == raycaster->side[i + 1]) {
        for (uint8_t j = 0; j < 18; j++){
            if (wall_col_map[wall_shade[normalized_dist] + j] < 2)
                buffer[j] = wall_col_map[wall_shade[normalized_dist] + j];
            else
                buffer[j] = wall_col_map[wall_shade[normalized_dist] + j] + 5;
        }
    } else {
        return set_bkg_tiles(i, 0, 1, 18, &wall_col_map[wall_shade[normalized_dist]]);
    }
    set_bkg_tiles(i, 0, 1, 18, buffer);
}

static const uint16_t cast_ray(const game_t *game, uint8_t ray_id)
{
    const uint8_t angle = (uint8_t)(((w3d_ent_plug_in_t *)game->entities[0].personal_data)->angle + ray_id - 10) & 127;
    int16_t rdx = COS(angle);
    int16_t rdy = SIN(angle);
    int8_t step_x = (rdx > 0) ? 1 : (rdx < 0 ? -1 : 0);
    int8_t step_y = (rdy > 0) ? 1 : (rdy < 0 ? -1 : 0);
    uint16_t abs_rdx = (rdx >= 0) ? (uint16_t)rdx : (uint16_t)(-rdx);
    uint16_t abs_rdy = (rdy >= 0) ? (uint16_t)rdy : (uint16_t)(-rdy);
    int32_t delta_dist_x = (rdx == 0) ? sizeof(int32_t) : ((int32_t)ray_lut[abs_rdx] << 8);
    int32_t delta_dist_y = (rdy == 0) ? sizeof(int32_t) : ((int32_t)ray_lut[abs_rdy] << 8);
    uint8_t tile_x = FLOAT_TO_INT(game->entities[0].x);
    uint8_t tile_y = FLOAT_TO_INT(game->entities[0].y);
    int32_t side_dist_x = (rdx == 0) ? sizeof(int32_t) : (step_x > 0
    ? (((int32_t)(INT_TO_FLOAT(tile_x + 1) - game->entities[0].x) * delta_dist_x) >> 8)
    : (((int32_t)(game->entities[0].x - INT_TO_FLOAT(tile_x)) * delta_dist_x) >> 8));
    int32_t side_dist_y = (rdy == 0) ? sizeof(int32_t) : (step_y > 0
    ? (((int32_t)(INT_TO_FLOAT(tile_y + 1) - game->entities[0].y) * delta_dist_y) >> 8)
    : (((int32_t)(game->entities[0].y - INT_TO_FLOAT(tile_y)) * delta_dist_y) >> 8));
    int8_t side = 0;
    uint8_t steps = 0;
    int32_t distance = 0;

    for (; steps < 80; steps++) {
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
        if (map_level_1.map[(tile_y << 5) + (tile_x)] == WALL)
            break;
    }
    if (side == 0)
        distance = side_dist_x - delta_dist_x;
    else
        distance = side_dist_y - delta_dist_y;
    if (distance < 0)
        distance = 0;
    distance >>= 6;
    ((w3d_plug_in_t *)game->personal_data)->side[ray_id] = side;
    return (uint16_t)distance;
}

const void draw_background(game_t *game)
{
    uint16_t ray_dist = 0;
    w3d_plug_in_t *raycaster = (w3d_plug_in_t *)game->personal_data;
    move_win(0, 120);
    SHOW_WIN;

    for (uint8_t i = 0; i < 20; i++) {
        ray_dist = cast_ray(game, i);
        if (ray_dist > 26)
            ray_dist = 26;
        raycaster->rays[i] = ray_dist;
    }
    for (uint8_t i = 0; i < 20; i++) {
        if (raycaster->rays[i] != raycaster->last_rays[i])
            display_col(raycaster, i);
        raycaster->last_rays[i] = raycaster->rays[i];
    }
}
