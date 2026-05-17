/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"
#include <stdio.h>

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

void update_obstacle(game_t *this)
{
    manage_spawner(this);
    update_tree(this);
    update_tylton(this);
}

void update_timers(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (data->invincible_timer > 0)
        data->invincible_timer -= 1;
    if (data->slow_timer > 0)
        data->slow_timer -= 1;
}

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
