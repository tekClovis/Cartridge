/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** print
*/
/** @file print.c @brief Text output and clearing for the background and window maps. */
#include "game.h"
#include "font.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/** @brief Fill the 32x32 window map with font_BLANK_TILE. */
const void reset_win(void)
{
    for (uint8_t i = 0; i < 32; i++){
        for (uint8_t j = 0; j < 32; j++){
            set_win_tile_xy(i, j, font_BLANK_TILE);
        }
    }
}

/** @brief Fill the 32x32 background map with font_BLANK_TILE. */
const void reset_bkg(void)
{
    for (uint8_t i = 0; i < 32; i++){
        for (uint8_t j = 0; j < 32; j++){
            set_bkg_tile_xy(i, j, font_BLANK_TILE);
        }
    }
}

/**
 * @brief Write a NUL-terminated string on the background map, one tile per character.
 * @param x Tile column of the first character.
 * @param y Tile row.
 * @param string Text to print; digits use NUMBER_TO_TILE, others ASCII_TO_TILE.
 * @warning No wrapping or newline handling; no bounds check on x.
 */
const void printToMap(uint8_t x, uint8_t y, const char string[256])
{
    int pc = 0;
    int og_x = x;

    for (uint8_t i = 0; string[i]; i++){
        // if (string[i] == '\n')
        //     pc = 21;
        // if (pc + i > 20){
        //     y++;
        //     x = og_x;   
        //     pc = 0;
        // }
        if (isdigit(string[i]))
            set_bkg_tile_xy(x + pc, y, NUMBER_TO_TILE(string[i]));
        else
            set_bkg_tile_xy(x + pc, y, ASCII_TO_TILE(string[i]));
        pc++;
    }
}

/**
 * @brief Write a NUL-terminated string on the window map, with index-based row wrapping.
 * @param x Tile column of the first character.
 * @param y Tile row of the first line.
 * @param string Text to print; digits use NUMBER_TO_TILE, others ASCII_TO_TILE.
 * @warning Wraps when x + i > 20 with i the string index (not the column), so every
 *          character from index 21 - x on starts a new row; '\n' forces this wrap too.
 */
const void printToWin(uint8_t x, uint8_t y, const char string[256])
{
    int pc = 0;
    int og_x = x;

    for (uint8_t i = 0; string[i]; i++){
        if (string[i] == '\n')
            x = 21;
        if (x + i > 20){
            y++;
            x = og_x;
            pc = 0;
        }
        if (isdigit(string[i]))
            set_win_tile_xy(x + pc, y, NUMBER_TO_TILE(string[i]));
        else
            set_win_tile_xy(x + pc, y, ASCII_TO_TILE(string[i]));
        pc++;
    }
}
