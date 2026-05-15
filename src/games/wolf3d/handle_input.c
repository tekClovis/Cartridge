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


static const void move_on_dir(game_t *this, const uint8_t angle)
{
    const int16_t cos_angle = COS(angle);
    const int16_t sin_angle = SIN(angle);
    int16_t dx = (cos_angle << 7) >> 8;
    int16_t dy = (sin_angle << 7) >> 8;
    int16_t next_x = (int16_t)this->entities[0].x + dx;
    int16_t next_y = (int16_t)this->entities[0].y + dy;
    uint16_t cur_tile_x = FLOAT_TO_INT(this->entities[0].x);
    uint16_t cur_tile_y = FLOAT_TO_INT(this->entities[0].y);
    uint16_t next_tile_x = FLOAT_TO_INT(next_x);
    uint16_t next_tile_y = FLOAT_TO_INT(next_y);

    if (next_y >= 0
        && next_y < INT_TO_FLOAT(this->map.height)
        && next_tile_y < this->map.height
        && cur_tile_x < this->map.width
        && map_level_1.map[(next_tile_y << 5) + cur_tile_x] != WALL) {
            this->entities[0].y = (uint16_t)next_y;
            cur_tile_y = next_tile_y;
    }
    if (next_x >= 0
        && next_x < INT_TO_FLOAT(this->map.width)
        && next_tile_x < this->map.width
        && cur_tile_y < this->map.height
        && map_level_1.map[(cur_tile_y << 5) + next_tile_x] != WALL) {
            this->entities[0].x = (uint16_t)next_x;
    }
    // char buf[256] = {0};
    // strcpy(buf, "  ");
    // itoa((int)this->entities[0].x, &buf[strlen(buf)], 10);
    // buf[strlen(buf)] = ' ';
    // itoa((int)this->entities[0].y, &buf[strlen(buf)], 10);
    // strcpy(&buf[strlen(buf)], "        ");
    // printToWin(0,1, buf);
}


static const void print_score_life(game_t *this){
    char buffer[32] = {0};

    sprintf(buffer, " SCORE %d%d\nHP %d%d",
            (this->score / 10), (this->score % 0x0A),
            (this->entities[0].life / 10), (this->entities[0].life % 0x0A));
    printToWin(0, 0, buffer);
}

const void handle_input(game_t *this)
{
    uint8_t *angle = &((w3d_ent_plug_in_t *)this->entities[0].personal_data)->angles[0];
    uint8_t input = joypad();

    if (input & J_LEFT){
        *angle = (*angle - 8) & 127;
        draw_background(this);
        return;
    }
    if (input & J_RIGHT){
        *angle = (*angle + 8) & 127;
        draw_background(this);
        return;
    }
    if (input & J_UP && this->actual_frame > 5){
        move_on_dir(this, *angle);
        this->actual_frame = 0;
        draw_background(this);
        anim_machop(this);
        return;
    }
    if (input & J_DOWN && this->actual_frame > 5){
        move_on_dir(this, (*angle + 64) & 127);
        this->actual_frame = 0;
        draw_background(this);
        anim_machop(this);
        return;
    }
    if (input & J_A  && this->actual_frame > 9){
        this->score += 1;
        print_score_life(this);
            this->actual_frame = 0;
        anim_weapon(this);
        return;
    }
}
