/*
** EPITECH PROJECT, 2026
** **
** File description:
** game_tyrunt
*/

#ifndef GAME_TYRUNT_H_
    #define GAME_TYRUNT_H_

    #include "game.h"
    typedef enum {
        TYRUNT_IDLE,
        TYRUNT_JUMPING,
        TYRUNT_FALLING
    } tyrunt_state_t;

    void init_tyrunt(game_t *this);
    void update_tyrunt(game_t *this);
    void handle_input_tyrunt(game_t *this);

    const void draw_background(game_t *game);
    

#endif /* !GAME_TYRUNT_H_ */
