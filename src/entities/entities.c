/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** entities
*/
#include "entities.h"
#include <gb/gb.h>

// function for 8x16 Sprrite displaying mode
void draw_ent16(const entities_t ent){
    for (uint8_t i = 0; i < ent.sprite_nb; i++){
        move_sprite(ent.sprite_ids[i], ent.x + 8 * i, ent.y + 8);
    }
}

//off mapping for 8x8 sprites to be centered on the entity position
void draw_ent8(const entities_t ent){
    int8_t off_mapping[8] = {-8, -8, 0, -8, 0, -8, 0, 0};

    for (uint8_t i = 0; i < ent.sprite_nb; i++){
        set_sprite_tile(ent.sprite_ids[i], ent.sprite_ids[i]);
        move_sprite(ent.sprite_ids[i], ent.x + off_mapping[i << 1], ent.y + off_mapping[(i << 1) + 1]);
    }
}