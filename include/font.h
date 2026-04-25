/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** font
*/

#ifndef FONT_H_
    #define FONT_H_
    #include <stdint.h>
    #include <gbdk/platform.h>
    #include <gbdk/metasprites.h>
    #define font_TILE_ORIGIN 0
    #define font_TILE_W 8
    #define font_TILE_H 8
    #define font_WIDTH 128
    #define font_HEIGHT 24
    #define font_TILE_COUNT 48
    #define font_PALETTE_COUNT 1
    #define font_COLORS_PER_PALETTE 4
    #define font_TOTAL_COLORS 4
    #define font_PIVOT_X 64
    #define font_PIVOT_Y 12
    #define font_PIVOT_W 128
    #define font_PIVOT_H 24
    # define ASCII_TO_TILE(c) ((c) - 65 + 225)
extern const metasprite_t* const font_metasprites[1];



BANKREF_EXTERN(font)

extern const palette_color_t font_palettes[4];
extern const uint8_t font_tiles[768];




#endif /* !FONT_H_ */
