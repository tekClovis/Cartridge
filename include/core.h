/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** core
*/

#ifndef CORE_H_
    #define CORE_H_
    #include "game.h"

//@game list of games including menu
//@window list of windows (background and layers) stat
typedef struct core_s {
    game_t game[5];
    game_t *actual_game;
} core_t;

void init_core(core_t *core);
void update_core(core_t *core);

#endif /* !CORE_H_ */
