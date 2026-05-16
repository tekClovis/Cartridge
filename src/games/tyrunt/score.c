/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt - score
*/

#include "game_tyrunt.h"
#include <stdio.h>

void update_score(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    char score_str[20];

    sprintf(score_str, "SCORE %d    ", data->score);
    printToWin(2, 0, score_str);
}
