/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** player
*/

#include "game_wolf3d.h"

const void init_player(game_t *game)
{
    uint16_t i = 0;

    game->entities[0].personal_data = &g_ent_data.wolf3d;
    game->entities[0].life = 100;
    game->entities[0].direction = 0;
    for (; map_level_1.map[i] != SPAWN &&  i < game->map.size; i++);
    game->entities[0].x = INT_TO_FLOAT(i % game->map.width);
    game->entities[0].y = INT_TO_FLOAT(i / game->map.width);

    game->entities[1].sprite_nb = 4;
    for (i = 0; i < 4; i++){
        game->entities[1].sprite_ids[i] = i;
        game->entities[1].sprite_tile[i] = i * 2;
        set_sprite_tile(i, i * 2);
    }

    move_sprite(1, 148, 138);
    move_sprite(2, 140, 138);
}