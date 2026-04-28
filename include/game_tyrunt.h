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
    
    const void reset_bkg(void);
    const void draw_background(game_t *game);
    const void handle_input(game_t *this);
    

#endif /* !GAME_TYRUNT_H_ */
