/*
** EPITECH PROJECT, 2026
** **
** File description:
** game_wolf3d
*/

#ifndef GAME_WOLF3D_H_
    #define GAME_WOLF3D_H_
    #define ray_TILE_COUNT 8
    #include "game.h"
    void init_wolf3d(game_t *this);
    void update_wolf3d(game_t *this);
    
    const void reset_bkg(void);
    const void draw_background(game_t *game);
    const void handle_input(game_t *this);
    
    extern const map_t map_level_1;
    
    extern const uint8_t raycaster_tiles[128];

#endif /* !GAME_WOLF3D_H_ */
