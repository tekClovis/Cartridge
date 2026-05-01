/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** handle-input
*/
#include "game_wolf3d.h"
#include <gb/gb.h>

const void handle_input(game_t *this)
{
    if (joypad() & J_LEFT)
        ((w3d_ent_plug_in_t *)this->entities[0].personal_data)->angle = 
            ((w3d_ent_plug_in_t *)this->entities[0].personal_data)->angle - 8 & 127;
    if (joypad() & J_RIGHT)
        ((w3d_ent_plug_in_t *)this->entities[0].personal_data)->angle =
            ((w3d_ent_plug_in_t *)this->entities[0].personal_data)->angle + 8 & 127;
    // if (joypad() & J_UP){
    //     this->entities[0].x += COS(this->entities[0].angle) << 1;
    //     this->entities[0].y += SIN(this->entities[0].angle) << 1;
    // }
    // if (joypad() & J_DOWN){
    //     this->entities[0].x -= COS(this->entities[0].angle) << 1;
    //     this->entities[0].y -= SIN(this->entities[0].angle) << 1;
    // }
}
