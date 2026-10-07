/**
 * @file save.h
 * @brief Save RAM layout.
 */

#pragma once

#include <gbdk/platform.h>

/**
 * @brief Three high scores stored in cartridge RAM at 0xA000.
 * @note Enable RAM (SWITCH_RAM/ENABLE_RAM) before access; values above 999 are treated as invalid.
 */
extern uint16_t high_scores[3];
