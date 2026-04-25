/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_
    #include "entities.h"
    #include "window.h"
    #include "map.h"
    #include <gb/gb.h>

// max 16 entities including the player
// max 2 windows (background and layers) static for now
typedef struct game_s game_t;

struct game_s {
    entities_t entities[16];
    window_t window[2];
    map_t map;
    uint8_t actual_frame; 
    void (*init)(game_t *this);
    void (*update)(game_t *this);
};

void init_game(game_t *game, uint8_t id);
void printToMap(uint8_t x, uint8_t y, char string[255]);

#endif /* !GAME_H_ */
