#ifndef ZELDAS_TILE_CORE_H
#define ZELDAS_TILE_CORE_H

#include <gb/gb.h>

/**
 * Check if tile 15 in the HUD has been marked for animation
 * either sea water, lake water, lava, lamp or a torch
 */
void InitTileAnimation();

void UpdateTileAnimation();

#endif
