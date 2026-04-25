/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** anims
*/
#include <gb/gb.h>
#include <gb/sgb.h>

void restore_pal(void) {
    OBP0_REG = DMG_PALETTE(0, 1, 2, 3);
    OBP1_REG = DMG_PALETTE(0, 1, 2, 3);
    BGP_REG = DMG_PALETTE(0, 1, 2, 3);
}

void blink_sprite(void){
    OBP0_REG = DMG_PALETTE(0, OBP0_REG >> 6,
        (OBP0_REG >> 2) & 0b11, (OBP0_REG >> 4) & 0b11);
}
void blink_bg(void){
    BGP_REG = DMG_PALETTE(0, BGP_REG >> 6,
         (BGP_REG >> 2) & 0b11, (BGP_REG >> 4) & 0b11);
}