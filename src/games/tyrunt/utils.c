/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt - score
*/

/**
 * @file utils.c
 * @brief Collision helper.
 */

#include "game_tyrunt.h"

/**
 * @brief Test whether the player box overlaps an object box (screen coordinates).
 * @param px Player x.
 * @param py Player y.
 * @param ox Object x.
 * @param oy Object y.
 * @return 1 on overlap, 0 otherwise.
 * @note Object box is 12x12; the player box is 12 wide and 16 tall.
 */
uint8_t collide(unsigned int px, unsigned int py,
    unsigned int ox, unsigned int oy)
{
    return (px < ox + 12 && px + 12 > ox &&
        py < oy + 12 && py + 16 > oy);
}
