#include <gb/gb.h>
#include "zeldasTileCore.h"
#include "zeldasTileData.h"

ZELDA_TILE_ANIMATION animateTile = ZELDA_TILE_ANIMATION_NONE;

void InitAnimatedTile()
{
    UBYTE _save = _current_bank;
    
    SWITCH_ROM(5);
        animateTile = FindAnimationTile();
    SWITCH_ROM(_save);
}

void AnimateTile()
{
    UBYTE _save = _current_bank;
    switch (animateTile) {
        case ZELDA_TILE_ANIMATION_SEA:
            SWITCH_ROM(5);
                AnimateSea();
            SWITCH_ROM(_save);
            break;
        case ZELDA_TILE_ANIMATION_LAKE:
            SWITCH_ROM(5);
                AnimateLake();
            SWITCH_ROM(_save);
            break;
        case ZELDA_TILE_ANIMATION_LAVA:
            SWITCH_ROM(5);
                AnimateLava();
            SWITCH_ROM(_save);
            break;
    }
}
