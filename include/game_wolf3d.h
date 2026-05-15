/*
** EPITECH PROJECT, 2026
** **
** File description:
** game_wolf3d
*/

#ifndef GAME_WOLF3D_H_
    #define GAME_WOLF3D_H_
    #define ray_TILE_COUNT 17
    #define machop_tiles_TILE_COUNT 8
    #define gun_tileset_TILE_COUNT 8
    #define TRIG_TABLE_SIZE 128
    #define TRIG_CENTER 128
    #define SIN_RAW(angle) (SIN_TABLE[((uint8_t)(angle))])
    #define COS_RAW(angle) (COS_TABLE[((uint8_t)(angle))])
    #define SIN(angle) (((int16_t)SIN_RAW(angle) - TRIG_CENTER))
    #define COS(angle) (((int16_t)COS_RAW(angle) - TRIG_CENTER))
    #define SIN_Q8_8(angle) (((int16_t)SIN_RAW(angle) - TRIG_CENTER) << 8)
    #define COS_Q8_8(angle) (((int16_t)COS_RAW(angle) - TRIG_CENTER) << 8)
    #define INT_TO_FLOAT(value) (value << 8)
    #define DECIMAL_TO_FLOAT(value) (value << 8)
    #define FLOAT_TO_INT(value) (value >> 8)
    #define PLAYER_ENTITY_ID 0
    #define POKEMON_ENTITY_ID 1
    #include "game.h"

    const void init_wolf3d(game_t *this);
    const void initialize_ennemies(game_t *game);
    const void init_player(game_t *game);

    const void update_wolf3d(game_t *this);
    
    const void draw_background(game_t *game);
    const void handle_input(game_t *this);
    const void anim_machop(game_t *this);
    const void anim_weapon(game_t *this);

    extern const map_t map_level_1;
    extern const uint8_t raycaster_tiles[272];
    extern uint16_t ray_lut[256];
    extern const palette_color_t machop_tiles_palettes[4];
    extern const uint8_t machop_tiles_tiles[128];
    extern const metasprite_t* const gun_tileset_metasprites[1];
    extern const palette_color_t gun_tileset_palettes[4];
    extern const uint8_t gun_tileset_tiles[160];

    typedef struct ray_s {
        uint8_t distance;
        uint8_t height;
        uint8_t sub_tile_id;

    } ray_t;

    typedef struct raycaster_s {
        ray_t rays[20];
        ray_t last_rays[20];
    } raycaster_t;

    static const uint8_t SIN_TABLE[TRIG_TABLE_SIZE] = {
            128, 134, 140, 147, 153, 159, 165, 171, 177, 182, 188, 193, 199, 204, 209, 213,
            218, 222, 226, 230, 234, 237, 240, 243, 245, 248, 250, 251, 253, 254, 254, 255,
            255, 255, 254, 254, 253, 251, 250, 248, 245, 243, 240, 237, 234, 230, 226, 222,
            218, 213, 209, 204, 199, 193, 188, 182, 177, 171, 165, 159, 153, 147, 140, 134,
            128, 122, 116, 109, 103,  97,  91,  85,  79,  74,  68,  63,  57,  52,  47,  43,
                38,  34,  30,  26,  22,  19,  16,  13,  11,   8,   6,   5,   3,   2,   2,   1,
                1,   1,   2,   2,   3,   5,   6,   8,  11,  13,  16,  19,  22,  26,  30,  34,
                38,  43,  47,  52,  57,  63,  68,  74,  79,  85,  91,  97, 103, 109, 116, 122,
    };

    static const uint8_t COS_TABLE[TRIG_TABLE_SIZE] = {
                        255, 255, 254, 254, 253, 251, 250, 248, 245, 243, 240, 237, 234, 230, 226, 222,
                        218, 213, 209, 204, 199, 193, 188, 182, 177, 171, 165, 159, 153, 147, 140, 134,
                        128, 122, 116, 109, 103,  97,  91,  85,  79,  74,  68,  63,  57,  52,  47,  43,
                         38,  34,  30,  26,  22,  19,  16,  13,  11,   8,   6,   5,   3,   2,   2,   1,
                            1,   1,   2,   2,   3,   5,   6,   8,  11,  13,  16,  19,  22,  26,  30,  34,
                         38,  43,  47,  52,  57,  63,  68,  74,  79,  85,  91,  97, 103, 109, 116, 122,
                        128, 134, 140, 147, 153, 159, 165, 171, 177, 182, 188, 193, 199, 204, 209, 213,
                        218, 222, 226, 230, 234, 237, 240, 243, 245, 248, 250, 251, 253, 254, 254, 255,
    };

#endif /* !GAME_WOLF3D_H_ */
