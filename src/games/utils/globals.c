#include "game.h"
#include "entities.h"

// Shared RAM buffers used as active plugin storage.
// Zero-initialized by default (WRAM).
active_game_data_t g_game_data;
active_ent_data_t g_ent_data;
