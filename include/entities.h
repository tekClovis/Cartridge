/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** entities
*/

#ifndef ENTITIES_H_
    #define ENTITIES_H_
    #include <stdint.h>
    #include <gb/cgb.h>



typedef struct entities_s {
    uint8_t x;
    uint8_t y;
    uint8_t sprite_ids[4];
    uint8_t sprite_nb;
} entities_t;

#endif
