#include <gb/gb.h>
#include "zeldasSpellData.h"

UINT16 *_spellEquipped = (UINT16 *)0xcb33;

void InitZeldasSpell()
{
    UBYTE _save = _current_bank;
    
    SWITCH_ROM(5);
        LoadSpell(*_spellEquipped);    
    SWITCH_ROM(_save);
}
