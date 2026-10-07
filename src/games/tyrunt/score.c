/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt - score
*/

/**
 * @file score.c
 * @brief Difficulty scaling and score/bonus display in the HUD window.
 */

#include "game_tyrunt.h"
#include <stdio.h>

/** Derive scroll speed from the score (thresholds 15, 45, 100); forced to 1 while slowed. */
static void update_difficulty(tyrunt_plug_in_t *data)
{
    if (data->slow_timer > 0) {
        data->speed = 1;
        return;
    }
    if (data->score < 15)
        data->speed = 1;
    if (data->score >= 15)
        data->speed = 2;
    if (data->score >= 45)
        data->speed = 3;
    if (data->score >= 100)
        data->speed = 4;
}

/** Return the active bonus: 1 invincible, 2 double jump, 3 slow, 0 none (in that priority). */
static uint8_t get_bonus_state(tyrunt_plug_in_t *data)
{
    if (data->invincible_timer > 0)
        return 1;
    if (data->double_jumps_left > 0)
        return 2;
    if (data->slow_timer > 0)
        return 3;
    return 0;
}

/** Redraw the bonus label only when the displayed state changes. */
static void show_bonus(tyrunt_plug_in_t *data)
{
    uint8_t current_bonus_state = get_bonus_state(data);

    if (current_bonus_state != data->last_displayed_bonus) {
        if (current_bonus_state == 1)
            printToWin(2, 1, "INVINCIBLE!   ");
        if (current_bonus_state == 2)
            printToWin(2, 1, "DOUBLE JUMP!  ");
        if (current_bonus_state == 3)
            printToWin(2, 1, "SLOW MODE!    ");
        if (current_bonus_state == 0) {
            printToWin(2, 1, "              ");
        }
        data->last_displayed_bonus = current_bonus_state;
    }
}

/**
 * @brief Update difficulty, then refresh the bonus label and the score in the window.
 * @param this Game state.
 * @warning The `score != score - 1` test is always true, so the score is redrawn every frame.
 */
void update_score(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    char score_str[20];

    update_difficulty(data);
    show_bonus(data);
    if (data->score != data->score - 1) {
        sprintf(score_str, "SCORE %d    ", data->score);
        printToWin(2, 0, score_str);
    }
}
