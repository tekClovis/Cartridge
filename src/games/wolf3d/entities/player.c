/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** player
*/

/**
 * @file player.c
 * @brief Wolf3D player and hand/weapon sprites.
 */

#include "game_wolf3d.h"

/** @brief Toggle the walking animation frame of the hand sprites (entity 1). */
const void anim_machop(game_t *this)
{
    this->entities[1].animation = !this->entities[1].animation;
    set_sprite_tile(0, this->entities[1].sprite_tile[0 + (this->entities[1].animation << 1)]);
    set_sprite_tile(1, this->entities[1].sprite_tile[1 + (this->entities[1].animation << 1)]);
}

/** @brief Toggle the attack animation frame of the weapon sprites (entity 0). */
const void anim_weapon(game_t *this)
{
    this->entities[0].animation = !this->entities[0].animation;
    set_sprite_tile(this->entities[0].sprite_ids[0], this->entities[0].sprite_tile[0 + (this->entities[0].animation << 1)]);
    set_sprite_tile(this->entities[0].sprite_ids[1], this->entities[0].sprite_tile[1 + (this->entities[0].animation << 1)]);
}

/**
 * @brief Place the player on the SPAWN tile (100 HP) and set up both sprite pairs.
 * @param game Game state.
 */
const void init_player(game_t *game)
{
    uint16_t i = 0;

    game->entities[0].personal_data = &g_ent_data.wolf3d;
    game->entities[0].life = 100;
    game->entities[0].direction = 0;
    for (; map_level_1.map[i] != SPAWN &&  i < game->map.size; i++);
    game->entities[0].x = INT_TO_FLOAT(i % game->map.width);
    game->entities[0].y = INT_TO_FLOAT(i / game->map.width);

    game->entities[1].sprite_nb = 2;
    for (i = 0; i < 2; i++){
        game->entities[1].sprite_ids[i] = i;
        game->entities[1].sprite_ids[i + 2] = i;
        game->entities[1].sprite_tile[i] = i * 2;
        game->entities[1].sprite_tile[i + 2] = (i + 2) * 2;
        set_sprite_tile(i, i * 2);
        move_sprite(i, 110 + 8 * i, 142);
    }
    for (i = 0; i < 2; i++){
        game->entities[0].sprite_ids[i] = i + 2;
        game->entities[0].sprite_ids[i + 2] = i + 2;
        game->entities[0].sprite_tile[i] = 8 + i * 2;
        game->entities[0].sprite_tile[i + 2] = 8 + (i + 2) * 2;
        set_sprite_tile(i + 2, 8 + i * 2);
        move_sprite(i + 2, 80 + 8 * i, 124);
    }
}