/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** menu
*/
#include "game.h"
#include "game_menu.h"
#include <string.h>
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

static void player_scroll_bg(game_t *this)
{
    int8_t rel_coord_x = this->entities[0].x >> 3;
    int8_t rel_coord_y = this->entities[0].y >> 3;

    if (rel_coord_x > 8 && rel_coord_x < (map_menu_width))
        this->window[0].x = this->entities[0].x - 6 << 3;
    else
        this->entities[0].x_sprite = this->entities[0].x + 1;
    if (rel_coord_y > 8 && rel_coord_y < (map_menu_height))
        this->window[0].y = this->entities[0].y - 7 << 3;
    else
        this->entities[0].y_sprite = this->entities[0].y + 1;
    move_bkg(this->window[0].x, this->window[0].y);
}

static void handleInput(game_t *this){
    (void)this;
    switch (joypad())
    {
        case J_UP:
            this->entities[0].y -= 1;
            player_scroll_bg(this);
            break;
        case J_DOWN:
            this->entities[0].y += 1;
            player_scroll_bg(this);
            break;
        case J_LEFT:
            this->entities[0].x -= 1;
            player_scroll_bg(this);
            break;
        case J_RIGHT:
            this->entities[0].x += 1;
            player_scroll_bg(this);
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
    get_bkg_xy_addr(this->window[0].x, this->window[0].y);
    get_win_xy_addr(this->window[1].x, this->window[1].y);
}

static void init_entities(game_t *this){
    for (int i = 0; i < 16; i++){
        this->entities[i].sprite_nb = 0;
        this->entities[i].x = 0;
        this->entities[i].y = 0;
    }
    this->entities[0].sprite_nb = 2;
    this->entities[0].x = 80;
    this->entities[0].y = 72;
    this->entities[0].x_sprite = this->entities[0].x;
    this->entities[0].y_sprite = this->entities[0].y;
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
    set_bkg_tiles(0, 0, 32, 32, map_menu);

    move_bkg(6 << 3, 7 << 3);
}

void init_menu(game_t *this)
{
    this->update = &update_menu;
    init_map(this);
    init_graphiques(this);
    init_window(this);
    init_entities(this);
}