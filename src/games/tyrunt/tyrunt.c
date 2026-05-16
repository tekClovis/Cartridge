/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** tyrunt
*/

#include "game_tyrunt.h"

void update_player(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (data->is_jumping) {
        this->entities[0].y += data->velocity_y;
        
        if (this->actual_frame % 4 == 0) {
            data->velocity_y += 1; 
        }

        if (this->entities[0].y >= 104) {
            this->entities[0].y = 104;
            data->velocity_y = 0;
            data->is_jumping = 0;
        }
    }
    move_sprite(0, this->entities[0].x, this->entities[0].y);
    move_sprite(1, this->entities[0].x + 8, this->entities[0].y);

}

void animate_player(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    uint8_t base_tile = 0;
    uint8_t anim_step = 0;

    if (data->is_jumping) {
        if (data->velocity_y < 0) {
            base_tile = 4;
        } 
        else {
            base_tile = 8;
        }
    } else {
        anim_step = (this->actual_frame / 10) % 3;
        base_tile = anim_step * 4;
    }
    set_sprite_tile(0, base_tile);
    set_sprite_tile(1, base_tile + 2);
}

void update_tree(game_t *this)
{

    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    if (this->entities[1].x >= 250)
        return;

    this->entities[1].x -= data->speed;

    if (this->entities[1].x == 0 || this->entities[1].x > 250) {
        this->entities[1].x = 250;
        data->score += 1;
        
        if (data->score % 5 == 0) {
            data->speed += 1; 
        }
        move_sprite(4, 0, 0);
        move_sprite(5, 0, 0);
        return;
    }

    move_sprite(4, this->entities[1].x, this->entities[1].y);
    move_sprite(5, this->entities[1].x + 8, this->entities[1].y);

    if (this->entities[0].x + 12 > this->entities[1].x && 
        this->entities[0].x < this->entities[1].x + 12 &&
        this->entities[0].y + 16 > this->entities[1].y) {
        
        data->score = 0;
        data->speed = 1;
        this->entities[1].x = 250;
        SCX_REG -= data->speed;
        move_sprite(4, 0, 0);
        move_sprite(5, 0, 0);
        return;
    }
}

void animate_tylton(game_t *this)
{

    uint8_t anim_step = (this->actual_frame / 15) % 2;

    if (anim_step == 0) {
        set_sprite_tile(8, 16);
        set_sprite_tile(9, 18);
    } else {
        set_sprite_tile(8, 20);
        set_sprite_tile(9, 22);
    }
}

void update_tylton(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    uint8_t current_tylton_speed = data->speed;

    if (this->entities[2].x >= 250)
        return;
    
    if (this->actual_frame % 3 == 0) {
        current_tylton_speed += 1;
    }
    this->entities[2].x -= current_tylton_speed;

    if (this->entities[2].x == 0 || this->entities[2].x > 250) {
        this->entities[2].x = 250;
        data->score += 1;

        move_sprite(8, 0, 0);
        move_sprite(9, 0, 0);
        return;
    }

    move_sprite(8, this->entities[2].x, this->entities[2].y);
    move_sprite(9, this->entities[2].x + 8, this->entities[2].y);

    if (this->entities[0].x + 12 > this->entities[2].x &&
        this->entities[0].x < this->entities[2].x + 12 &&
        this->entities[0].y + 16 > this->entities[2].y &&
        this->entities[0].y < this->entities[2].y + 12) {
        
        data->score = 0;
        data->speed = 1;
        this->entities[2].x = 250;
        SCX_REG -= data->speed; 
        move_sprite(8, 0, 0);
        move_sprite(9, 0, 0);
        return;
    }
    animate_tylton(this);
}

void manage_spawner(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;
    uint8_t random_val = DIV_REG; 
    int16_t safe_gap = 80 + (random_val % 40); 

    if (data->spawn_timer > 0) {
        data->spawn_timer--;
        return;
    }
    if (random_val % 2 == 0) {
        if (this->entities[1].x >= 250) {
            this->entities[1].x = 160;
            data->spawn_timer = safe_gap;
        }
    } else {
        if (this->entities[2].x >= 250) {
            this->entities[2].x = 160; 
            data->spawn_timer = safe_gap;
        }
    }
}

void update_obstacle(game_t *this)
{
    manage_spawner(this);
    update_tree(this);
    update_tylton(this); 
}

void update_tyrunt(game_t *this)
{
    tyrunt_plug_in_t *data = (tyrunt_plug_in_t *)this->personal_data;

    handle_input_tyrunt(this);
    update_player(this);
    animate_player(this);
    update_obstacle(this);
    update_score(this);
    SCX_REG += data->speed;
}