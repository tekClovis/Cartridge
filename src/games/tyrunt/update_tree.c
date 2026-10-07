/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

/**
 * @file update_tree.c
 * @brief Tree obstacle movement, scoring and collision.
 */

#include "game_tyrunt.h"

/**
 * @brief End the game if the player hits the tree while not invincible.
 * @param this Game state.
 */
void check_tree_collide(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (data->invincible_timer > 0)
        return;
    if (collide(this->entities[0].x, this->entities[0].y,
            this->entities[1].x, this->entities[1].y)) {
        data->speed = 1;
        this->entities[1].x = 250;
        SCX_REG -= data->speed;
        move_sprite(4, 0, 0);
        move_sprite(5, 0, 0);
        trigger_game_over(this);
    }
}

/**
 * @brief Deactivate the tree once it leaves the screen and award 1 point.
 * @param this Game state.
 */
void check_tree_score(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (this->entities[1].x == 0 || this->entities[1].x > 250) {
        this->entities[1].x = 250;
        data->score += 1;
        move_sprite(4, 0, 0);
        move_sprite(5, 0, 0);
    }
}

/**
 * @brief Move the active tree left by the current speed, then check score and collision.
 * @param this Game state.
 */
void update_tree(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (this->entities[1].x >= 250)
        return;
    this->entities[1].x -= data->speed;
    move_sprite(4, this->entities[1].x, this->entities[1].y);
    move_sprite(5, this->entities[1].x + 8, this->entities[1].y);
    check_tree_score(this);
    check_tree_collide(this);
}
