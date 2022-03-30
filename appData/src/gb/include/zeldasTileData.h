#ifndef ZELDAS_TILE_DATA_H
#define ZELDAS_TILE_DATA_H

#include <gb/gb.h>

typedef enum
{
    ZELDA_TILE_ANIMATION_NONE = 0,
    ZELDA_TILE_ANIMATION_SEA,
    ZELDA_TILE_ANIMATION_LAKE,
    ZELDA_TILE_ANIMATION_LAVA,
    ZELDA_TILE_ANIMATION_LAMP,
    ZELDA_TILE_ANIMATION_TORCH,
    ZELDA_TILE_ANIMATION_TORCH_AND_LAMP,
} ZELDA_TILE_ANIMATION;

/**
 * If tile 15 in the HUD has been marked for animation
 * return either sea water, lake water, lava, lamp or torch
 */
UBYTE FindAnimationTile() BANKED;

/**
 * Animates the identified tile(s)
 */
void AnimateTile() BANKED;

#endif
