/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** entities
*/

#ifndef ENTITIES_H_
    #define ENTITIES_H_
    #define MAX_PLUG_IN_BYTES 128
    #include <stdint.h>

    typedef struct w3d_ent_plug_in_s {
        uint8_t angles[16];
    } w3d_ent_plug_in_t;

    typedef union {
        uint8_t data[MAX_PLUG_IN_BYTES];
        w3d_ent_plug_in_t wolf3d;
    } active_ent_data_t;

    extern active_ent_data_t g_ent_data;

typedef struct entities_s {
    uint16_t x;
    uint16_t y;
    uint8_t x_sprite;
    uint8_t y_sprite;
    uint8_t sprite_ids[4];
    uint8_t sprite_tile[4];
    uint8_t direction;
    uint8_t animation;
    uint8_t sprite_nb;
    uint8_t life;
    void *personal_data;
} entities_t;

void draw_ent16(const entities_t ent);
void draw_ent8(const entities_t ent);
#endif
