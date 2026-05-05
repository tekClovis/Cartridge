/*
** EPITECH PROJECT, 2026
** G-ING-401-LIL-4-1-cartridge-3
** File description:
** game_snake
*/

#ifndef GAME_SNAKE_H_
#define GAME_SNAKE_H_

    #include "game.h"

    void init_snake(game_t *this);
    void update_snake(game_t *this);
    
    const void reset_bkg(void);
    const void draw_background(game_t *game);
    const void handle_input(game_t *this);

#endif /* !GAME_SNAKE_H_ */
