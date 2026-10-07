/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** snake
*/

/** @file snake.c @brief Snake game: grid movement, food spawning, scoring and game over. */

#include "game_snake.h"
#include <gb/gb.h>
#include <stdio.h>

static const unsigned char bg_tiles[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char snake_tiles[] = {
    // head tile (tile 8)
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    // body tile (tile 9)
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    // fruit tile (tile 10) - grey square
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00
};

static const uint8_t snake_start_x = 10;
static const uint8_t snake_start_y = 6;

/** @brief Return 1 if tile (x, y) is occupied by one of the first snake_length segments. */
static uint8_t snake_is_on_body(const snake_plug_in_t *data, uint8_t x, uint8_t y)
{
    for (uint8_t i = 0; i < data->snake_length; i++) {
        if (data->body_x[i] == x && data->body_y[i] == y)
            return 1;
    }
    return 0;
}

/** @brief Move the sprites of unused body slots off screen. */
static void snake_hide_unused_sprites(const snake_plug_in_t *data)
{
    for (uint8_t i = data->snake_length; i < SNAKE_MAX_LENGTH; i++) {
        move_sprite(i, 255, 255);
    }
}

/**
 * @brief Place the food on a tile derived from the frame counter, score and length.
 * @note No RNG is used. Tries at most 255 candidates to avoid the body, then keeps the last one.
 */
static void snake_spawn_food(game_t *this, snake_plug_in_t *data)
{
    uint8_t x;
    uint8_t y;
    uint8_t tries = 0;

    do {
        x = (this->actual_frame + data->score + tries * 5) % SNAKE_GRID_WIDTH;
        y = ((this->actual_frame >> 1) + data->snake_length + tries * 7) % SNAKE_GRID_HEIGHT;
        tries += 1;
    } while (snake_is_on_body(data, x, y) && tries < 255);

    data->food_x = x;
    data->food_y = y;
    move_sprite(SNAKE_FOOD_SPRITE_ID, x << 3, y << 3);
    set_sprite_tile(SNAKE_FOOD_SPRITE_ID, 10);
    SHOW_SPRITES;
}

static void snake_draw_score(const snake_plug_in_t *data)
{
    char score_str[32];
    sprintf(score_str, "SCORE %d   ", data->score);
    printToWin(0, 0, score_str);
}

static void snake_draw(const snake_plug_in_t *data)
{
    for (uint8_t i = 0; i < data->snake_length; i++) {
        move_sprite(i, data->body_x[i] << 3, data->body_y[i] << 3);
        set_sprite_tile(i, i == 0 ? 8 : 9);
    }
    snake_hide_unused_sprites(data);
}

const void init_snake(game_t *this)
{
    this->update = &update_snake;
    this->personal_data = &g_game_data.snake;
    snake_plug_in_t *data = (snake_plug_in_t *)this->personal_data;

    data->score = 0;
    this->score = 0;
    data->speed = 1;
    data->direction = SNAKE_RIGHT;
    data->snake_length = 3;
    data->move_delay = 0;
    data->body_x[0] = snake_start_x;
    data->body_y[0] = snake_start_y;
    data->body_x[1] = snake_start_x - 1;
    data->body_y[1] = snake_start_y;
    data->body_x[2] = snake_start_x - 2;
    data->body_y[2] = snake_start_y;

    SCX_REG = 0;
    SCY_REG = 0;

    SPRITES_8x8;
    set_sprite_data(8, 3, snake_tiles);
    set_bkg_data(0, 2, bg_tiles);

    for (uint8_t y = 0; y < SNAKE_GRID_HEIGHT; y++) {
        uint8_t row[SNAKE_GRID_WIDTH];
        for (uint8_t x = 0; x < SNAKE_GRID_WIDTH; x++)
            row[x] = 0;
        set_bkg_tiles(0, y, SNAKE_GRID_WIDTH, 1, row);
    }

    move_sprite(SNAKE_FOOD_SPRITE_ID, 255, 255);
    set_sprite_tile(SNAKE_FOOD_SPRITE_ID, 10);

    reset_win();
    snake_spawn_food(this, data);
    snake_draw(data);
    snake_draw_score(data);

    SHOW_WIN;
    move_win(7, 120);
}

/** @brief Hide the score window and return to the menu. */
static void snake_game_over(game_t *this)
{
    HIDE_WIN;
    init_game(this, MENU);
}

const void update_snake(game_t *this)
{
    snake_plug_in_t *data = (snake_plug_in_t *)this->personal_data;

    handle_input_snake(this);
    data->move_delay += 1;
    if (data->move_delay < (12 - data->speed))
        return;
    data->move_delay = 0;

    uint8_t next_x = data->body_x[0];
    uint8_t next_y = data->body_y[0];

    switch (data->direction) {
        case SNAKE_UP:
            next_y -= 1;
            break;
        case SNAKE_RIGHT:
            next_x += 1;
            break;
        case SNAKE_DOWN:
            next_y += 1;
            break;
        case SNAKE_LEFT:
            next_x -= 1;
            break;
    }

    /* next_* are unsigned: moving past 0 wraps to 255, caught by the bounds check below. */
    uint8_t collides_with_body = 0;
    uint8_t tail_index = data->snake_length - 1;

    if (next_x >= SNAKE_GRID_WIDTH || next_y >= SNAKE_GRID_HEIGHT) {
        set_high_score(SNAKE, data->score);
        snake_game_over(this);
        return;
    }

    /* Eating: the tail does not move, so the whole body counts as an obstacle. Otherwise
     * the tail tile is about to be vacated and is excluded. */
    if (next_x == data->food_x && next_y == data->food_y) {
        collides_with_body = snake_is_on_body(data, next_x, next_y);
    } else {
        for (uint8_t i = 0; i < tail_index; i++) {
            if (data->body_x[i] == next_x && data->body_y[i] == next_y) {
                collides_with_body = 1;
                break;
            }
        }
    }

    if (collides_with_body) {
        set_high_score(SNAKE, data->score);
        snake_game_over(this);
        return;
    }

    for (int i = data->snake_length; i > 0; i--) {
        data->body_x[i] = data->body_x[i - 1];
        data->body_y[i] = data->body_y[i - 1];
    }
    data->body_x[0] = next_x;
    data->body_y[0] = next_y;

    if (next_x == data->food_x && next_y == data->food_y) {
        if (data->snake_length < SNAKE_MAX_LENGTH)
            data->snake_length += 1;
        data->score += 1;
        this->score = data->score;
        if (data->speed < 10 && (data->score % 4) == 0)
            data->speed += 1;
        snake_spawn_food(this, data);
        snake_draw_score(data);
    }

    snake_draw(data);
}

/** @brief Read the joypad: SELECT quits, d-pad turns the snake (180 degree turns are ignored). */
static const void handle_input_snake(game_t *this)
{
    uint8_t input = joypad();
    snake_plug_in_t *data = (snake_plug_in_t *)this->personal_data;

    if (input & J_SELECT) {
        snake_game_over(this);
        return;
    }

    if ((input & J_UP) && data->direction != SNAKE_DOWN)
        data->direction = SNAKE_UP;
    else if ((input & J_DOWN) && data->direction != SNAKE_UP)
        data->direction = SNAKE_DOWN;
    else if ((input & J_LEFT) && data->direction != SNAKE_RIGHT)
        data->direction = SNAKE_LEFT;
    else if ((input & J_RIGHT) && data->direction != SNAKE_LEFT)
        data->direction = SNAKE_RIGHT;
}
