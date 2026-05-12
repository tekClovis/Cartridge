/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** handle-input
*/
#include "game_wolf3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gb/gb.h>


void move_on_dir(game_t *this, const uint8_t angle)
{
    const int16_t speed = 128;
    const int16_t cos_angle = COS(angle);
    const int16_t sin_angle = SIN(angle);
    int16_t dx = (cos_angle << 7) >> 7;
    int16_t dy = (sin_angle << 7) >> 7;
    int16_t next_x = (int16_t)this->entities[0].x + dx;
    int16_t next_y = (int16_t)this->entities[0].y + dy;

    if (next_y >= 0 && next_y < (int16_t)(this->map.height << 8)) {
        uint16_t tile_x = FLOAT_TO_INT(next_x);
        uint16_t tile_y = FLOAT_TO_INT(next_y);

        if (tile_y < this->map.height
            && this->map.map[(tile_y << 5) + tile_x] != WALL)
            this->entities[0].y = (uint16_t)next_y;
    }
    if (next_x >= 0 && next_x < (int16_t)(this->map.width << 8)) {
        uint16_t tile_x = FLOAT_TO_INT(next_x);
        uint16_t tile_y = FLOAT_TO_INT(this->entities[0].y);

        if (tile_x < this->map.width
            && this->map.map[(tile_y << 5) + tile_x] != WALL)
            this->entities[0].x = (uint16_t)next_x;
    }
    char buf[256] = {0};
    strcpy(buf, "  ");
    itoa((int)this->entities[0].x, &buf[strlen(buf)], 10);
    buf[strlen(buf)] = ' ';
    itoa((int)this->entities[0].y, &buf[strlen(buf)], 10);
    strcpy(&buf[strlen(buf)], "        ");
    printToWin(0,1, buf);
}

const void handle_input(game_t *this)
{
    uint8_t *angle = &((w3d_ent_plug_in_t *)this->entities[0].personal_data)->angle;
    uint8_t input = joypad();

    if (input & J_LEFT){
        *angle = (*angle - 8) & 127;
        return;
    }
    if (input & J_RIGHT){
        *angle = (*angle + 8) & 127;
        return;
    }
    if (input & J_UP && this->actual_frame > 5){
        move_on_dir(this, *angle);
        this->actual_frame = 0;
        return;
    }
    if (input & J_DOWN && this->actual_frame > 5){
        move_on_dir(this, (*angle + 64) & 127);
        this->actual_frame = 0;
        return;
    }
}
