/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** utils
*/

#include "game_wolf3d.h"
#include <stdio.h>
#include <string.h>

const void print_score_life(game_t *this){
    char buffer[32] = {0};

    sprintf(buffer, " SCORE %d%d%d\nHP %d%d",
            (this->score / 100), ((this->score % 100) / 10), (this->score % 0x0A),
            (this->entities[0].life / 10), (this->entities[0].life % 0x0A));
    printToWin(0, 0, buffer);
}
