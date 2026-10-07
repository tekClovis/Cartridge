/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** entities
*/

/**
 * @file entities.h
 * @brief Entity (sprite-group) type, per-game entity plug-in data and draw helpers.
 */

#ifndef ENTITIES_H_
    #define ENTITIES_H_
    /** Size in bytes of the shared plug-in data unions. */
    #define MAX_PLUG_IN_BYTES 128
    #include <stdint.h>

    /** Wolf3D per-entity data. */
    typedef struct w3d_ent_plug_in_s {
        uint8_t angles[16];
    } w3d_ent_plug_in_t;

    /** Entity data of the running game; the members overlay the same storage. */
    typedef union {
        uint8_t data[MAX_PLUG_IN_BYTES];
        w3d_ent_plug_in_t wolf3d;
    } active_ent_data_t;

    /** Global instance of the entity plug-in data union. */
    extern active_ent_data_t g_ent_data;

/** A sprite-based game entity: position, sprite tiles and state. */
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

/**
 * @brief Draw an entity as a 16x16 sprite group.
 * @param ent Entity to draw, passed by value.
 */
void draw_ent16(const entities_t ent);
/**
 * @brief Draw an entity as 8x8 sprites.
 * @param ent Entity to draw, passed by value.
 */
void draw_ent8(const entities_t ent);
#endif
