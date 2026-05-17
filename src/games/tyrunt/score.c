/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt - score
*/

#include "game_tyrunt.h"
#include <stdio.h>

static void update_difficulty(tyrunt_plug_in_t *data)
{
    if (data->score < 15)
        data->speed = 1;
    if (data->score >= 15)
        data->speed = 2;
    if (data->score >= 45)
        data->speed = 3;
    if (data->score >= 100)
        data->speed = 4;
}

void update_score(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    char score_str[20];

    update_difficulty(data);
    sprintf(score_str, "SCORE %d    ", data->score);
    printToWin(2, 0, score_str);
}
