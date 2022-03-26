#include <gb/gb.h>
#include "zeldasTileCore.h"
#include "zeldasTileData.h"

UBYTE shouldAnimateTile = 0;
void InitTileAnimation()
{
    UBYTE _save = _current_bank;
    
    SWITCH_ROM(5);
        shouldAnimateTile = FindAnimationTile();
    SWITCH_ROM(_save);
}

void UpdateTileAnimation()
{
    if (shouldAnimateTile)
    {
        UBYTE _save = _current_bank;
        SWITCH_ROM(5);
            AnimateTile();
        SWITCH_ROM(_save);
    }
}
