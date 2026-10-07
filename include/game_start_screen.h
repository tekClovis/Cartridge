/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** game_start_screen
*/

/** @file game_start_screen.h @brief Start screen assets and entry points. */

#ifndef GAME_START_SCREEN_H_
    #define GAME_START_SCREEN_H_
    #define pokopie_tileset_WIDTH 128
    #define pokopie_tileset_HEIGHT 40
    #define pokopie_tileset_TILE_COUNT 80
    #define pokopie_tileset_PALETTE_COUNT 8
    #include "game.h"
    #include <stdint.h>
    #include <gbdk/platform.h>
    #include <gbdk/metasprites.h>
    BANKREF_EXTERN(pokopie_tileset)
    extern const metasprite_t* const pokopie_tileset_metasprites[1];
    extern const palette_color_t pokopie_tileset_palettes[32];
    extern const uint8_t pokopie_tileset_tiles[1280];
    extern const uint8_t pokopie_tilemap[360];
    /** @brief Set up the start screen. */
    const void init_start_screen(game_t *this);
    /** @brief Per-frame update of the start screen. */
    const void update_start_screen(game_t *this);
#endif /* !GAME_START_SCREEN_H_ */
