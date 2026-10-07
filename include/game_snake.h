/*
** EPITECH PROJECT, 2026
** G-ING-401-LIL-4-1-cartridge-3
** File description:
** game_snake
*/

/** @file game_snake.h @brief Snake game constants and entry points. */

#ifndef GAME_SNAKE_H_
#define GAME_SNAKE_H_

    #include "game.h"

    /** @name Snake limits @{ */
    #define SNAKE_MAX_LENGTH 30
    #define SNAKE_FOOD_SPRITE_ID 30
    #define SNAKE_GRID_WIDTH 20
    #define SNAKE_GRID_HEIGHT 18
    /** @} */

    /** @name Snake directions @{ */
    #define SNAKE_UP 0
    #define SNAKE_RIGHT 1
    #define SNAKE_DOWN 2
    #define SNAKE_LEFT 3
    /** @} */

/** @brief Initialise the Snake game. */
void init_snake(game_t *this);
/** @brief Per-frame update of the Snake game. */
void update_snake(game_t *this);

static const void handle_input_snake(game_t *this);

#endif /* !GAME_SNAKE_H_ */
