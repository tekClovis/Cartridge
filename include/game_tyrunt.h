/*
** EPITECH PROJECT, 2026
** **
** File description:
** game_tyrunt
*/

#ifndef GAME_TYRUNT_H_
    #define GAME_TYRUNT_H_

    #include "game.h"

    void init_tyrunt(game_t *this);
    void update_tyrunt(game_t *this);
    void handle_input_tyrunt(game_t *this);

    const void draw_background(game_t *game);

    void update_score(game_t *this);
    

#endif /* !GAME_TYRUNT_H_ */
