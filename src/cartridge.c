/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** cartride
*/
#include "core.h"
#include <gb/cgb.h>
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
    SPRITES_8x8;
    init(&core);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
    while (1){
        vsync();
    }
}
