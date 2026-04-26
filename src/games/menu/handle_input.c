/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** handle_input
*/

#include "game.h"
#include "game_menu.h"
#include <gb/gb.h>
#include <stdio.h>


static const void scroll_x(game_t *this, uint8_t action)
{
    uint8_t rel_coord_x = (uint8_t)(this->entities[0].x >> 3) < 10 ? 10 : (uint8_t)(this->entities[0].x >> 3);
    uint8_t rel_coord_y = (uint8_t)(this->entities[0].y >> 3) < 9 ? 9 : (uint8_t)(this->entities[0].y >> 3);
    
    if (rel_coord_x > 22)
        rel_coord_x = 22;
    if (rel_coord_y > 54)
        rel_coord_y = 54;
    if (this->entities[0].x > (10 << 3) && this->entities[0].x < (map_menu_width - 10) << 3){
        this->window[0].x = this->entities[0].x - (10 << 3);
        if (action == J_RIGHT)    
            set_bkg_submap(rel_coord_x + 10,rel_coord_y  - 9, 1, 19u
                , map_menu, map_menu_width);
        if (action == J_LEFT)
            set_bkg_submap(rel_coord_x - 10,rel_coord_y  - 9, 1, 19u
                , map_menu, map_menu_width);
    }
    if (this->entities[0].x < (10 << 3) + 1 || this->entities[0].x > ((map_menu_width - 11) << 3) - 1)
        this->entities[0].x_sprite = (uint8_t)this->entities[0].x;
    if (this->entities[0].x_sprite > 20 << 3)
        this->entities[0].x_sprite -= 11 << 3;
}

static const void scroll_y(game_t *this, uint8_t action)
{
    uint8_t rel_coord_x = (uint8_t)(this->entities[0].x >> 3) < 11 ? 11 : (uint8_t)(this->entities[0].x >> 3);
    uint8_t rel_coord_y = (uint8_t)(this->entities[0].y >> 3) < 9 ? 9 : (uint8_t)(this->entities[0].y >> 3);

    if (rel_coord_x > 21)
        rel_coord_x = 21;
    if (rel_coord_y > 54)
        rel_coord_y = 54;
    if (this->entities[0].y > (9 << 3) && this->entities[0].y < (map_menu_height - 10) << 3){
        this->window[0].y = this->entities[0].y - (9 << 3);
        if (action == J_UP)
            set_bkg_submap(rel_coord_x - 11, rel_coord_y - 9
                , 22u, 1, map_menu, map_menu_width);
        if (action == J_DOWN)
            set_bkg_submap(rel_coord_x - 11, rel_coord_y + 9
            , 22u, 1 ,map_menu, map_menu_width);
    }
    if (this->entities[0].y + 1 < (9 << 3) || this->entities[0].y > ((map_menu_height - 10) << 3))
        this->entities[0].y_sprite = (uint8_t)this->entities[0].y;
    if (this->entities[0].y_sprite > 18 << 3)
        this->entities[0].y_sprite -= 13  << 3;
}

static const void trying_to_enter_game(game_t *this)
{
    uint8_t rel_coord_x = (uint8_t)(this->entities[0].x >> 3);
    uint8_t rel_coord_y = (uint8_t)(this->entities[0].y >> 3);

    if (rel_coord_x == 6 && rel_coord_y == 12){
        printf("entering game\n"); 
    }
}

static const void handle_up(game_t *this)
{
    scroll_y(this, J_UP);
    if (this->entities[0].y >> 3 > 0){
        this->entities[0].y -= 1;
        SCY_REG = this->window[0].y;
        if (this->entities[0].direction == J_UP)
            return;
        this->entities[0].sprite_tile[0] = 8  + 4 * this->entities[0].animation;
        this->entities[0].sprite_tile[1] = 10 + 4 * this->entities[0].animation;
    }
}

static const void handle_down(game_t *this)
{
    scroll_y(this, J_DOWN);
    if (this->entities[0].y < (this->map.height - 2) << 3){
        this->entities[0].y += 1;
        SCY_REG = this->window[0].y;
        if (this->entities[0].direction == J_DOWN)
            return;
        this->entities[0].sprite_tile[0] =  4 * this->entities[0].animation;
        this->entities[0].sprite_tile[1] = 2 + 4 * this->entities[0].animation;
    }
}

static const void handle_left(game_t *this)
{
    scroll_x(this, J_LEFT);
    if (this->entities[0].x >> 3 > 0){
        this->entities[0].x -= 1;
        SCX_REG = (uint8_t)this->window[0].x ;
        if (this->entities[0].direction == J_LEFT)
            return;
        this->entities[0].sprite_tile[0] = 16  + 4 * this->entities[0].animation;
        this->entities[0].sprite_tile[1] = 18 + 4 * this->entities[0].animation;
    }
}

static const void handle_right(game_t *this)
{
    scroll_x(this, J_RIGHT);
    if (this->entities[0].x < (this->map.width - 2) << 3 ){
        this->entities[0].x += 1;
        SCX_REG = (uint8_t)this->window[0].x ;
        if (this->entities[0].direction == J_RIGHT)
            return;
        this->entities[0].sprite_tile[1] = 16 + 4 * this->entities[0].animation;
        this->entities[0].sprite_tile[0] = 18 + 4 * this->entities[0].animation;
        set_sprite_prop(this->entities[0].sprite_ids[0], S_FLIPX);
        set_sprite_prop(this->entities[0].sprite_ids[1], S_FLIPX);
    }
}

static const void handle_direction(game_t *this, uint8_t direction)
{
    if (direction && this->entities[0].direction != direction){
        if (this->entities[0].direction == J_RIGHT){
            set_sprite_prop(this->entities[0].sprite_ids[0], 0);
            set_sprite_prop(this->entities[0].sprite_ids[1], 0);
        }
        set_sprite_tile(this->entities[0].sprite_ids[0], this->entities[0].sprite_tile[0]);
        set_sprite_tile(this->entities[0].sprite_ids[1], this->entities[0].sprite_tile[1]);
    }
    this->entities[0].direction = direction;
}

void handleInput(game_t *this)
{
    switch (joypad()) {
        case J_UP:
            handle_up(this);
            break;
        case J_DOWN:
            handle_down(this);
            break;
        case J_LEFT:
            handle_left(this);
            break;
        case J_RIGHT:
            handle_right(this);
            break;
        case J_A | J_START:
            trying_to_enter_game(this);
            break;
        default:
            return;
    }
    handle_direction(this, joypad());
}