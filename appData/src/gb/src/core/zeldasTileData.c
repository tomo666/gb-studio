#pragma bank 5

#include <gb/gb.h>
#include "bankdata.h"
#include "zeldasTileData.h"
#include "game_time.h"

const unsigned char blank[] = {
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};
const unsigned char river0[] = {
0xFF,0x00,0xF3,0x00,0xE0,0x00,0x0E,0x00,0xFF,0x00,0x7C,0x00,0x31,0x00,0x87,0x00,
};
const unsigned char river1[] = {
0xFF,0x00,0xFC,0x00,0x38,0x00,0x83,0x00,0xFF,0x00,0xF1,0x00,0xC4,0x00,0x1E,0x00,
};
const unsigned char river2[] = {
0xFF,0x00,0x3F,0x00,0x0E,0x00,0xE0,0x00,0xFF,0x00,0xC7,0x00,0x13,0x00,0x78,0x00,
};
const unsigned char river3[] = {
0xFF,0x00,0xCF,0x00,0x83,0x00,0x38,0x00,0xFF,0x00,0x1F,0x00,0x4C,0x00,0xE1,0x00,
};
const unsigned char lake0[] = {
0xFF,0x00,0x3F,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFC,0x00,0xFF,0x00,0xFF,0x00,
};
const unsigned char lake1[] = {
0xFF,0x00,0xCF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xF3,0x00,0xFF,0x00,0xFF,0x00,
};
const unsigned char lake2[] = {
0xFF,0x00,0xF3,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xCF,0x00,0xFF,0x00,0xFF,0x00,
};
const unsigned char lake3[] = {
0xFF,0x00,0xFC,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0x3F,0x00,0xFF,0x00,0xFF,0x00,
};
const unsigned char lava0[] = {
0x00,0xFF,0x00,0xFF,0x1C,0xFF,0x32,0xEF,0x22,0xFF,0x14,0xFF,0x00,0xFF,0x00,0xFF,
};
const unsigned char lava1[] = {
0x00,0xFF,0x3C,0xFF,0x42,0xFF,0x99,0xC7,0xB1,0xCF,0x81,0xFF,0x42,0xFF,0x00,0xFF,
};
const unsigned char lava2[] = {
0x00,0xFF,0x42,0xBD,0x28,0xF7,0x00,0xFF,0x24,0xFF,0x5A,0xBD,0x00,0xFF,0x00,0xFF,
};
const unsigned char lava3[] = {
0x00,0xFF,0x00,0xFF,0x00,0xFF,0x10,0xEF,0x18,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,
};
const unsigned char lamp0a[] = {
0x3F,0x3F,0x42,0x42,0x84,0x84,0x8A,0x88,0x93,0x90,0x96,0x91,0x96,0x91,0x8B,0x89,
};
const unsigned char lamp0b[] = {
0xFC,0xFC,0xC2,0xC2,0xB1,0xA1,0x99,0x91,0x59,0x11,0xD9,0x11,0x59,0x91,0xB1,0xA1,
};
const unsigned char lamp1a[] = {
0x3F,0x3F,0x43,0x43,0x8D,0x85,0x98,0x88,0x99,0x88,0x9B,0x88,0x9A,0x89,0x8D,0x85,
};
const unsigned char lamp1b[] = {
0x7C,0x7C,0x22,0x22,0x11,0x11,0x51,0x11,0xC9,0x09,0x69,0x89,0x69,0x89,0xD1,0x91,
};
const unsigned char lamp2a[] = {
0x3F,0x3F,0x40,0x40,0x9F,0x81,0xBE,0x82,0xBC,0x84,0xB8,0x88,0xB9,0x88,0x9D,0x85,
};
const unsigned char lamp2b[] = {
0xFC,0xFC,0x02,0x02,0xF9,0xC1,0xBD,0xA1,0x1D,0x11,0x9D,0x11,0x1D,0x91,0xB9,0xA1,
};
const unsigned char lamp3a[] = {
0x3F,0x3F,0x41,0x41,0x9F,0x83,0xBD,0x85,0xB8,0x88,0xB9,0x88,0xB8,0x89,0x9D,0x85,
};
const unsigned char lamp3b[] = {
0xFC,0xFC,0x82,0x82,0x79,0x41,0x3D,0x21,0x9D,0x11,0xDD,0x11,0x5D,0x91,0xB9,0xA1,
};
const unsigned char torch0[] = {
0x81,0x7E,0x00,0xFF,0x00,0xFF,0x18,0xE7,0x18,0xE7,0x00,0xFF,0x00,0xFF,0x81,0x7E,
};
const unsigned char torch1[] = {
0x81,0x7E,0x00,0xFF,0x18,0xE7,0x24,0xC3,0x24,0xC3,0x18,0xE7,0x00,0xFF,0x81,0x7E,
};
const unsigned char torch2[] = {
0x81,0x7E,0x3C,0xC3,0x66,0x81,0x42,0x81,0x42,0x81,0x66,0x81,0x3C,0xC3,0x81,0x7E,
};
const unsigned char torch3[] = {
0xBD,0x42,0x66,0x81,0xC3,0x00,0x81,0x00,0x81,0x00,0xC3,0x00,0x66,0x81,0xBD,0x42,
};
const unsigned char sea0a[] = {
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xF8,0x00,0xC0,0x00,0x09,0x00,0x3F,0x00,
};
const unsigned char sea0b[] = {
0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0x1F,0x00,0x07,0x00,0x80,0x00,0xD8,0x00,
};
const unsigned char sea1a[] = {
0xFF,0x00,0xFF,0x00,0xFE,0x00,0xE0,0x00,0x01,0x00,0x33,0x00,0xFF,0x00,0xFF,0x00,
};
const unsigned char sea1b[] = {
0xFF,0x00,0xFF,0x00,0x3F,0x00,0x0F,0x00,0x80,0x00,0xE0,0x00,0xFF,0x00,0xFF,0x00,
};
const unsigned char sea2a[] = {
0xFC,0x00,0xF0,0x00,0x01,0x00,0x03,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
};
const unsigned char sea2b[] = {
0x1F,0x00,0x00,0x00,0xC0,0x00,0xE7,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
};
const unsigned char sea3a[] = {
0x03,0x00,0xE7,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xF8,0x00,0xC0,0x00,
};
const unsigned char sea3b[] = {
0x80,0x00,0xF3,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0x3F,0x00,0x07,0x00,
};
const unsigned char wave0a[] = {
0x03,0x00,0x1C,0x03,0xE0,0x1F,0x02,0xFC,0x08,0xF0,0x01,0x00,0x11,0x00,0xCE,0x00,
};
const unsigned char wave0b[] = {
0xC0,0x00,0x38,0xC0,0x07,0xF8,0x40,0x3F,0x08,0x07,0x80,0x00,0xA2,0x00,0x78,0x00,
};
const unsigned char wave1a[] = {
0x03,0x00,0x1C,0x00,0xE0,0x00,0x09,0x00,0x01,0x00,0xE6,0x00,0xFF,0x00,0xFF,0x00,
};
const unsigned char wave1b[] = {
0xC0,0x00,0x38,0x00,0x0F,0x00,0xA0,0x00,0xCC,0x00,0x35,0x00,0xFB,0x00,0xFF,0x00,
};
const unsigned char wave2a[] = {
0x03,0x00,0x1C,0x03,0xE2,0x1C,0x08,0xF0,0x03,0x00,0x20,0x00,0x8F,0x00,0xFF,0x00,
};
const unsigned char wave2b[] = {
0xC0,0x00,0x38,0xC0,0x47,0x38,0x10,0x0F,0x10,0x00,0x40,0x00,0xFC,0x00,0xFF,0x00,
};
const unsigned char wave3a[] = {
0x03,0x00,0x1C,0x03,0xE0,0x1F,0x00,0xFF,0x00,0xFF,0x04,0xF8,0x10,0xE0,0x05,0x00,
};
const unsigned char wave3b[] = {
0xC0,0x00,0x38,0xC0,0x07,0xF8,0x00,0xFF,0x00,0xFF,0x20,0x1F,0x08,0x07,0x40,0x00,
};

UINT8 frame = 0;
// The HUD is a curated set of reference tiles
// the tile in position 15 is the animation indicator tile
UINT8 *_zeldaAnimationTile0 = (UINT8 *)0x980f;
UINT8 *_zeldaAnimationTile1 = (UINT8 *)0x9810;
UINT8 *_zeldaAnimationTile2 = (UINT8 *)0x9811;
UINT8 *_zeldaAnimationTile3 = (UINT8 *)0x9812;

UINT8 staticRefTile0 = 0xff;
UINT8 staticRefTile1 = 0xff;
UINT8 staticRefTile2 = 0xff;
UINT8 staticRefTile3 = 0xff;

ZELDA_TILE_ANIMATION animationTile = ZELDA_TILE_ANIMATION_NONE;

void initTileReference()
{
    // clear cache
    staticRefTile0 = 0xff;
    staticRefTile1 = 0xff;
    staticRefTile2 = 0xff;
    staticRefTile3 = 0xff;

    // a simple allocation seems to be incosistent due to a de-bounce
    // so keep trying until we've got a stable reference to the animation tiles
    while (staticRefTile0 == 0xff || staticRefTile1 == 0xff || staticRefTile2 == 0xff || staticRefTile3 == 0xff)
    {
        if (staticRefTile0 == 0xff) staticRefTile0 = *_zeldaAnimationTile0;
        if (staticRefTile1 == 0xff) staticRefTile1 = *_zeldaAnimationTile1;
        if (staticRefTile2 == 0xff) staticRefTile2 = *_zeldaAnimationTile2;
        if (staticRefTile3 == 0xff) staticRefTile3 = *_zeldaAnimationTile3;
    }
}

UBYTE CompareAnimationTile(unsigned char tile[]) BANKED 
{
    UINT8 *bkgMemory[128] = {
        (UINT8 *)0x9000, (UINT8 *)0x9010, (UINT8 *)0x9020, (UINT8 *)0x9030, (UINT8 *)0x9040, (UINT8 *)0x9050, (UINT8 *)0x9060, (UINT8 *)0x9070, (UINT8 *)0x9080, (UINT8 *)0x9090, (UINT8 *)0x90A0, (UINT8 *)0x90B0, (UINT8 *)0x90C0, (UINT8 *)0x90D0, (UINT8 *)0x90E0, (UINT8 *)0x90F0,
        (UINT8 *)0x9100, (UINT8 *)0x9110, (UINT8 *)0x9120, (UINT8 *)0x9130, (UINT8 *)0x9140, (UINT8 *)0x9150, (UINT8 *)0x9160, (UINT8 *)0x9170, (UINT8 *)0x9180, (UINT8 *)0x9190, (UINT8 *)0x91A0, (UINT8 *)0x91B0, (UINT8 *)0x91C0, (UINT8 *)0x91D0, (UINT8 *)0x91E0, (UINT8 *)0x91F0,
        (UINT8 *)0x9200, (UINT8 *)0x9210, (UINT8 *)0x9220, (UINT8 *)0x9230, (UINT8 *)0x9240, (UINT8 *)0x9250, (UINT8 *)0x9260, (UINT8 *)0x9270, (UINT8 *)0x9280, (UINT8 *)0x9290, (UINT8 *)0x92A0, (UINT8 *)0x92B0, (UINT8 *)0x92C0, (UINT8 *)0x92D0, (UINT8 *)0x92E0, (UINT8 *)0x92F0,
        (UINT8 *)0x9300, (UINT8 *)0x9310, (UINT8 *)0x9320, (UINT8 *)0x9330, (UINT8 *)0x9340, (UINT8 *)0x9350, (UINT8 *)0x9360, (UINT8 *)0x9370, (UINT8 *)0x9380, (UINT8 *)0x9390, (UINT8 *)0x93A0, (UINT8 *)0x93B0, (UINT8 *)0x93C0, (UINT8 *)0x93D0, (UINT8 *)0x93E0, (UINT8 *)0x93F0,
        (UINT8 *)0x9400, (UINT8 *)0x9410, (UINT8 *)0x9420, (UINT8 *)0x9430, (UINT8 *)0x9440, (UINT8 *)0x9450, (UINT8 *)0x9460, (UINT8 *)0x9470, (UINT8 *)0x9480, (UINT8 *)0x9490, (UINT8 *)0x94A0, (UINT8 *)0x94B0, (UINT8 *)0x94C0, (UINT8 *)0x94D0, (UINT8 *)0x94E0, (UINT8 *)0x94F0,
        (UINT8 *)0x9500, (UINT8 *)0x9510, (UINT8 *)0x9520, (UINT8 *)0x9530, (UINT8 *)0x9540, (UINT8 *)0x9550, (UINT8 *)0x9560, (UINT8 *)0x9570, (UINT8 *)0x9580, (UINT8 *)0x9590, (UINT8 *)0x95A0, (UINT8 *)0x95B0, (UINT8 *)0x95C0, (UINT8 *)0x95D0, (UINT8 *)0x95E0, (UINT8 *)0x95F0,
        (UINT8 *)0x9600, (UINT8 *)0x9610, (UINT8 *)0x9620, (UINT8 *)0x9630, (UINT8 *)0x9640, (UINT8 *)0x9650, (UINT8 *)0x9660, (UINT8 *)0x9670, (UINT8 *)0x9680, (UINT8 *)0x9690, (UINT8 *)0x96A0, (UINT8 *)0x96B0, (UINT8 *)0x96C0, (UINT8 *)0x96D0, (UINT8 *)0x96E0, (UINT8 *)0x96F0,
        (UINT8 *)0x9700, (UINT8 *)0x9710, (UINT8 *)0x9720, (UINT8 *)0x9730, (UINT8 *)0x9740, (UINT8 *)0x9750, (UINT8 *)0x9760, (UINT8 *)0x9770, (UINT8 *)0x9780, (UINT8 *)0x9790, (UINT8 *)0x97A0, (UINT8 *)0x97B0, (UINT8 *)0x97C0, (UINT8 *)0x97D0, (UINT8 *)0x97E0, (UINT8 *)0x97F0,
    };

    if (*(bkgMemory[*_zeldaAnimationTile0]) == tile[0] && *(bkgMemory[*_zeldaAnimationTile0] + 1) == tile[1]
            && *(bkgMemory[*_zeldaAnimationTile0] + 2) == tile[2] && *(bkgMemory[*_zeldaAnimationTile0] + 3) == tile[3]
            && *(bkgMemory[*_zeldaAnimationTile0] + 4) == tile[4] && *(bkgMemory[*_zeldaAnimationTile0] + 5) == tile[5]
            && *(bkgMemory[*_zeldaAnimationTile0] + 6) == tile[6] && *(bkgMemory[*_zeldaAnimationTile0] + 7) == tile[7]
            && *(bkgMemory[*_zeldaAnimationTile0] + 8) == tile[8] && *(bkgMemory[*_zeldaAnimationTile0] + 9) == tile[9]
            && *(bkgMemory[*_zeldaAnimationTile0] + 10) == tile[10] && *(bkgMemory[*_zeldaAnimationTile0] + 11) == tile[11]
            && *(bkgMemory[*_zeldaAnimationTile0] + 12) == tile[12] && *(bkgMemory[*_zeldaAnimationTile0] + 13) == tile[13]
            && *(bkgMemory[*_zeldaAnimationTile0] + 14) == tile[14] && *(bkgMemory[*_zeldaAnimationTile0] + 15) == tile[15])
        {
            return 1;
        }

    return 0;
}

UBYTE FindAnimationTile() BANKED 
{
    // the pointer to the animation tile will be wiped by the re-ordering of the HUD
    // grab a static reference to it while it's available;
    initTileReference();

    BYTE found = 0;
    while (!found)
    {
        // look for sea water tile (isolation)
        found = CompareAnimationTile(sea0a);
        if (found) 
        {
            animationTile = ZELDA_TILE_ANIMATION_SEA;
            break;
        }

        // look for sea water with crashing wave tile
        found = CompareAnimationTile(wave0a);
        if (found) 
        {
            animationTile = ZELDA_TILE_ANIMATION_WAVE;
            break;
        }

        // look for river water tile (isolation)
        found = CompareAnimationTile(river0);
        if (found) 
        {
            animationTile = ZELDA_TILE_ANIMATION_RIVER;
            break;
        }

        // look for sea water (with river water) tile
        found = CompareAnimationTile(sea0b);
        if (found) 
        {
            animationTile = ZELDA_TILE_ANIMATION_SEA_RIVER;
            break;
        }

        // look for lake water tile
        found = CompareAnimationTile(lake0);
        if (found) 
        {
            animationTile = ZELDA_TILE_ANIMATION_LAKE;
            break;
        }

        // look for lava tile
        found = CompareAnimationTile(lava0);
        if (found) 
        {
            animationTile = ZELDA_TILE_ANIMATION_LAVA;
            break;
        }

        // look for lamp tile
        found = CompareAnimationTile(lamp0a);
        if (found) 
        {
            animationTile = ZELDA_TILE_ANIMATION_LAMP;
            break;
        }

        // look for torch tile (isolation)
        found = CompareAnimationTile(torch0);
        if (found) 
        {
            animationTile = ZELDA_TILE_ANIMATION_TORCH;
            break;
        }

        // look for torch tile (with lamp)
        found = CompareAnimationTile(torch3);
        if (found) 
        {
            animationTile = ZELDA_TILE_ANIMATION_TORCH_AND_LAMP;
            break;
        }

        // look for blank tile (no animation)
        found = CompareAnimationTile(blank);
        if (found) 
        {
            animationTile = ZELDA_TILE_ANIMATION_NONE;
            break;
        }
    }

    return animationTile == ZELDA_TILE_ANIMATION_NONE ? 0 : 1;
}

void AnimateSea() BANKED
{
    if (IS_FRAME_32) 
    {
        switch (frame) 
        {
            case 0:
                set_bkg_data(staticRefTile0, 1, sea1a);
                set_bkg_data(staticRefTile1, 1, sea1b);
                frame++;
                break;
            case 1:
                set_bkg_data(staticRefTile0, 1, sea2a);
                set_bkg_data(staticRefTile1, 1, sea2b);
                frame++;
                break;
            case 2:
                set_bkg_data(staticRefTile0, 1, sea3a);
                set_bkg_data(staticRefTile1, 1, sea3b);
                frame++;
                break;
            case 3:
                set_bkg_data(staticRefTile0, 1, sea0a);
                set_bkg_data(staticRefTile1, 1, sea0b);
                frame = 0;
                break;
        }
    }
}

void AnimateWave() BANKED
{
    if (IS_FRAME_32) 
    {
        switch (frame) 
        {
            case 0:
                set_bkg_data(staticRefTile0, 1, wave1a);
                set_bkg_data(staticRefTile1, 1, wave1b);
                set_bkg_data(staticRefTile2, 1, sea1a);
                set_bkg_data(staticRefTile3, 1, sea1b);
                frame++;
                break;
            case 1:
                set_bkg_data(staticRefTile0, 1, wave2a);
                set_bkg_data(staticRefTile1, 1, wave2b);
                set_bkg_data(staticRefTile2, 1, sea2a);
                set_bkg_data(staticRefTile3, 1, sea2b);
                frame++;
                break;
            case 2:
                set_bkg_data(staticRefTile0, 1, wave3a);
                set_bkg_data(staticRefTile1, 1, wave3b);
                set_bkg_data(staticRefTile2, 1, sea3a);
                set_bkg_data(staticRefTile3, 1, sea3b);
                frame++;
                break;
            case 3:
                set_bkg_data(staticRefTile0, 1, wave0a);
                set_bkg_data(staticRefTile1, 1, wave0b);
                set_bkg_data(staticRefTile2, 1, sea0a);
                set_bkg_data(staticRefTile3, 1, sea0b);
                frame = 0;
                break;
        }
    }
}

void AnimateRiver() BANKED
{
    if (IS_FRAME_32) 
    {
        switch (frame) 
        {
            case 0:
                set_bkg_data(staticRefTile0, 1, river1);
                frame++;
                break;
            case 1:
                set_bkg_data(staticRefTile0, 1, river2);
                frame++;
                break;
            case 2:
                set_bkg_data(staticRefTile0, 1, river3);
                frame++;
                break;
            case 3:
                set_bkg_data(staticRefTile0, 1, river0);
                frame = 0;
                break;
        }
    }
}

void AnimateSeaRiver() BANKED
{
    if (IS_FRAME_32) 
    {
        switch (frame) 
        {
            case 0:
                set_bkg_data(staticRefTile0, 1, sea1b);
                set_bkg_data(staticRefTile1, 1, sea1a);
                set_bkg_data(staticRefTile2, 1, river1);
                frame++;
                break;
            case 1:
                set_bkg_data(staticRefTile0, 1, sea2b);
                set_bkg_data(staticRefTile1, 1, sea2a);
                set_bkg_data(staticRefTile2, 1, river2);
                frame++;
                break;
            case 2:
                set_bkg_data(staticRefTile0, 1, sea3b);
                set_bkg_data(staticRefTile1, 1, sea3a);
                set_bkg_data(staticRefTile2, 1, river3);
                frame++;
                break;
            case 3:
                set_bkg_data(staticRefTile0, 1, sea0b);
                set_bkg_data(staticRefTile1, 1, sea0a);
                set_bkg_data(staticRefTile2, 1, river0);
                frame = 0;
                break;
        }
    }
}

void AnimateLake() BANKED
{
    if (IS_FRAME_64) 
    {
        switch (frame) 
        {
            case 0:
                set_bkg_data(staticRefTile0, 1, lake1);
                frame++;
                break;
            case 1:
                set_bkg_data(staticRefTile0, 1, lake2);
                frame++;
                break;
            case 2:
                set_bkg_data(staticRefTile0, 1, lake3);
                frame++;
                break;
            case 3:
                set_bkg_data(staticRefTile0, 1, lake0);
                frame = 0;
                break;
        }
    }
}

void AnimateLava() BANKED
{
    // small, big, smile, dash, smile, big
    // smile, dash, small, big, small, dash
    if (IS_FRAME_64) 
    {
        switch (frame) 
        {
            case 0:
                set_bkg_data(staticRefTile0, 1, lava1);
                set_bkg_data(staticRefTile1, 1, lava3);
                frame++;
                break;
            case 1:
                set_bkg_data(staticRefTile0, 1, lava2);
                set_bkg_data(staticRefTile1, 1, lava0);
                frame++;
                break;
            case 2:
                set_bkg_data(staticRefTile0, 1, lava3);
                set_bkg_data(staticRefTile1, 1, lava1);
                frame++;
                break;
            case 3:
                set_bkg_data(staticRefTile0, 1, lava2);
                set_bkg_data(staticRefTile1, 1, lava0);
                frame++;
                break;
            case 4:
                set_bkg_data(staticRefTile0, 1, lava1);
                set_bkg_data(staticRefTile1, 1, lava3);
                frame++;
                break;
            case 5:
                set_bkg_data(staticRefTile0, 1, lava0);
                set_bkg_data(staticRefTile1, 1, lava2);
                frame = 0;
                break;
        }
    }
}

void AnimateLamp() BANKED
{
    if (IS_FRAME_16) 
    {
        switch (frame) 
        {
            case 0:
                set_bkg_data(staticRefTile0, 1, lamp1a);
                set_bkg_data(staticRefTile1, 1, lamp1b);
                frame++;
                break;
            case 1:
                set_bkg_data(staticRefTile0, 1, lamp2a);
                set_bkg_data(staticRefTile1, 1, lamp2b);
                frame++;
                break;
            case 2:
                set_bkg_data(staticRefTile0, 1, lamp3a);
                set_bkg_data(staticRefTile1, 1, lamp3b);
                frame++;
                break;
            case 3:
                set_bkg_data(staticRefTile0, 1, lamp2a);
                set_bkg_data(staticRefTile1, 1, lamp2b);
                frame++;
                break;
            case 4:
                set_bkg_data(staticRefTile0, 1, lamp1a);
                set_bkg_data(staticRefTile1, 1, lamp1b);
                frame++;
                break;
            case 5:
                set_bkg_data(staticRefTile0, 1, lamp0a);
                set_bkg_data(staticRefTile1, 1, lamp0b);
                frame = 0;
                break;
        }
    }
}

void AnimateTorch() BANKED
{
    if (IS_FRAME_32) 
    {
        switch (frame) 
        {
            case 0:
                set_bkg_data(staticRefTile0, 1, torch1);
                frame++;
                break;
            case 1:
                set_bkg_data(staticRefTile0, 1, torch2);
                frame++;
                break;
            case 2:
                set_bkg_data(staticRefTile0, 1, torch3);
                frame++;
                break;
            case 3:
                set_bkg_data(staticRefTile0, 1, torch2);
                frame++;
                break;
            case 4:
                set_bkg_data(staticRefTile0, 1, torch1);
                frame++;
                break;
            case 5:
                set_bkg_data(staticRefTile0, 1, torch0);
                frame = 0;
                break;
        }
    }
}

void AnimateTorchAndLamp() BANKED
{
    // purposely slow the lamp animation down to sync with lamp
    if (IS_FRAME_32) 
    {
        switch (frame) 
        {
            case 0:
                set_bkg_data(staticRefTile0, 1, torch1);
                set_bkg_data(staticRefTile1, 1, lamp2a);
                set_bkg_data(staticRefTile2, 1, lamp2b);
                frame++;
                break;
            case 1:
                set_bkg_data(staticRefTile0, 1, torch2);
                set_bkg_data(staticRefTile1, 1, lamp1a);
                set_bkg_data(staticRefTile2, 1, lamp1b);
                frame++;
                break;
            case 2:
                set_bkg_data(staticRefTile0, 1, torch3);
                set_bkg_data(staticRefTile1, 1, lamp0a);
                set_bkg_data(staticRefTile2, 1, lamp0b);
                frame++;
                break;
            case 3:
                set_bkg_data(staticRefTile0, 1, torch2);
                set_bkg_data(staticRefTile1, 1, lamp1a);
                set_bkg_data(staticRefTile2, 1, lamp1b);
                frame++;
                break;
            case 4:
                set_bkg_data(staticRefTile0, 1, torch1);
                set_bkg_data(staticRefTile1, 1, lamp2a);
                set_bkg_data(staticRefTile2, 1, lamp2b);
                frame++;
                break;
            case 5:
                set_bkg_data(staticRefTile0, 1, torch0);
                set_bkg_data(staticRefTile1, 1, lamp3a);
                set_bkg_data(staticRefTile2, 1, lamp3b);
                frame = 0;
                break;
        }
    }
}

void AnimateTile() BANKED
{
    switch (animationTile) {
        case ZELDA_TILE_ANIMATION_SEA:
            AnimateSea();
            break;
        case ZELDA_TILE_ANIMATION_WAVE:
            AnimateWave();
            break;
        case ZELDA_TILE_ANIMATION_RIVER:
            AnimateRiver();
            break;
        case ZELDA_TILE_ANIMATION_SEA_RIVER:
            AnimateSeaRiver();
            break;
        case ZELDA_TILE_ANIMATION_LAKE:
            AnimateLake();
            break;
        case ZELDA_TILE_ANIMATION_LAVA:
            AnimateLava();
            break;
        case ZELDA_TILE_ANIMATION_LAMP:
            AnimateLamp();
            break;
        case ZELDA_TILE_ANIMATION_TORCH:
            AnimateTorch();
            break;
        case ZELDA_TILE_ANIMATION_TORCH_AND_LAMP:
            AnimateTorchAndLamp();
            break;
    }
}
