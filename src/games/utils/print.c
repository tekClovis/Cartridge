/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** print
*/
#include "game.h"
#include "font.h"
#include <stdlib.h>

const void reset_win(void)
{
    for (uint8_t i = 0; i < 32; i++){
        for (uint8_t j = 0; j < 32; j++){
            set_win_tile_xy(i, j, font_BLANK_TILE);
        }
    }
}

const void reset_bkg(void)
{
    for (uint8_t i = 0; i < 32; i++){
        for (uint8_t j = 0; j < 32; j++){
            set_bkg_tile_xy(i, j, font_BLANK_TILE);
        }
    }
}

const void printToMap(uint8_t x, uint8_t y, const char string[256])
{
    int pc = 0;

    for (uint8_t i = 0; string[i]; i++){
        if (string[i] == '\n')
            x = 21;
        if (x + i > 20){
            y++;
            pc = 0;
        }
        if (atoi(&string[i]))
            set_win_tile_xy(x + pc, y, NUMBER_TO_TILE(string[i]));
        else
            set_bkg_tile_xy(x + pc, y, ASCII_TO_TILE(string[i]));
        pc++;
    }
}

const void printToWin(uint8_t x, uint8_t y, const char string[256])
{
    int pc = 0;

    for (uint8_t i = 0; string[i]; i++){
        if (string[i] == '\n')
            x = 21;
        if (x + i > 20){
            y++;
            pc = 0;
        }
        if (atoi(&string[i]))
            set_win_tile_xy(x + pc, y, NUMBER_TO_TILE(string[i]));
        else
            set_win_tile_xy(x + pc, y, ASCII_TO_TILE(string[i]));
        pc++;
    }
}
