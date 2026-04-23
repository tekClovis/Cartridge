/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** cartride
*/
#include "core.h"
#include <gb/cgb.h>
#include <gb/sgb.h>
#include <string.h>

void init(core_t *core)
{
    cpu_fast();
    init_core(core);
}

int main(void){
    core_t core;
    memset(&core, 0, sizeof(core));

    DISPLAY_OFF;
    HIDE_BKG;
    HIDE_WIN;
    SPRITES_8x16;
    init(&core);

    SHOW_BKG;
    SHOW_SPRITES;
    // SHOW_WIN;
    // move_window(0, 6);
    DISPLAY_ON;
    uint8_t count = 0;
    while (1){
        vsync();
        update_core(&core);
    }
}
