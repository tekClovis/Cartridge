/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

/**
 * @file update_bonus.c
 * @brief Bonus pickup movement, collision and effects.
 */

#include "game_tyrunt.h"

/**
 * @brief Apply a random bonus chosen from DIV_REG.
 * @param this Game state.
 * @note Outcomes: +5 score, 300 frames invincible, one double jump, 300 frames slow.
 */
void give_bonus(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    switch (DIV_REG % 4) {
        case 0:
            data->score += 5;
            break;
        case 1:
            data->invincible_timer = 300;
            break;
        case 2:
            data->double_jumps_left = 1;
            break;
        case 3:
            data->slow_timer = 300;
            break;
    }
}

/**
 * @brief Grant the bonus and deactivate it if the player touches it.
 * @param this Game state.
 */
void check_bonus_collide(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (collide(this->entities[0].x, this->entities[0].y,
            this->entities[3].x, this->entities[3].y)) {
        give_bonus(this);
        this->entities[3].x = 250;
        move_sprite(10, 0, 0);
    }
}

/**
 * @brief Deactivate the bonus once it has left the left edge of the screen.
 * @param this Game state.
 */
void check_bonus_missed(game_t *this)
{
    if (this->entities[3].x == 0 || this->entities[3].x > 250) {
        this->entities[3].x = 250;
        move_sprite(10, 0, 0);
    }
}

/**
 * @brief Scroll the active bonus left by the current speed and check pickup or miss.
 * @param this Game state.
 */
void update_bonus(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (this->entities[3].x >= 250)
        return;
    this->entities[3].x -= data->speed;
    move_sprite(10, this->entities[3].x, this->entities[3].y);
    check_bonus_collide(this);
    check_bonus_missed(this);
}
