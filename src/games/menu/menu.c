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

static void scroll_x(game_t *this, uint8_t action)
{
    uint8_t rel_coord_x = (uint8_t)(this->entities[0].x >> 3) < 10 ? 10 : (uint8_t)(this->entities[0].x >> 3);
    uint8_t rel_coord_y = (uint8_t)(this->entities[0].y >> 3) < 9 ? 9 : (uint8_t)(this->entities[0].y >> 3);
    
    if (rel_coord_x > 21)
        rel_coord_x = 22;
    if (rel_coord_y > 54)
        rel_coord_y = 55;
    if (rel_coord_x > 10 && rel_coord_x < (map_menu_width - 11)){
        this->window[0].x = this->entities[0].x - 10 * 8;
        if (action == J_RIGHT)    
            set_bkg_submap(rel_coord_x + 10, rel_coord_y - 9, 1, 19u
                , map_menu
                , map_menu_width);
        if (action == J_LEFT)
            set_bkg_submap(rel_coord_x - 10, rel_coord_y - 9, 1, 19u
                ,map_menu
                , map_menu_width);
    } else
        this->entities[0].x_sprite = (uint8_t)this->entities[0].x;
    if (this->entities[0].x_sprite > 20 << 3)
        this->entities[0].x_sprite -= 12 << 3;
}

static void scroll_y(game_t *this, uint8_t action)
{
    uint8_t rel_coord_x = (uint8_t)(this->entities[0].x >> 3) < 10 ? 10 : (uint8_t)(this->entities[0].x >> 3);
    uint8_t rel_coord_y = (uint8_t)(this->entities[0].y >> 3) < 9 ? 9 : (uint8_t)(this->entities[0].y >> 3);

    if (rel_coord_x > 21)
        rel_coord_x = 22;
   if (rel_coord_y > 54)
        rel_coord_y = 55;

    if (rel_coord_y > 9 && rel_coord_y < (map_menu_height - 10)){
        this->window[0].y = this->entities[0].y - 9 * 8;
        if (action == J_UP)
            set_bkg_submap(rel_coord_x - 10, rel_coord_y - 9
                , 21u, 1, map_menu, map_menu_width);
        if (action == J_DOWN)
            set_bkg_submap(rel_coord_x - 10, rel_coord_y + 9
            , 21u, 1 ,map_menu, map_menu_width);
    } else
        this->entities[0].y_sprite = (uint8_t)this->entities[0].y;
    if (this->entities[0].y_sprite > 18 << 3)
        this->entities[0].y_sprite -= 14  << 3;
}

static void trying_to_enter_game(game_t *this)
{
    uint8_t rel_coord_x = (uint8_t)(this->entities[0].x >> 3);
    uint8_t rel_coord_y = (uint8_t)(this->entities[0].y >> 3);

    if (rel_coord_x == 5 && rel_coord_y == 12){
        printf("entering game\n"); 
    }
}

static void handleInput(game_t *this){
    switch (joypad())
    {
        case J_UP:
            scroll_y(this, J_UP);
            if (this->entities[0].y >> 3 > 0){
                this->entities[0].y -= 1;
                SCY_REG = this->window[0].y;
                set_sprite_tile(this->entities[0].sprite_ids[0], 8);
                set_sprite_tile(this->entities[0].sprite_ids[1], 10);
            }
            break;
        case J_DOWN:
            scroll_y(this, J_DOWN);
            if (this->entities[0].y >> 3 < (this->map.height - 1)){
                this->entities[0].y += 1;
                SCY_REG = this->window[0].y;
                set_sprite_tile(this->entities[0].sprite_ids[0], 0);
                set_sprite_tile(this->entities[0].sprite_ids[1], 2);
            }
            break;
            case J_LEFT:
            scroll_x(this, J_LEFT);
            if (this->entities[0].x >> 3 > 0){
                this->entities[0].x -= 1;
                SCX_REG = (uint8_t)this->window[0].x ;
            }
            break;
        case J_RIGHT:
            scroll_x(this, J_RIGHT);
            if (this->entities[0].x >> 3 < (this->map.width - 1)){
                this->entities[0].x += 1;
                SCX_REG = (uint8_t)this->window[0].x ;
            }
            set_sprite_tile(this->entities[0].sprite_ids[0], 16);
            set_sprite_tile(this->entities[0].sprite_ids[1], 17);
            break;
        case J_A:
            trying_to_enter_game(this);
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