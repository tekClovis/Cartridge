/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

/**
 * @file spawner.c
 * @brief Spawning of obstacles and bonuses on the right edge of the screen.
 */

#include "game_tyrunt.h"

/** Place the bonus at x = 160 when DIV_REG is a multiple of 600, at one of two heights. */
static void spawn_bonus(game_t *this)
{
    if (DIV_REG % 600 == 0) {
        this->entities[3].x = 160;
        if (DIV_REG % 2 == 0) {
            this->entities[3].y = 112;
        } else {
            this->entities[3].y = 65;
        }
    }
}

static void manage_bonus(game_t *this)
{
    if (this->entities[3].x >= 250)
        spawn_bonus(this);
}

/**
 * @brief Choose an inactive obstacle, preferring tree or Tylton at random via DIV_REG.
 * @return Entity index (1 tree, 2 Tylton), or 0 if both are already on screen.
 */
static uint8_t get_obstacle_to_spawn(game_t *this)
{
    uint8_t primary = 2;
    uint8_t fallback = 1;

    if (DIV_REG % 2 == 0) {
        primary = 1;
        fallback = 2;
    }
    if (this->entities[primary].x >= 250)
        return primary;
    if (this->entities[fallback].x >= 250)
        return fallback;
    return 0;
}

/**
 * @brief Spawn a bonus and, after a cooldown, one obstacle at x = 160.
 * @param this Game state.
 * @note No obstacle spawns while another is between x = 80 and 250. The next cooldown is
 *       80 to 119 frames, randomised from DIV_REG.
 */
void manage_spawner(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    int16_t safe_gap = 80 + (DIV_REG % 40);
    uint8_t target = 0;

    manage_bonus(this);
    if (data->spawn_timer > 0) {
        data->spawn_timer--;
        return;
    }
    if ((this->entities[1].x < 250 && this->entities[1].x > 80) ||
        (this->entities[2].x < 250 && this->entities[2].x > 80)) {
        return;
    }
    target = get_obstacle_to_spawn(this);
    if (target != 0) {
        this->entities[target].x = 160;
        data->spawn_timer = safe_gap;
    }
}
