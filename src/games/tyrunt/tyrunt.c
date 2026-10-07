/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

/**
 * @file tyrunt.c
 * @brief Main loop, timers and game-over screen of the tyrunt game.
 */

#include "game_tyrunt.h"
#include <stdio.h>

/**
 * @brief Game-over callback: A restarts the game, SELECT returns to the menu.
 * @param this Game state.
 */
void update_gameover(game_t *this)
{
    if (joypad() & J_A) {
        reset_win();
        init_tyrunt(this);
    }
    if (joypad() & J_SELECT) {
        reset_win();
        HIDE_WIN;
        init_game(this, MENU);
    }
}

/**
 * @brief Save the high score, switch to the game-over screen and swap the update callback.
 * @param this Game state.
 */
void trigger_game_over(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    char score_str[20];

    set_high_score(TYRUNT, data->score);
    this->update = &update_gameover;
    HIDE_SPRITES;
    reset_win();
    move_win(7, 0);
    printToWin(5, 2, "GAME OVER!");
    sprintf(score_str, "SCORE %d", data->score);
    printToWin(6, 4, score_str);
    printToWin(2, 7, "PRESS A TO REPLAY");
    printToWin(0, 9, "PRESS SELECT TO MENU");
}

/**
 * @brief Run the spawner and update the tree and Tylton obstacles.
 * @param this Game state.
 */
void update_obstacle(game_t *this)
{
    manage_spawner(this);
    update_tree(this);
    update_tylton(this);
}

/**
 * @brief Decrement the invincibility and slow-mode timers by one frame.
 * @param this Game state.
 */
void update_timers(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (data->invincible_timer > 0)
        data->invincible_timer -= 1;
    if (data->slow_timer > 0)
        data->slow_timer -= 1;
}

/**
 * @brief Per-frame update of the running game; scrolls the background by the current speed.
 * @param this Game state.
 * @note Returns early when an obstacle hit switched `update` to the game-over callback.
 */
void update_tyrunt(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    handle_input_tyrunt(this);
    update_player(this);
    animate_player(this);
    update_obstacle(this);
    if (this->update != &update_tyrunt)
        return;
    update_score(this);
    update_bonus(this);
    update_timers(this);
    SCX_REG += data->speed;
}
