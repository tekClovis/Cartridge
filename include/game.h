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
    #include "save.h"
    #include <gb/gb.h>
    #define MAX_ENTITIES 16
    #define MAX_WINDOWS 2
    #define NORMAL_PAL 0xE4
    #define MAX_PLUG_IN_BYTES 128

    typedef struct game_s game_t;

    typedef struct w3d_plug_in_s {
        int8_t last_rays[20];
        int8_t rays[20];
        int8_t side[20];
        int8_t x_tiles_touch[20];
        int8_t y_tiles_touch[20];
    } w3d_plug_in_t;

    typedef struct tyrunt_plug_in_s {
        int8_t velocity_y;
        uint8_t is_jumping;
        uint16_t score;
        uint8_t speed;
        int16_t spawn_timer;
        uint16_t invincible_timer;
        uint8_t double_jumps_left;
        uint16_t slow_timer;
        uint8_t last_displayed_bonus;
    } tyrunt_plug_in_t;

    typedef union {
        uint8_t data[MAX_PLUG_IN_BYTES];
        w3d_plug_in_t wolf3d;
        tyrunt_plug_in_t tyrunt;
    } active_game_data_t;

    extern active_game_data_t g_game_data;
    struct game_s {
        entities_t entities[MAX_ENTITIES];
        window_t window[MAX_WINDOWS];
        map_t map;
        uint8_t actual_frame;
        uint16_t frame_counter;
        uint16_t score;
        uint8_t game_over;
        const void (*init)(game_t *this);
        const void (*update)(game_t *this);
        void *personal_data;
    };

    typedef enum game_id_e {
        START_SCREEN,
        MENU,
        WOLF_3D,
        TYRUNT,
        GAME_3,
        GAME_ID_COUNT
    } game_id;

    typedef struct rectangle_s {
        uint8_t x;
        uint8_t y;
        uint8_t width;
        uint8_t height;
    } rectangle_t;
    
    //utils
    const void init_game(game_t *game, game_id id);
    const void printToMap(uint8_t x, uint8_t y, const char string[256]);
    const void printToWin(uint8_t x, uint8_t y, const char string[256]);
    const void reset_win(void);
    const void reset_bkg(void);
    const void clear_sprite_tiles(void);
    const int8_t point_in_rect(const uint8_t x, const uint8_t y,
    const rectangle_t *rect);
    const void set_high_score(game_id id, uint16_t score);
    
    //anims
    const void blink_sprite(void);
    const void blink_bg(void);
    const void restore_pal(void);
    const void fade_out(void);
    const void fade_in(void);
    

#endif /* !GAME_H_ */
