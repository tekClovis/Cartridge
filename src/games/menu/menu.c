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

static const void show_game_stat(game_t *this)
{
    uint8_t rel_coord_x = this->entities[0].x >> 3;
    uint8_t rel_coord_y = this->entities[0].y >> 3;

    if (rel_coord_x > 4  && rel_coord_x < 10 && rel_coord_y > 8 && rel_coord_y < 14) {
        if (this->window[1].y == 144){
            reset_win();
            printToWin(1, 0, (char *)game_names[WOLF_3D]);
            SHOW_WIN;
        }
        if (this->window[1].y > 120)
            this->window[1].y -= 1;
        } else if (rel_coord_x > 22 && rel_coord_x < 30 && rel_coord_y > 18 && rel_coord_y < 22) {
            if (this->window[1].y == 144){
                reset_win();
                printToWin(1, 0, (char *)game_names[TYRUNT]);
                SHOW_WIN;
            }
            if (this->window[1].y > 120)
                this->window[1].y -= 1;
    } else if (this->window[1].y < 144)
        this->window[1].y += 1;
    move_win(0, this->window[1].y);
}

void update_menu(game_t *this)
{
    handleInput(this);
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