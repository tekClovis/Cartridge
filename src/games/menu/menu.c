/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** menu
*/
#include "game.h"
#include "game_menu.h"
#include <string.h>
#include <stdio.h>
#include "map.h"
#include <gb/gb.h>

static const rectangle_t infos_rect[3] = {
    {.x = 5, .y = 11, .width = 2, .height = 2},
    {.x = 25, .y = 19, .width = 2, .height = 2},
    {0}
};

static const char game_names[GAME_ID_COUNT][32] = {
    "START_SCREEN",
    "MENU        ",
    "WOLF 3D     ",
    "TYRUNT      ",
    "GAME 3      "
};

static const void show_game_stat(game_t *this)
{
    uint8_t rel_coord_x = this->entities[0].x >> 3;
    uint8_t rel_coord_y = this->entities[0].y >> 3;
    game_id game_id = 0;
    char buffer_score[256] = {0};

    for (uint8_t i = 0; infos_rect[i].width != 0; i++)
        if (point_in_rect(rel_coord_x, rel_coord_y, &infos_rect[i])){
            game_id = i + 2;
            break;
        }
    if (game_id == 0 && this->window[1].y < 144){
        this->window[1].y += 1;
        move_win(0, this->window[1].y);
    }
    if (game_id && this->window[1].y == 144){
        SWITCH_RAM(0);
        ENABLE_RAM;
        sprintf(buffer_score, "HIGH SCORE     %d%d%d",
            high_scores[game_id - 2] / 100, (high_scores[game_id - 2] % 100) / 10,  high_scores[game_id - 2] % 10);
        DISABLE_RAM;
        printToWin(1, 0, (char *)game_names[game_id]);
        printToWin(1, 2, buffer_score);
    }
    if (game_id && this->window[1].y > 120){
        this->window[1].y -= 1;
        move_win(0, this->window[1].y);
    }
}

const void update_menu(game_t *this)
{
    handleInput(this);
    if (this->game_over)
        return;
    if (this->actual_frame >> 4){
        this->entities[0].animation = !this->entities[0].animation;
        this->entities[0].sprite_tile[0] += this->entities[0].animation ? 4 : -4;
        this->entities[0].sprite_tile[1] += this->entities[0].animation ? 4 : -4;
        set_sprite_tile(this->entities[0].sprite_ids[0], this->entities[0].sprite_tile[0]);
        set_sprite_tile(this->entities[0].sprite_ids[1], this->entities[0].sprite_tile[1]);
        this->actual_frame = 0;
    }
    show_game_stat(this);
    draw_ent16(this->entities[0]);
}