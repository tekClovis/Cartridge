/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_
    #include <stdint.h>

    typedef struct map_s {
        uint8_t map[4096];
        uint16_t width;
        uint16_t height;
        uint16_t size;
    } map_t;
#endif /* !MAP_H_ */