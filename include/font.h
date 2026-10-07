/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** font
*/

/** @file font.h @brief Font tileset constants and ASCII/digit to tile mapping macros. */

#ifndef FONT_H_
    #define FONT_H_
    #include <stdint.h>
    
    #include <gbdk/platform.h>
    #include <gbdk/metasprites.h>
    /** @name Font tileset layout (generated asset values) @{ */
    #define font_TILE_ORIGIN 209
    #define font_TILE_W 8
    #define font_TILE_H 8
    #define font_WIDTH 128
    #define font_HEIGHT 24
    #define font_TILE_COUNT (uint8_t)48
    #define font_PALETTE_COUNT 1
    #define font_COLORS_PER_PALETTE 4
    #define font_TOTAL_COLORS 4
    #define font_PIVOT_X 64
    #define font_PIVOT_Y 12
    #define font_PIVOT_W 128
    #define font_PIVOT_H 24
    /** @} */
    /** Tile index of the blank tile, used to clear the background, window and sprites. */
    #define font_BLANK_TILE 207
    /** Convert an uppercase ASCII character @p c to its font tile index. */
    #define ASCII_TO_TILE(c) ((uint8_t)((uint16_t)((c) + 225) - ((uint16_t)'A')))
    /** Convert a digit character @p c ('0'..'9') to its font tile index. */
    #define NUMBER_TO_TILE(c) (210 + c - '0')

    extern const metasprite_t* const font_metasprites[1];
    extern const palette_color_t font_palettes[4];
    extern const uint8_t font_tiles[768];




#endif /* !FONT_H_ */
