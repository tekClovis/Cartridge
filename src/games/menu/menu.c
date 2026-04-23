/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** menu
*/
#include "game.h"
#include "game_menu.h"
#include <string.h>
#include <stdio.h>
#include "map.h"
#include <gb/gb.h>

// static const palette_color_t menu_bg_palette[4] = {
//     RGB8(250, 242, 215), RGB8(196, 175, 112), RGB8(102, 112, 74), RGB8( 26,  34,  40)
// };

// static const palette_color_t menu_sprite_palette[4] = {
//     RGB8(255, 232, 204), RGB8(240, 173, 108), RGB8(142,  84,  84), RGB8( 25,  20,  23)
// };

// static void apply_color_mapping(void)
// {
//     // Swap middle shades for stronger contrast on DMG palettes.
//     BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_DARK_GRAY, DMG_LITE_GRAY, DMG_BLACK);
//     OBP0_REG = DMG_PALETTE(DMG_WHITE, DMG_DARK_GRAY, DMG_LITE_GRAY, DMG_BLACK);
//     OBP1_REG = DMG_PALETTE(DMG_WHITE, DMG_BLACK, DMG_DARK_GRAY, DMG_LITE_GRAY);

//     if (DEVICE_SUPPORTS_COLOR) {
//         set_bkg_palette(0, 1, menu_bg_palette);
//         set_sprite_palette(0, 1, menu_sprite_palette);
//     }
// }

static void scroll_x(game_t *this, uint8_t action)
{
    uint8_t rel_coord_x = (uint8_t)(this->entities[0].x >> 3) < 10 ? 10 : (uint8_t)(this->entities[0].x >> 3);
    uint8_t rel_coord_y = (uint8_t)(this->entities[0].y >> 3) < 9 ? 9 : (uint8_t)(this->entities[0].y >> 3);

    if (rel_coord_x > 10 && rel_coord_x < (map_menu_width - 10)){
        this->window[0].x = rel_coord_x == 10 ? 10 : this->entities[0].x - 10 * 8;
        if (action == J_RIGHT)    
            set_bkg_submap(rel_coord_x + 10, rel_coord_y - 9, 1, 19u
                , map_menu//map_menu[(rel_coord_y - 9) * map_menu_width + rel_coord_x + 10]
                , map_menu_width);
        if (action == J_LEFT)
            set_bkg_submap(rel_coord_x - 10, rel_coord_y - 9, 1, 19u
                ,map_menu//map_menu[(rel_coord_y + 10) * map_menu_width + rel_coord_x - 10]
                , map_menu_width);
        move_bkg(this->window[0].x, this->window[0].y);
    } else
        this->entities[0].x_sprite = (uint8_t)this->entities[0].x;
    if (this->entities[0].x_sprite > 20 << 3)
        this->entities[0].x_sprite -= 12 << 3;
}

static void scroll_y(game_t *this, uint8_t action)
{
    uint8_t rel_coord_x = (uint8_t)(this->entities[0].x >> 3) < 10 ? 10 : (uint8_t)(this->entities[0].x >> 3);
    uint8_t rel_coord_y = (uint8_t)(this->entities[0].y >> 3) < 9 ? 9 : (uint8_t)(this->entities[0].y >> 3);

    if (rel_coord_y > 9 && rel_coord_y < (map_menu_height - 9)){
        this->window[0].y = rel_coord_y == 9 ? 10 : this->entities[0].y - 9 * 8;
        if (action == J_UP)
            set_bkg_submap(rel_coord_x - 10, rel_coord_y - 9
                , 21u, 1, map_menu
                , map_menu_width);
        if (action == J_DOWN)
            set_bkg_submap(rel_coord_x - 10, rel_coord_y + 9
            , 21u, 1 ,map_menu//map_menu[(rel_coord_y - 9) * map_menu_width + rel_coord_x + 10]
            , map_menu_width);
        move_bkg(this->window[0].x, this->window[0].y);
    } else
        this->entities[0].y_sprite = (uint8_t)this->entities[0].y;
    if (this->entities[0].y_sprite > 18 << 3)
        this->entities[0].y_sprite -= 14  << 3;
}

static void handleInput(game_t *this){
    switch (joypad())
    {
        case J_UP:
            scroll_y(this, J_UP);
            if (this->entities[0].y >> 3 > 0)
                this->entities[0].y -= 1;
            break;
            case J_DOWN:
            scroll_y(this, J_DOWN);
            if (this->entities[0].y >> 3 < (this->map.height - 1))
                this->entities[0].y += 1;
            break;
            case J_LEFT:
            scroll_x(this, J_LEFT);
            if (this->entities[0].x >> 3 > 0)
                this->entities[0].x -= 1;
            break;
        case J_RIGHT:
            scroll_x(this, J_RIGHT);
            if (this->entities[0].x >> 3 < (this->map.width - 1))
                this->entities[0].x += 1;
            break;
        case J_A:
            break;
        case J_B:
            break;
        default:
            return;
    }
}

void update_menu(game_t *this)
{
    handleInput(this);
    draw_ent16(this->entities[0]);
}

static void init_map(game_t *this)
{
    
    this->map.width = map_menu_width;
    this->map.height = map_menu_height;
    this->map.size = map_menu_size;
}

static void init_window(game_t *this)
{
    this->window[0].x = 6 << 3;
    this->window[0].y = 7 << 3;
    move_bkg(this->window[0].x, this->window[0].y);
}

static void init_entities(game_t *this){
    for (int i = 0; i < 16; i++){
        this->entities[i].sprite_nb = 0;
        this->entities[i].x = 0;
        this->entities[i].y = 0;
    }
    this->entities[0].sprite_nb = 2;
    this->entities[0].x = 32 << 2;
    this->entities[0].y = 32 << 2;
    this->entities[0].x_sprite = 80;
    this->entities[0].y_sprite = 72;
    for (int i = 0; i < 2; i++){
        this->entities[0].sprite_ids[i] = i;
        set_sprite_tile(this->entities[0].sprite_ids[i], this->entities[0].sprite_ids[i] * 2);
    }
}

static void init_graphiques(game_t *this){
    (void)this;
    // apply_color_mapping();
    SWITCH_ROM(BANK(metamorph));
    set_sprite_data(0, metamorph_TILE_COUNT, metamorph_tiles);
    SWITCH_ROM(BANK(menu_tilesets)); 
    set_bkg_data(0, menu_tilesets_TILE_COUNT, menu_tilesets_tiles);
    SWITCH_ROM(BANK(menu_tilemap));
    set_bkg_submap(0, 0, 32, 32, map_menu, map_menu_width);
}

void init_menu(game_t *this)
{
    this->update = &update_menu;
    init_map(this);
    init_graphiques(this);
    init_window(this);
    init_entities(this);
}