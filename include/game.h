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
    #include "font.h"
    #include <gb/gb.h>
    #define MAX_ENTITIES 16
    #define MAX_WINDOWS 2
    #define NORMAL_PAL 0xE4

    typedef struct game_s game_t;

    struct game_s {
        entities_t entities[MAX_ENTITIES];
        window_t window[MAX_WINDOWS];
        map_t map;
        uint8_t actual_frame; 
        void (*init)(game_t *this);
        void (*update)(game_t *this);
    };

    typedef const enum game_id_e {
        START_SCREEN,
        MENU,
        GAME_1,
        GAME_2,
        GAME_3
    } game_id;

    //utils
    const void init_game(game_t *game, game_id id);
    const void printToMap(const game_t *game, uint8_t x, uint8_t y, char string[256]);
    const void printToWin(const game_t *game, uint8_t x, uint8_t y, char string[256]);

    //anims
    const void blink_sprite(void);
    const void blink_bg(void);
    const void restore_pal(void);
    const void fade_out(void);
    const void fade_in(void);

#endif /* !GAME_H_ */
