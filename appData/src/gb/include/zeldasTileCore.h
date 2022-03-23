#ifndef ZELDAS_TILE_CORE_H
#define ZELDAS_TILE_CORE_H

#include <gb/gb.h>

typedef enum
{
    ZELDA_TILE_ANIMATION_NONE = 0,
    ZELDA_TILE_ANIMATION_SEA,
    ZELDA_TILE_ANIMATION_LAKE,
    ZELDA_TILE_ANIMATION_LAVA,
    ZELDA_TILE_ANIMATION_LAMP,
    ZELDA_TILE_ANIMATION_TORCH,
} ZELDA_TILE_ANIMATION;

/**
 * Check if tile 15 in the HUD has been marked for animation
 * either sea water, lake water, lava, lamp or a torch
 */
void InitAnimatedTile();

void AnimateTile();

#endif
