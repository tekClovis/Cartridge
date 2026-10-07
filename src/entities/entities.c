/**
 * @file entities.c
 * @brief Move the hardware sprites that make up an entity.
 */
#include "entities.h"
#include <gb/gb.h>

/**
 * @brief Place an entity's sprites side by side (8x16 sprite mode).
 * @param ent Entity; sprite i is drawn at x_sprite + 8 * i, y_sprite + 8.
 */
void draw_ent16(const entities_t ent){
    for (uint8_t i = 0; i < ent.sprite_nb; i++){
        move_sprite(ent.sprite_ids[i], ent.x_sprite + 8 * i, ent.y_sprite + 8);
    }
}

/**
 * @brief Place an entity's sprites using fixed offsets (8x8 sprite mode).
 * @param ent Entity; each sprite's tile is set to its own sprite id.
 * @warning Offsets exist for 4 sprites only; sprite_nb above 4 reads past the table.
 */
void draw_ent8(const entities_t ent){
    int8_t off_mapping[8] = {-8, -8, 0, -8, 0, -8, 0, 0};

    for (uint8_t i = 0; i < ent.sprite_nb; i++){
        set_sprite_tile(ent.sprite_ids[i], ent.sprite_ids[i]);
        move_sprite(ent.sprite_ids[i], ent.x_sprite + off_mapping[i << 1], ent.y_sprite + off_mapping[(i << 1) + 1]);
    }
}