/**
 * @file save.c
 * @brief Save RAM storage for high scores.
 */
#include <stdlib.h>
#include <stdint.h>
#include <gbdk/platform.h>

uint16_t AT(0xA000) high_scores[3];
