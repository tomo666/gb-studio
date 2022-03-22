#include <gb/gb.h>
#include "zeldasTileCore.h"
#include "zeldasTileData.h"

ZELDA_TILE_ANIMATION animateTile = ZELDA_TILE_ANIMATION_NONE;

void InitAnimatedTile()
{
    UBYTE _save = _current_bank;
    
    SWITCH_ROM(6);
        animateTile = FindAnimationTile();
    SWITCH_ROM(_save);
}

void AnimateTile()
{
    UBYTE _save = _current_bank;
    switch (animateTile) {
        case ZELDA_TILE_ANIMATION_SEA:
            SWITCH_ROM(6);
                AnimateSeaWater();
            SWITCH_ROM(_save);
            break;
    }
}
