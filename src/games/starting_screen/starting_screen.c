/** @file starting_screen.c
 * @brief Title screen: scrolls the logo in, then waits for START.
 */

/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** starting_screen
*/

#include "game.h"
#include "font.h"
#include "game_start_screen.h"
#include <gb/gb.h>
#include <gb/cgb.h>


/** @brief Switch to the MENU game when START is held. */
static const void handle_input(game_t *this)
{
    if (joypad() & J_START){
        init_game(this, MENU);
    }
}

static const uint16_t spritetiles[9] =
{
    ASCII_TO_TILE('P'),
    ASCII_TO_TILE('R'),
    ASCII_TO_TILE('E'),
    ASCII_TO_TILE('S'),
    ASCII_TO_TILE('S'),
    ASCII_TO_TILE(' '),
    220,
    221,
    222,
};

/** @brief Place the 9 sprites ("PRESS " + 3 tiles 220-222) on one row at y=104. */
static const void init_sprites(void)
{
    SPRITES_8x8;
    for (uint8_t i = 0; i < 9; i++){
        set_sprite_tile(i, spritetiles[i]);
        move_sprite(i, (5 + (i + 1)) << 3, 104);
    }
}

static const void move_cred(game_t *this)
{
    if (this->window[1].x < 20)
        return;
    this->window[1].x -= 1;
    move_win(this->window[1].x, this->window[1].y);
}

/**
 * @brief Per-frame update: scroll the background up, then run the idle phase.
 * @param this Game state; window[0].y is the background scroll, window[1] the credits window.
 * @note Once the scroll reaches 0, sprites and credits are shown once, then input and credits
 *       scrolling run every frame; blink_sprite runs only when actual_frame >> 4 is non-zero.
 */
const void update_start_screen(game_t *this)
{
    if (this->actual_frame >> 1 && this->window[0].y > 0){
        this->window[0].y -= 1;
        SCY_REG = this->window[0].y;
        this->actual_frame = 0;
        if (this->window[0].y == 0){
            init_sprites();
            printToWin(0, 0, "MADE BY C R AND T");
            SHOW_WIN;
        }
    }
    if (this->window[0].y == 0){
        handle_input(this);
        move_cred(this);
        if (this->actual_frame >> 4){
            blink_sprite();
            this->actual_frame = 0;
        }
    }
}

/**
 * @brief Set up the title screen and install update_start_screen as the update callback.
 * @param this Game state; window[0] is set to (0, 96) and window[1] to (160, 128).
 */
const void init_start_screen(game_t *this)
{
    this->actual_frame = 0;
    this->update = &update_start_screen;
    this->window[0].x = 0;
    this->window[0].y = 96;
    this->window[1].x = 160;
    this->window[1].y = 128;
    SCX_REG = this->window[0].x;
    SCY_REG = this->window[0].y;
    move_win(this->window[1].x, this->window[1].y);
    reset_win();
    set_bkg_data(0, pokopie_tileset_TILE_COUNT, pokopie_tileset_tiles);
    reset_bkg();
    set_bkg_tiles(0, 0, 20, 18, pokopie_tilemap);
}