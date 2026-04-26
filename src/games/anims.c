/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** anims
*/
#include <gb/gb.h>
#include <gb/sgb.h>
#include "game.h"

const void restore_pal(void)
{
    OBP0_REG = NORMAL_PAL;
    OBP1_REG = NORMAL_PAL;
    BGP_REG = NORMAL_PAL;
}

const void blink_sprite(void)
{
    OBP0_REG = DMG_PALETTE(0, OBP0_REG >> 6,
        (OBP0_REG >> 2) & 0b11, (OBP0_REG >> 4) & 0b11);
}

const void blink_bg(void)
{
    BGP_REG = DMG_PALETTE(0, BGP_REG >> 6,
         (BGP_REG >> 2) & 0b11, (BGP_REG >> 4) & 0b11);
}

const void fade_out(void)
{
    uint8_t frame = 0;

    while (OBP0_REG != 0 &&  OBP1_REG != 0 && BGP_REG != 0){
        wait_vbl_done();
        frame++;
        if (frame < 16)
            continue;
        frame = 0;
        OBP0_REG = DMG_PALETTE(0, OBP0_REG &0b11, (OBP0_REG >> 2) & 0b11,
            (OBP0_REG >> 4) & 0b11);
        OBP1_REG = DMG_PALETTE(0, OBP1_REG &0b11, (OBP1_REG >> 2) & 0b11,
            (OBP1_REG >> 4) & 0b11);
        BGP_REG = DMG_PALETTE(0, BGP_REG &0b11, (BGP_REG >> 2) & 0b11,
            (BGP_REG >> 4) & 0b11);
    }
}

const void fade_in(void)
{
    uint8_t frame = 0;
    uint8_t count = 0;

    while (OBP0_REG != NORMAL_PAL &&  OBP1_REG != NORMAL_PAL && BGP_REG != NORMAL_PAL){
        wait_vbl_done();
        frame++;
        if (frame < 16)
            continue;
        frame = 0;
        OBP0_REG = NORMAL_PAL & (0b11 << (count << 1)) | OBP0_REG;
        OBP1_REG = NORMAL_PAL & (0b11 << (count << 1)) | OBP0_REG;
        BGP_REG = NORMAL_PAL & (0b11 << (count << 1)) | OBP0_REG;
        count++;
    }
}
