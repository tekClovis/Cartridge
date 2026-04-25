/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** starting_screen
*/

#include "game.h"
#include "game_start_screen.h"
#include <gb/gb.h>


static
void handle_input(game_t *this)
{
    if (joypad() & J_START){
        init_game(this, 0);
    }
}

void update_start_screen(game_t *this)
{
    if (this->actual_frame >> 1 && this->window[0].y > 0){
        this->window[0].y -= 1;
        SCY_REG = this->window[0].y;
        this->actual_frame = 0;
        if (this->window[0].y == 0)
            printToMap(this, 5, 11, "PRESS ");
    }
    if (this->actual_frame >> 2 && this->window[0].y == 0){
        this->actual_frame = 0;
        handle_input(this);
    }
}

static void init_entities(game_t *this)
{
    (void)this;
}

void init_start_screen(game_t *this)
{
    this->actual_frame = 0;
    this->update = &update_start_screen;
    this->window[0].x = 0;
    this->window[0].y = 12 << 3;
    SCY_REG = this->window[0].y;
    SWITCH_ROM(BANK(pokopie_tileset));
    set_bkg_data(0, pokopie_tileset_TILE_COUNT, pokopie_tileset_tiles);
    set_bkg_tiles(0, 0, 20, 18, pokopie_tilemap);
}