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
    HIDE_BKG;
    HIDE_WIN;
    HIDE_SPRITES;
    SPRITES_8x16;
    cpu_fast();
    init_core(core);
    SHOW_BKG;
    SHOW_SPRITES;
}

int main(void){
    core_t core;
    memset(&core, 0, sizeof(core));

    init(&core);
    while (1){
        update_core(&core);
        vsync();
    }
}
