/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** game
*/

/**
 * @file game.h
 * @brief Core game structure, shared plug-in data, and display/animation utilities.
 */

#ifndef GAME_H_
    #define GAME_H_
    #include "entities.h"
    #include "window.h"
    #include "map.h"
    #include "font.h"
    #include "save.h"
    #include <gb/gb.h>
    /** Number of entity slots in a game_t. */
    #define MAX_ENTITIES 16
    /** Number of window_t slots in a game_t. */
    #define MAX_WINDOWS 2
    /** Default DMG palette register value (0xE4). */
    #define NORMAL_PAL 0xE4
    /** Size in bytes of the shared plug-in data union. */
    #define MAX_PLUG_IN_BYTES 128

    typedef struct game_s game_t;

    /** Wolf3D raycaster state. */
    typedef struct w3d_plug_in_s {
        int8_t last_rays[20];
        int8_t rays[20];
        int8_t side[20];
        int8_t x_tiles_touch[20];
        int8_t y_tiles_touch[20];
    } w3d_plug_in_t;

    /** Tyrunt game state. */
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

    /** Snake game state; body_x/body_y hold up to 30 segments. */
    typedef struct snake_plug_in_s {
        uint16_t score;
        uint8_t speed;
        uint8_t direction;
        uint8_t snake_length;
        uint8_t move_delay;
        uint8_t food_x;
        uint8_t food_y;
        uint8_t body_x[30];
        uint8_t body_y[30];
    } snake_plug_in_t;

    /** Per-game state of the running game; members overlay the same storage. */
    typedef union {
        uint8_t data[MAX_PLUG_IN_BYTES];
        w3d_plug_in_t wolf3d;
        tyrunt_plug_in_t tyrunt;
        snake_plug_in_t snake;
    } active_game_data_t;

    /** Global instance of the game plug-in data union. */
    extern active_game_data_t g_game_data;
    /** Game state; init and update are the callbacks of the current game. */
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

    /** Identifier of a game or screen. */
    typedef enum game_id_e {
        START_SCREEN,
        MENU,
        WOLF_3D,
        TYRUNT,
        SNAKE,
        GAME_ID_COUNT
    } game_id;

    /** Axis-aligned rectangle. */
    typedef struct rectangle_s {
        uint8_t x;
        uint8_t y;
        uint8_t width;
        uint8_t height;
    } rectangle_t;
    
    //utils
    /**
     * @brief Switch to the game or screen @p id and run its init function.
     * @param game Game state passed to the init function.
     * @param id Target game; an out-of-range id leaves the display off.
     * @note Fades out (except for START_SCREEN), clears sprites, background and window,
     *       then fades back in after init.
     */
    const void init_game(game_t *game, game_id id);
    /**
     * @brief Print a string on the background layer, one tile per character.
     * @param x First tile column.
     * @param y Tile row.
     * @param string NUL-terminated text; no wrapping is done.
     */
    const void printToMap(uint8_t x, uint8_t y, const char string[256]);
    /**
     * @brief Print a string on the window layer, wrapping past column 20.
     * @param x First tile column, also the column restored on wrap.
     * @param y Tile row.
     * @param string NUL-terminated text.
     */
    const void printToWin(uint8_t x, uint8_t y, const char string[256]);
    /** @brief Fill the window tile map with the blank tile. */
    const void reset_win(void);
    /** @brief Fill the background tile map with the blank tile. */
    const void reset_bkg(void);
    /** @brief Set all 40 OAM sprites to the blank tile. */
    const void clear_sprite_tiles(void);
    /**
     * @brief Test whether a point lies inside a rectangle.
     * @return Non-zero if inside; right and bottom edges are exclusive.
     */
    const int8_t point_in_rect(const uint8_t x, const uint8_t y,
    const rectangle_t *rect);
    /**
     * @brief Store @p score as the high score of a game if it beats the saved one.
     * @param id WOLF_3D, TYRUNT or SNAKE; other ids are ignored.
     * @param score Score to compare with the saved high score.
     * @note Temporarily enables cartridge RAM (bank 0).
     */
    const void set_high_score(game_id id, uint16_t score);
    
    //anims
    /** @brief Rewrite OBP0 with a shifted colour mapping for a blink effect. */
    const void blink_sprite(void);
    /** @brief Same remapping as blink_sprite(), applied to BGP. */
    const void blink_bg(void);
    /** @brief Reset OBP0, OBP1 and BGP to NORMAL_PAL. */
    const void restore_pal(void);
    /** @brief Fade the palettes towards black, one step every 16 frames (blocking). */
    const void fade_out(void);
    /** @brief Fade the palettes back towards NORMAL_PAL, one step every 16 frames (blocking). */
    const void fade_in(void);
    

#endif /* !GAME_H_ */
