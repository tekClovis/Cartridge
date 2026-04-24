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
    draw_ent16(this->entities[0]);
}