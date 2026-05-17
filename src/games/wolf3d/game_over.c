/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** game_over
*/

#include "game_wolf3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gb/gb.h>

const void update_game_over(game_t *this)
{
    if (joypad() & J_START){
        init_game(this, WOLF_3D);
        return;
    }
    if (joypad() & J_SELECT){
        init_game(this, MENU);
        return;
    }
    if (this->actual_frame > 10){
        this->actual_frame = 0;
        blink_bg();
    }
}

static const void display_game_over(game_t *this, uint8_t victory)
{
    char buffer[256] = {0};
    sprintf(buffer, "%s", victory ? "VICTORY" : "DEFEAT");
    printToMap(7, 2, buffer);
    sprintf(buffer, "GAME OVER");
    printToMap(6, 7, buffer);
    sprintf(&buffer[0], "SCORE          %d%d%d",
        (this->score / 100), ((this->score % 100) / 10), (this->score % 10));
    printToMap(1, 10, buffer);
    SWITCH_RAM(0);
    ENABLE_RAM;
    sprintf(&buffer[0], "HIGH SCORE     %d%d%d",
        (high_scores[WOLF_3D - 2] / 100), ((high_scores[WOLF_3D - 2] % 100) / 10), (high_scores[WOLF_3D - 2] % 10));
    DISABLE_RAM;
    printToMap(1, 12, buffer);
    sprintf(buffer, "<=> RESTART");
    printToMap(5, 16, buffer);
}

const void set_game_over(game_t *this, uint8_t victory)
{
    char buffer[256] = {0};

    fade_out();
    reset_bkg();
    save_score(this);
    display_game_over(this, victory);
    HIDE_WIN;
    clear_sprite_tiles();
    fade_in();
    this->update = &update_game_over;
    this->game_over = 1;
}