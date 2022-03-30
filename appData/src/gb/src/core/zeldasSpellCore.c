#include <gb/gb.h>
#include "zeldasSpellData.h"

#ifdef CGB
    UINT16 *_spellEquipped = (UINT16 *)0xcb34;
#else
    UINT16 *_spellEquipped = (UINT16 *)0xcb33;
#endif

void InitZeldasSpell()
{
    UBYTE _save = _current_bank;
    
    SWITCH_ROM(5);
        LoadSpell(*_spellEquipped);    
    SWITCH_ROM(_save);
}
