#include <gb/gb.h>
#include "zeldasSpellData.h"

void InitZeldasSpell()
{
    UBYTE _save = _current_bank;
    
    SWITCH_ROM(5);
        LoadSpell();    
    SWITCH_ROM(_save);
}
