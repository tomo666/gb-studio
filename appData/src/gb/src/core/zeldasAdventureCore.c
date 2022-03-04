#include <gb/gb.h>

UINT8 ZELDA_HUD_BLANK = 0xff;
UINT8 ZELDA_HUD_1 = 0xff;
UINT8 ZELDA_HUD_2 = 0xff;
UINT8 ZELDA_HUD_3 = 0xff;
UINT8 ZELDA_HUD_4 = 0xff;
UINT8 ZELDA_HUD_5 = 0xff;
UINT8 ZELDA_HUD_6 = 0xff;
UINT8 ZELDA_HUD_7 = 0xff;
UINT8 ZELDA_HUD_8 = 0xff;
UINT8 ZELDA_HUD_9 = 0xff;
UINT8 ZELDA_HUD_0 = 0xff;
UINT8 ZELDA_HUD_RUPEE = 0xff;
UINT8 ZELDA_HUD_HEART_EMPTY = 0xff;
UINT8 ZELDA_HUD_HEART_HALF = 0xff;
UINT8 ZELDA_HUD_HEART_FULL = 0xff;

BYTE ZELDA_TILES_FOUND = 0;
const UINT8 HEART_START_DRAW = 16; // for 3 hearts the starting point for rendering is tile 16

unsigned char zeldasAdventureHudMap[20] = {0x00, 0x0B, 0x0A, 0x0A, 0x0A, 0x00, 0x0E,
                                           0x0E, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
                                           0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C};

// pointer to GB Studio variables $00 and $01
UINT8 *cachedHealth = (UINT8 *)0xcb1f;
UINT8 *health = (UINT8 *)0xcb21;
// pointer to GB Studio variables $02 and $03
UINT8 *cachedMaxHearts = (UINT8 *)0xcb23;
UINT8 *maxHearts = (UINT8 *)0xcb25;
// pointer to GB Studio variables $04 and $05
UINT8 *cachedRupees = (UINT8 *)0xcb27;
UINT8 *rupees = (UINT8 *)0xcb29;

UINT8 GetNumberTile(UINT8 number)
{
    switch (number)
    {
    case 0:
        return ZELDA_HUD_0;
        break;
    case 1:
        return ZELDA_HUD_1;
        break;
    case 2:
        return ZELDA_HUD_2;
        break;
    case 3:
        return ZELDA_HUD_3;
        break;
    case 4:
        return ZELDA_HUD_4;
        break;
    case 5:
        return ZELDA_HUD_5;
        break;
    case 6:
        return ZELDA_HUD_6;
        break;
    case 7:
        return ZELDA_HUD_7;
        break;
    case 8:
        return ZELDA_HUD_8;
        break;
    case 9:
        return ZELDA_HUD_9;
        break;
    default:
        return ZELDA_HUD_BLANK;
        break;
    }
}

void CalculateRupees(char *hud, UINT8 rupees)
{
    if(rupees < 100) hud[2] = ZELDA_HUD_0;
    if(rupees < 10) hud[3] = ZELDA_HUD_0;
    if(rupees < 1) hud[4] = ZELDA_HUD_0;

    UINT8 count = 1;
    while (rupees > 0)
    {
        UINT8 digit = rupees % 10;
        // set the hundreds
        if (count == 3)
        {
            hud[2] = GetNumberTile(digit);
        }
        // set the tens
        if (count == 2)
        {
            hud[3] = GetNumberTile(digit);
        }
        // set the units
        if (count == 1)
        {
            hud[4] = GetNumberTile(digit);
        }

        rupees /= 10;
        count++;
    }
}

void CalculateHearts(char *hud, UINT8 maxHearts, UINT8 health)
{
    // max hearts is 14
    // max health is 28 (2 half hearts)
    UINT8 healthCounter = health;
    UINT8 startDraw = HEART_START_DRAW - maxHearts + 3;

    for (UINT8 i = 6; i < 19; i++)
    {
        if (i < startDraw)
        {
            hud[i] = ZELDA_HUD_BLANK;
        }
        else if (healthCounter > 2)
        {
            hud[i] = ZELDA_HUD_HEART_FULL;
            healthCounter -= 2;
            continue;
        }
        else if (healthCounter == 2)
        {
            hud[i] = ZELDA_HUD_HEART_FULL;
            healthCounter -= 2;
            continue;
        }
        else if (healthCounter == 1)
        {
            hud[i] = ZELDA_HUD_HEART_HALF;
            healthCounter--;
            continue;
        }
        else
        {
            hud[i] = ZELDA_HUD_HEART_EMPTY;
        }
    }

    // special case for last heart as we nornally leave the last tile empty
    if (maxHearts == 14)
    {
        if (health == 28)
        {
            hud[19] = ZELDA_HUD_HEART_FULL;
        }
        else if (health == 27)
        {
            hud[19] = ZELDA_HUD_HEART_HALF;
        }
        else
        {
            hud[19] = ZELDA_HUD_HEART_EMPTY;
        }
    }
    else
    {
        hud[19] = ZELDA_HUD_BLANK;
    }
}

void CalculateHud(char *hud, UINT8 rupees, UINT8 maxHearts, UINT8 health, BYTE heartsChanged, BYTE maxHeartsChanged, BYTE rupeesChanged)
{
    // set the rupee count
    if(rupeesChanged) {    
        CalculateRupees(hud, rupees);
    }

    // set the hearts
    if(heartsChanged || maxHeartsChanged) { 
        CalculateHearts(hud, maxHearts, health);
    }
}

void DrawZeldaHud(BYTE heartsChanged, BYTE maxHeartsChanged, BYTE rupeesChanged) 
{
  CalculateHud(zeldasAdventureHudMap, *rupees, *maxHearts, *health, heartsChanged, maxHeartsChanged, rupeesChanged);
  set_bkg_tiles(0, 0, 20, 1, zeldasAdventureHudMap);
}

void InvalidateZeldaHudCache() 
{
    ZELDA_HUD_BLANK = 0xff;
    ZELDA_HUD_1 = 0xff;
    ZELDA_HUD_2 = 0xff;
    ZELDA_HUD_3 = 0xff;
    ZELDA_HUD_4 = 0xff;
    ZELDA_HUD_5 = 0xff;
    ZELDA_HUD_6 = 0xff;
    ZELDA_HUD_7 = 0xff;
    ZELDA_HUD_8 = 0xff;
    ZELDA_HUD_9 = 0xff;
    ZELDA_HUD_0 = 0xff;
    ZELDA_HUD_RUPEE = 0xff;
    ZELDA_HUD_HEART_EMPTY = 0xff;
    ZELDA_HUD_HEART_HALF = 0xff;
    ZELDA_HUD_HEART_FULL = 0xff;

    ZELDA_TILES_FOUND = 0;
}

void InitZeldaHud()
{
    InvalidateZeldaHudCache();
    
    if(!ZELDA_TILES_FOUND) {
        BYTE found = 0;

        // for some reason copying the tile numbers from tile RAM is very inconsistent
        // so we need to retry until we've got 'em all!
        while(found == 0) {
            if(ZELDA_HUD_BLANK != 0xff 
                && ZELDA_HUD_1 != 0xff
                && ZELDA_HUD_2 != 0xff
                && ZELDA_HUD_3 != 0xff
                && ZELDA_HUD_4 != 0xff
                && ZELDA_HUD_5 != 0xff
                && ZELDA_HUD_6 != 0xff
                && ZELDA_HUD_7 != 0xff
                && ZELDA_HUD_8 != 0xff
                && ZELDA_HUD_9 != 0xff
                && ZELDA_HUD_0 != 0xff
                && ZELDA_HUD_RUPEE != 0xff
                && ZELDA_HUD_HEART_EMPTY != 0xff
                && ZELDA_HUD_HEART_HALF != 0xff
                && ZELDA_HUD_HEART_FULL != 0xff) {
                found = 1;
            }

            if(ZELDA_HUD_BLANK == 0xff) ZELDA_HUD_BLANK = *(UINT8 *)0x9800;
            if(ZELDA_HUD_1 == 0xff) ZELDA_HUD_1 = *(UINT8 *)0x9801;
            if(ZELDA_HUD_2 == 0xff) ZELDA_HUD_2 = *(UINT8 *)0x9802;
            if(ZELDA_HUD_3 == 0xff) ZELDA_HUD_3 = *(UINT8 *)0x9803;
            if(ZELDA_HUD_4 == 0xff) ZELDA_HUD_4 = *(UINT8 *)0x9804;
            if(ZELDA_HUD_5 == 0xff) ZELDA_HUD_5 = *(UINT8 *)0x9805;
            if(ZELDA_HUD_6 == 0xff) ZELDA_HUD_6 = *(UINT8 *)0x9806;
            if(ZELDA_HUD_7 == 0xff) ZELDA_HUD_7 = *(UINT8 *)0x9807;
            if(ZELDA_HUD_8 == 0xff) ZELDA_HUD_8 = *(UINT8 *)0x9808;
            if(ZELDA_HUD_9 == 0xff) ZELDA_HUD_9 = *(UINT8 *)0x9809;
            if(ZELDA_HUD_0 == 0xff) ZELDA_HUD_0 = *(UINT8 *)0x980a;
            if(ZELDA_HUD_RUPEE == 0xff) ZELDA_HUD_RUPEE = *(UINT8 *)0x980b;
            if(ZELDA_HUD_HEART_EMPTY == 0xff) ZELDA_HUD_HEART_EMPTY = *(UINT8 *)0x980c;
            if(ZELDA_HUD_HEART_HALF == 0xff) ZELDA_HUD_HEART_HALF = *(UINT8 *)0x980d;
            if(ZELDA_HUD_HEART_FULL == 0xff) ZELDA_HUD_HEART_FULL = *(UINT8 *)0x980e;
        }

        for (UINT8 i = 0; i < 20; i++) {
            if (i == 1) {
                zeldasAdventureHudMap[i] = ZELDA_HUD_RUPEE;
            } else {
                zeldasAdventureHudMap[i] = ZELDA_HUD_BLANK;
            }
        }
        
        ZELDA_TILES_FOUND = 1;
    } 

    // initialise the HUD for the first time
    DrawZeldaHud(1, 1, 1);
}

void CheckForHudRedraw()
{
    BYTE heartsChanged = *cachedHealth != *health;
    BYTE maxHeartsChanged = *cachedMaxHearts != *maxHearts;
    BYTE rupeesChanged = *cachedRupees != *rupees;

    if(heartsChanged || maxHeartsChanged || rupeesChanged)
    {
        *cachedHealth = *health;
        *cachedMaxHearts = *maxHearts;
        *cachedRupees = *rupees;
        DrawZeldaHud(heartsChanged, maxHeartsChanged, rupeesChanged);
    }
}
