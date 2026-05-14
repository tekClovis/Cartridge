/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** wolf3d
*/
#include "game_wolf3d.h"

uint16_t ray_lut[256];

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
    uint16_t i = 0;
    w3d_ent_plug_in_t *plug_in = &g_ent_data.wolf3d;

    plug_in->angle = 0;
    for (; map_level_1.map[i] != SPAWN &&  i < game->map.size; i++);
    game->entities[0].x = INT_TO_FLOAT(i % game->map.width);
    game->entities[0].y = INT_TO_FLOAT(i / game->map.width);
    game->entities[0].personal_data = plug_in;
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
}

const void update_wolf3d(game_t *this)
{
    handle_input(this);}

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
    draw_background(this);
}