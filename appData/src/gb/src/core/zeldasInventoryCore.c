#include <gb/gb.h>
#include "bankdata.h"
#include "zeldasInventoryCore.h"
#include "zeldasInventoryData.h"

#ifdef CGB
    // pointer to GB Studio variables $06 - $12
    UINT16 *_inventoryInteraction = (UINT16 *)0xcb2c;
    UINT16 *_inventoryFlags1 = (UINT16 *)0xcb2e;
    UINT16 *_inventoryFlags2 = (UINT16 *)0xcb30;
    UINT16 *_inventoryFlags3 = (UINT16 *)0xcb32;
    UINT16 *_equipped = (UINT16 *)0xcb34;
    UINT16 *_overworldFlags = (UINT16 *)0xcb36;
#else
    // pointer to GB Studio variables $06 - $12
    UINT16 *_inventoryInteraction = (UINT16 *)0xcb2b;
    UINT16 *_inventoryFlags1 = (UINT16 *)0xcb2d;
    UINT16 *_inventoryFlags2 = (UINT16 *)0xcb2f;
    UINT16 *_inventoryFlags3 = (UINT16 *)0xcb31;
    UINT16 *_equipped = (UINT16 *)0xcb33;
    UINT16 *_overworldFlags = (UINT16 *)0xcb35;
#endif

const UINT8 maxItemsOnScreen = 6;
const UINT8 totalWeaponsAvailable = 19;
const UINT8 totalTreasuresAvailable = 25;

UINT8 slot = 0;
unsigned char firstWeaponTile = 0x00;
unsigned char firstTreasureTile = 0x4C;

UINT8 totalWeaponsFound = 0;
UINT8 weaponScrollOffset = 0;
ZELDA_WEAPONS weapons[19];

UINT8 totalTreasuresFound = 0;
UINT8 treasureScrollOffset = 0;
ZELDA_TREASURES treasures[25];

// on screen view of weapons
unsigned char weaponPanel[] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2,
                               0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
// on screen view of treasures
unsigned char treasurePanel[] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2,
                                 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2};

unsigned char equippedPanel[] = {0xC2, 0xC2, 
                                 0xC2, 0xC2};

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
    totalTreasuresFound = 0;
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

void DrawWeaponsTreasures()
{
    // add weapons to on screen weaponPanel
    slot = 0;
    for (UINT8 i = weaponScrollOffset; i < maxItemsOnScreen + weaponScrollOffset; i++)
    {
        for (UINT8 j = 1; j <= totalWeaponsAvailable; j++)
        {
            if (weapons[i] == j) 
            {
                weaponPanel[slot] = firstWeaponTile + ((j-1) * 4);
                weaponPanel[slot + 1] = firstWeaponTile + ((j-1) * 4) + 1;
                weaponPanel[slot + 12] = firstWeaponTile + ((j-1) * 4) + 2;
                weaponPanel[slot + 13] = firstWeaponTile + ((j-1) * 4) + 3;
                slot += 2;
                if (*_equipped == j) 
                {
                    equippedPanel[0] = firstWeaponTile + ((j-1) * 4);
                    equippedPanel[1] = firstWeaponTile + ((j-1) * 4) + 1;
                    equippedPanel[2] = firstWeaponTile + ((j-1) * 4) + 2;
                    equippedPanel[3] = firstWeaponTile + ((j-1) * 4) + 3;
                }
                continue;
            }
        }
    }

    slot = 0;
    for (UINT8 i = treasureScrollOffset; i < maxItemsOnScreen + treasureScrollOffset; i++)
    {
        for (UINT8 j = 1; j <= totalTreasuresAvailable; j++)
        {
            if (treasures[i] == j && j < ZELDA_TREASURE_HARP) 
            {
                treasurePanel[slot] = firstTreasureTile + ((j-1) * 4);
                treasurePanel[slot + 1] = firstTreasureTile + ((j-1) * 4) + 1;
                treasurePanel[slot + 12] = firstTreasureTile + ((j-1) * 4) + 2;
                treasurePanel[slot + 13] = firstTreasureTile + ((j-1) * 4) + 3;
                slot += 2;
                if (*_equipped == j + totalWeaponsAvailable) 
                {
                    equippedPanel[0] = firstTreasureTile + ((j-1) * 4);
                    equippedPanel[1] = firstTreasureTile + ((j-1) * 4) + 1;
                    equippedPanel[2] = firstTreasureTile + ((j-1) * 4) + 2;
                    equippedPanel[3] = firstTreasureTile + ((j-1) * 4) + 3;
                }
                continue;
            }
            // strange 1 tile gap in VRAM next to harp
            if (treasures[i] == j && j > ZELDA_TREASURE_KNIFE) 
            {
                treasurePanel[slot] = firstTreasureTile + ((j-1) * 4) + 1;
                treasurePanel[slot + 1] = firstTreasureTile + ((j-1) * 4) + 2;
                treasurePanel[slot + 12] = firstTreasureTile + ((j-1) * 4) + 3;
                treasurePanel[slot + 13] = firstTreasureTile + ((j-1) * 4) + 4;
                slot += 2;
                if (*_equipped == j + totalWeaponsAvailable) 
                {
                    equippedPanel[0] = firstTreasureTile + ((j-1) * 4) + 1;
                    equippedPanel[1] = firstTreasureTile + ((j-1) * 4) + 2;
                    equippedPanel[2] = firstTreasureTile + ((j-1) * 4) + 3;
                    equippedPanel[3] = firstTreasureTile + ((j-1) * 4) + 4;
                }
                continue;
            }
        }
    }

    set_bkg_tiles(3, 15, 12, 2, weaponPanel);
    set_bkg_tiles(3, 11, 12, 2, treasurePanel);
    set_bkg_tiles(17, 13, 2, 2, equippedPanel);
}

void ScrollWeaponsRight()
{
    if (weaponScrollOffset < totalWeaponsFound - maxItemsOnScreen)
    {
        weaponScrollOffset++;
        DrawWeaponsTreasures();
    }
}

void ScrollWeaponsLeft()
{
    if (weaponScrollOffset > 0)
    {
        weaponScrollOffset--;
        DrawWeaponsTreasures();
    }
}

void ScrollTreasuresRight()
{
    if (treasureScrollOffset < totalTreasuresFound - maxItemsOnScreen)
    {
        treasureScrollOffset++;
        DrawWeaponsTreasures();
    }
}

void ScrollTreasuresLeft()
{
    if (treasureScrollOffset > 0)
    {
        treasureScrollOffset--;
        DrawWeaponsTreasures();
    }
}

void SelectWeapon(UINT8 weaponSlot) 
{
    *_equipped = weapons[weaponSlot + weaponScrollOffset];
    DrawWeaponsTreasures();
}

void SelectTreasure(UINT8 treasureSlot) 
{
    *_equipped = treasures[treasureSlot + treasureScrollOffset] + totalWeaponsAvailable;
    DrawWeaponsTreasures();
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
    UINT8 shrinesComplete = CalcCelestialSigns();
    UBYTE keys = GetBit(*_inventoryFlags3, 12); // Flag 13 in GB Studio

    SWITCH_ROM(5);
        // draw the background tiles
        DrawStaticInventory();
        // fill the segments of the celestial sign indicator
        DrawCelestialSigns(shrinesComplete);
        // write 0-1 depending on keys found
        DrawKeyIndicator(keys);
    SWITCH_ROM(_save);

    // initialise the weapon tiles
    IdentifyWeaponsTreasuresFound();
    DrawWeaponsTreasures();
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
