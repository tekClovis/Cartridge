/**
 * @file cartridge.c
 * @brief Entry point: hardware init and the per-frame game loop.
 */
#include "game.h"
#include <gb/cgb.h>
#include <gb/sgb.h>
#include <string.h>

/** @brief Reset any high score above 999 (uninitialised or corrupt save RAM) to 0. */
static const void check_save(void)
{
    SWITCH_RAM(0);
    ENABLE_RAM;
    for (uint8_t i = 0; i < 3; i++) {
        if (high_scores[i] > 999)
            high_scores[i] = 0;
    }
    DISABLE_RAM;
}

/**
 * @brief Configure display and CPU, clear @p game, and enter START_SCREEN.
 * @param[out] game Game state, zeroed then initialised.
 * @note Switches to CGB double speed and 8x16 sprites; font tiles load at BG tile 209.
 */
static const void init(game_t *game)
{
    HIDE_BKG;
    HIDE_WIN;
    HIDE_SPRITES;
    SPRITES_8x16;
    DISPLAY_OFF;
    cpu_fast();
    memset(game, 0, sizeof(*game));
    set_bkg_data(209, font_TILE_COUNT, font_tiles);
    check_save();
    init_game(game, START_SCREEN);
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
}

/** @brief Advance the frame counter and run the current screen's update callback. */
static const void update(game_t *game)
{
    game->actual_frame++;
    game->update(game);
}

int main(void){
    game_t game;

    init(&game);
    while (1){
        update(&game);
        vsync();
    }
}
