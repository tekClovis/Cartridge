/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** entities
*/

#ifndef ENTITIES_H_
    #define ENTITIES_H_
    #include <stdint.h>


typedef struct entities_s {
    uint16_t x;
    uint16_t y;
    uint8_t x_sprite;
    uint8_t y_sprite;
    uint8_t sprite_ids[4];
    uint8_t sprite_nb;
} entities_t;

void draw_ent16(const entities_t ent);
void draw_ent8(const entities_t ent);
#endif
