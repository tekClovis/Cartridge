/*
** EPITECH PROJECT, 2026
** **
** File description:
** game_tyrunt
*/

/** @file game_tyrunt.h @brief Tyrunt game entry points and helpers. */

#ifndef GAME_TYRUNT_H_
    #define GAME_TYRUNT_H_

    #include "game.h"

    /** Player state. */
    typedef enum {
        TYRUNT_IDLE,
        TYRUNT_JUMPING,
        TYRUNT_FALLING
    } tyrunt_state_t;

    /** @brief Initialise the Tyrunt game. */
    void init_tyrunt(game_t *this);
    /** @brief Per-frame update of the Tyrunt game. */
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
    /**
     * @brief Test collision between the player and an obstacle.
     * @param px Player x.
     * @param py Player y.
     * @param ox Obstacle x.
     * @param oy Obstacle y.
     * @return Non-zero on collision.
     */
    uint8_t collide(unsigned int px, unsigned int py,
        unsigned int ox, unsigned int oy);
    void update_bonus(game_t *this);
    void trigger_game_over(game_t *this);

    

#endif /* !GAME_TYRUNT_H_ */
