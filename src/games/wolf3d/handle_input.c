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

static const uint8_t move_on_dir(game_t *this, const uint8_t angle)
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
    uint8_t moved = 0;

    if (next_y >= 0
        && next_y < INT_TO_FLOAT(this->map.height)
        && next_tile_y < this->map.height
        && cur_tile_x < this->map.width
        && map_level_1.map[(next_tile_y << 5) + cur_tile_x] != WALL) {
            this->entities[0].y = (uint16_t)next_y;
            cur_tile_y = next_tile_y;
            moved = 1;
    }
    if (next_x >= 0
        && next_x < INT_TO_FLOAT(this->map.width)
        && next_tile_x < this->map.width
        && cur_tile_y < this->map.height
        && map_level_1.map[(cur_tile_y << 5) + next_tile_x] != WALL) {
            this->entities[0].x = (uint16_t)next_x;
            moved = 1;
    }
    if (moved){
        this->score = this->score >= 2
        ? this->score -2
        : 0;
        print_score_life(this);
    }
    if (moved && (map_level_1.map[(cur_tile_y << 5) + cur_tile_x] == EXIT
        || this->score == 0)) {
        set_game_over(this, this->score != 0);
        return 1;
    }
    return 0;
}

static const uint8_t handle_turn(game_t *this, uint8_t *angle, uint8_t input)
{
    if (input & J_LEFT) {
        *angle = (*angle - 8) & 127;
        draw_background(this);
        return 1;
    }
    if (input & J_RIGHT) {
        *angle = (*angle + 8) & 127;
        draw_background(this);
        return 1;
    }
    return 0;
}

static const uint8_t handle_move(game_t *this, uint8_t angle, uint8_t input)
{
    if ((input & J_UP) && this->actual_frame > 5) {
        if (move_on_dir(this, angle))
            return 1;
        this->actual_frame = 0;
        draw_background(this);
        anim_machop(this);
        return 1;
    }
    if ((input & J_DOWN) && this->actual_frame > 5) {
        if (move_on_dir(this, (angle + 64) & 127))
            return 1;
        this->actual_frame = 0;
        draw_background(this);
        anim_machop(this);
        return 1;
    }
    return 0;
}

static const uint8_t handle_action(game_t *this, uint8_t input)
{
    if (input & J_SELECT) {
        init_game(this, MENU);
        return 1;
    }
    if ((input & J_A) && this->actual_frame > 9) {
        this->score += 1;
        print_score_life(this);
        this->actual_frame = 0;
        anim_weapon(this);
        return 1;
    }
    if ((input & J_B) && this->actual_frame > 9) {
        this->score += 1;
        print_score_life(this);
        this->actual_frame = 0;
        anim_weapon(this);
        return 1;
    }
    return 0;
}



const void handle_input(game_t *this)
{
    uint8_t *angle = &((w3d_ent_plug_in_t *)this->entities[0].personal_data)->angles[0];
    uint8_t input = joypad();

    if (handle_turn(this, angle, input))
        return;
    if (handle_move(this, *angle, input))
        return;
    if (handle_action(this, input))
        return;
}
