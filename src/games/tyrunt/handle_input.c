/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

/**
 * @file handle_input.c
 * @brief Joypad handling for the tyrunt game.
 */

#include "game_tyrunt.h"

/**
 * @brief Start a jump from the ground, or spend the double jump while airborne.
 * @param this Game state; `personal_data` must point to the tyrunt data.
 * @note The double jump is only taken once the player stops rising (velocity_y > -1).
 */
void handle_jump(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (data->is_jumping == 0) {
        data->is_jumping = 1;
        data->velocity_y = -5;
    }
    if (data->double_jumps_left > 0 && data->velocity_y > -1) {
        data->velocity_y = -5;
        data->double_jumps_left -= 1;
    }
}

/**
 * @brief Read the joypad: A jumps, SELECT hides the window and returns to the menu.
 * @param this Game state.
 */
void handle_input_tyrunt(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (joypad() & J_A) {
        handle_jump(this);
    }
    if ((joypad() & J_SELECT)) {
        HIDE_WIN;
        init_game(this, MENU);
    }
}
