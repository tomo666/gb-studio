#include <gb/gb.h>
#include "bankdata.h"
#include "zeldasInventoryCore.h"
#include "zeldasInventoryData.h"
#define ZELDAS_INVENTORY_BANK 5

// pointer to GB Studio variables $06 - $12
UINT16 *_inventoryInteraction = (UINT16 *)0xcb2b;
UINT16 *_inventoryFlags1 = (UINT16 *)0xcb2d;
UINT16 *_inventoryFlags2 = (UINT16 *)0xcb2f;
UINT16 *_inventoryFlags3 = (UINT16 *)0xcb31;
UINT16 *_equipped = (UINT16 *)0xcb33;
UINT16 *_overworldFlags = (UINT16 *)0xcb35;

ZELDA_WEAPONS weapons[19];
ZELDA_TREASURES treasures[25];
UINT8 totalWeaponsFound = 0;
UINT8 totalTreasuresFound = 0;

UBYTE GetBit(UINT16 byte, UINT8 bit)
{
    return (byte & (1 << bit)) != 0;
}

// weapons 1-19 = inventory1 (0-15) + inventory2 (0-2)
// treasures 1-25 = inventory2 (2-15), inventory3 (0-11)
void IdentifyWeaponsTreasuresFound()
{
    // populate weapons array by interrogate GB Studio
    totalWeaponsFound = 0;
    for (UINT8 i = 0; i < 16; i++)
    {
        // populate weapons
        if (GetBit(*_inventoryFlags1, i)) 
        {
            // when i = 0, i+1 = 1 (ZELDA_WEAPON_WAND)
            weapons[totalWeaponsFound] = i+1;
            totalWeaponsFound++;
        }
    }

    for (UINT8 i = 0; i < 16; i++)
    {
        // populate weapons
        if (i < 3 && GetBit(*_inventoryFlags2, i)) 
        {
            // when i = 0, i+17 = 17 (ZELDA_WEAPON_SHORTAXE)
            weapons[totalWeaponsFound] = i+17;
            totalWeaponsFound++;
        }

        // populate treasures
        if (i > 2 && GetBit(*_inventoryFlags2, i)) 
        {
            // when i = 3, i-2 = 1 (ZELDA_TREASURE_LADDER)
            treasures[totalTreasuresFound] = i-2;
            totalTreasuresFound++;
        }
    }

    for (UINT8 i = 0; i < 12; i++)
    {
        if (GetBit(*_inventoryFlags3, i)) 
        {
            // when i = 0, i+14 = 14 (ZELDA_TREASURE_HARP)
            treasures[totalTreasuresFound] = i+14;
            totalTreasuresFound++;
        }
    }
}


void ScrollWeaponsRight()
{
    UBYTE _save = _current_bank;
    SWITCH_ROM(ZELDAS_INVENTORY_BANK);
        ConditionalScrollWeaponsRight(weapons, treasures, *_equipped, totalWeaponsFound);
    SWITCH_ROM(_save);
}

void ScrollWeaponsLeft()
{
    UBYTE _save = _current_bank;
    SWITCH_ROM(ZELDAS_INVENTORY_BANK);
        ConditionalScrollWeaponsLeft(weapons, treasures, *_equipped);
    SWITCH_ROM(_save);
}

void ScrollTreasuresRight()
{
    UBYTE _save = _current_bank;
    SWITCH_ROM(ZELDAS_INVENTORY_BANK);
        ConditionalScrollTreasuresRight(weapons, treasures, *_equipped, totalTreasuresFound);
    SWITCH_ROM(_save);
}

void ScrollTreasuresLeft()
{
    UBYTE _save = _current_bank;
    SWITCH_ROM(ZELDAS_INVENTORY_BANK);
        ConditionalScrollTreasuresLeft(weapons, treasures, *_equipped);
    SWITCH_ROM(_save);
}

void SelectWeapon(UINT8 weaponSlot) 
{
    UINT8 weaponScrollOffset = 0;
    UBYTE _save = _current_bank;
    SWITCH_ROM(ZELDAS_INVENTORY_BANK);
        weaponScrollOffset = GetWeaponScrollOffset();
    SWITCH_ROM(_save);
    
    *_equipped = weapons[weaponSlot + weaponScrollOffset];
    
    SWITCH_ROM(ZELDAS_INVENTORY_BANK);
        DrawWeaponsTreasures(weapons, treasures, *_equipped);
    SWITCH_ROM(_save);
}

void SelectTreasure(UINT8 treasureSlot) 
{
    UINT8 treasureScrollOffset = 0;
    UBYTE _save = _current_bank;
    SWITCH_ROM(ZELDAS_INVENTORY_BANK);
        treasureScrollOffset = GetTreasureScrollOffset();
    SWITCH_ROM(_save);
    
    *_equipped = treasures[treasureSlot + treasureScrollOffset] + 19; //totalWeaponsAvailable;
    
    SWITCH_ROM(ZELDAS_INVENTORY_BANK);
        DrawWeaponsTreasures(weapons, treasures, *_equipped);
    SWITCH_ROM(_save);
}

UINT8 CalcCelestialSigns()
{
    if (GetBit(*_overworldFlags, 6)) return 7;
    if (GetBit(*_overworldFlags, 5)) return 6;
    if (GetBit(*_overworldFlags, 4)) return 5;
    if (GetBit(*_overworldFlags, 3)) return 4;
    if (GetBit(*_overworldFlags, 2)) return 3;
    if (GetBit(*_overworldFlags, 1)) return 2;
    if (GetBit(*_overworldFlags, 0)) return 1;

    return 0;
}

void InitZeldaInventory() 
{
    UBYTE _save = _current_bank;
    UINT8 shinesComplete = CalcCelestialSigns();
    UBYTE keys = GetBit(*_inventoryFlags3, 11); // Flag 12 in GB Studio
    
    // initialise the weapon tiles
    IdentifyWeaponsTreasuresFound();

    SWITCH_ROM(ZELDAS_INVENTORY_BANK);
        // draw the background tiles
        DrawStaticInventory();
        // fill the segments of the celestial sign indicator
        DrawCelestialSigns(shinesComplete);
        // write 0-1 depending on keys found
        DrawKeyIndicator(keys);
        DrawWeaponsTreasures(weapons, treasures, *_equipped);
    SWITCH_ROM(_save);
}

void CheckForInventoryInteraction() 
{
    if (*_inventoryInteraction != 0) 
    {
        // weapon interaction
        if (*_inventoryInteraction == 1) 
        {
            *_inventoryInteraction = 0;
            ScrollWeaponsLeft();
        }
        if (*_inventoryInteraction == 2) 
        {
            *_inventoryInteraction = 0;
            ScrollWeaponsRight();
        }
        if (*_inventoryInteraction >= 3 && *_inventoryInteraction <= 8) 
        {
            SelectWeapon(*_inventoryInteraction - 3);
            *_inventoryInteraction = 0;
        }

        // treasure interaction
        if (*_inventoryInteraction == 9) 
        {
            *_inventoryInteraction = 0;
            ScrollTreasuresLeft();
        }
        if (*_inventoryInteraction == 10) 
        {
            *_inventoryInteraction = 0;
            ScrollTreasuresRight();
        }
        if (*_inventoryInteraction >= 11 && *_inventoryInteraction <= 16) 
        {
            SelectTreasure(*_inventoryInteraction - 11);
            *_inventoryInteraction = 0;
        }
    }    
}
