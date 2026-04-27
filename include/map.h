/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_
    #include <stdint.h>

    typedef const enum tile_effect {
        VOID,
        WALL,
        SPAWN,
        TILE_EFFECT_COUNT
    } tile_id;
    typedef struct map_s {
        uint8_t map[256];
        uint16_t width;
        uint16_t height;
        uint16_t size;
    } map_t;
#endif /* !MAP_H_ */