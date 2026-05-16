/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt - score
*/

#include "game_tyrunt.h"

uint8_t collide(unsigned int px, unsigned int py,
    unsigned int ox, unsigned int oy)
{
    return (px < ox + 12 && px + 12 > ox &&
            py < oy + 12 && py + 16 > oy);
}
