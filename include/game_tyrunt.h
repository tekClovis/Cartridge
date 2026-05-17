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
    void update_player(game_t *this);
    void animate_player(game_t *this);
    void update_tree(game_t *this);
    void update_tylton(game_t *this);
    void animate_tylton(game_t *this);
    void manage_spawner(game_t *this);
    uint8_t collide(unsigned int px, unsigned int py,
        unsigned int ox, unsigned int oy);
    void update_bonus(game_t *this);
    void trigger_game_over(game_t *this);

    

#endif /* !GAME_TYRUNT_H_ */
