#pragma bank 6

#include <gb/gb.h>
#include "bankdata.h"
#include "zeldasTileCore.h"
#include "game_time.h"

UINT8 *bkgMemory[16] = {
(UINT8 *)0x9000, (UINT8 *)0x9010, (UINT8 *)0x9020, (UINT8 *)0x9030,
 (UINT8 *)0x9040, (UINT8 *)0x9050, (UINT8 *)0x9060, (UINT8 *)0x9070,
  (UINT8 *)0x9080, (UINT8 *)0x9090, (UINT8 *)0x90A0, (UINT8 *)0x90B0,
   (UINT8 *)0x90C0, (UINT8 *)0x90D0, (UINT8 *)0x90E0, (UINT8 *)0x90F0,
};

// UINT8 *bkgMemory[128] = {
// (UINT8 *)0x9000, (UINT8 *)0x9010, (UINT8 *)0x9020, (UINT8 *)0x9030, (UINT8 *)0x9040, (UINT8 *)0x9050, (UINT8 *)0x9060, (UINT8 *)0x9070, (UINT8 *)0x9080, (UINT8 *)0x9090, (UINT8 *)0x90A0, (UINT8 *)0x90B0, (UINT8 *)0x90C0, (UINT8 *)0x90D0, (UINT8 *)0x90E0, (UINT8 *)0x90F0,
// (UINT8 *)0x9100, (UINT8 *)0x9110, (UINT8 *)0x9120, (UINT8 *)0x9130, (UINT8 *)0x9140, (UINT8 *)0x9150, (UINT8 *)0x9160, (UINT8 *)0x9170, (UINT8 *)0x9180, (UINT8 *)0x9190, (UINT8 *)0x91A0, (UINT8 *)0x91B0, (UINT8 *)0x91C0, (UINT8 *)0x91D0, (UINT8 *)0x91E0, (UINT8 *)0x91F0,
// (UINT8 *)0x9200, (UINT8 *)0x9210, (UINT8 *)0x9220, (UINT8 *)0x9230, (UINT8 *)0x9240, (UINT8 *)0x9250, (UINT8 *)0x9260, (UINT8 *)0x9270, (UINT8 *)0x9280, (UINT8 *)0x9290, (UINT8 *)0x92A0, (UINT8 *)0x92B0, (UINT8 *)0x92C0, (UINT8 *)0x92D0, (UINT8 *)0x92E0, (UINT8 *)0x92F0,
// (UINT8 *)0x9300, (UINT8 *)0x9310, (UINT8 *)0x9320, (UINT8 *)0x9330, (UINT8 *)0x9340, (UINT8 *)0x9350, (UINT8 *)0x9360, (UINT8 *)0x9370, (UINT8 *)0x9380, (UINT8 *)0x9390, (UINT8 *)0x93A0, (UINT8 *)0x93B0, (UINT8 *)0x93C0, (UINT8 *)0x93D0, (UINT8 *)0x93E0, (UINT8 *)0x93F0,
// (UINT8 *)0x9400, (UINT8 *)0x9410, (UINT8 *)0x9420, (UINT8 *)0x9430, (UINT8 *)0x9440, (UINT8 *)0x9450, (UINT8 *)0x9460, (UINT8 *)0x9470, (UINT8 *)0x9480, (UINT8 *)0x9490, (UINT8 *)0x94A0, (UINT8 *)0x94B0, (UINT8 *)0x94C0, (UINT8 *)0x94D0, (UINT8 *)0x94E0, (UINT8 *)0x94F0,
// (UINT8 *)0x9500, (UINT8 *)0x9510, (UINT8 *)0x9520, (UINT8 *)0x9530, (UINT8 *)0x9540, (UINT8 *)0x9550, (UINT8 *)0x9560, (UINT8 *)0x9570, (UINT8 *)0x9580, (UINT8 *)0x9590, (UINT8 *)0x95A0, (UINT8 *)0x95B0, (UINT8 *)0x95C0, (UINT8 *)0x95D0, (UINT8 *)0x95E0, (UINT8 *)0x95F0,
// (UINT8 *)0x9600, (UINT8 *)0x9610, (UINT8 *)0x9620, (UINT8 *)0x9630, (UINT8 *)0x9640, (UINT8 *)0x9650, (UINT8 *)0x9660, (UINT8 *)0x9670, (UINT8 *)0x9680, (UINT8 *)0x9690, (UINT8 *)0x96A0, (UINT8 *)0x96B0, (UINT8 *)0x96C0, (UINT8 *)0x96D0, (UINT8 *)0x96E0, (UINT8 *)0x96F0,
// (UINT8 *)0x9700, (UINT8 *)0x9710, (UINT8 *)0x9720, (UINT8 *)0x9730, (UINT8 *)0x9740, (UINT8 *)0x9750, (UINT8 *)0x9760, (UINT8 *)0x9770, (UINT8 *)0x9780, (UINT8 *)0x9790, (UINT8 *)0x97A0, (UINT8 *)0x97B0, (UINT8 *)0x97C0, (UINT8 *)0x97D0, (UINT8 *)0x97E0, (UINT8 *)0x97F0,
// };

const unsigned char water0[] = {
0xFF,0x00,0xF3,0x00,0xE0,0x00,0x0E,0x00,0xFF,0x00,0x7C,0x00,0x31,0x00,0x87,0x00,
};
const unsigned char water1[] = {
0xFF,0x00,0xFC,0x00,0x38,0x00,0x83,0x00,0xFF,0x00,0xF1,0x00,0xC4,0x00,0x1E,0x00,
};
const unsigned char water2[] = {
0xFF,0x00,0x3F,0x00,0x0E,0x00,0xE0,0x00,0xFF,0x00,0xC7,0x00,0x13,0x00,0x78,0x00,
};
const unsigned char water3[] = {
0xFF,0x00,0xCF,0x00,0x83,0x00,0x38,0x00,0xFF,0x00,0x1F,0x00,0x4C,0x00,0xE1,0x00,
};

UINT8 frame = 0;
// point to animation indicator tile 15
UINT8 *_zeldaAnimationTile = (UINT8 *)0x980f;

ZELDA_TILE_ANIMATION FindAnimationTile() BANKED 
{
    BYTE found = 0;
    while (found == 0)
    {
        if (*(bkgMemory[*_zeldaAnimationTile]) == water0[0] && *(bkgMemory[*_zeldaAnimationTile] + 1) == water0[1]
            && *(bkgMemory[*_zeldaAnimationTile] + 2) == water0[2] && *(bkgMemory[*_zeldaAnimationTile] + 3) == water0[3]
            && *(bkgMemory[*_zeldaAnimationTile] + 4) == water0[4] && *(bkgMemory[*_zeldaAnimationTile] + 5) == water0[5]
            && *(bkgMemory[*_zeldaAnimationTile] + 6) == water0[6] && *(bkgMemory[*_zeldaAnimationTile] + 7) == water0[7]
            && *(bkgMemory[*_zeldaAnimationTile] + 8) == water0[8] && *(bkgMemory[*_zeldaAnimationTile] + 9) == water0[9]
            && *(bkgMemory[*_zeldaAnimationTile] + 10) == water0[10] && *(bkgMemory[*_zeldaAnimationTile] + 11) == water0[11]
            && *(bkgMemory[*_zeldaAnimationTile] + 12) == water0[12] && *(bkgMemory[*_zeldaAnimationTile] + 13) == water0[13]
            && *(bkgMemory[*_zeldaAnimationTile] + 14) == water0[14] && *(bkgMemory[*_zeldaAnimationTile] + 15) == water0[15])
        {
            found = 1;
            return ZELDA_TILE_ANIMATION_SEA;
        }
    }    

    return ZELDA_TILE_ANIMATION_NONE;
}

void AnimateSeaWater() BANKED
{
    if(IS_FRAME_32) {
        switch(frame) {
            case 0:
                set_bkg_data(0x0f, 1, water1);
                frame++;
                break;
            case 1:
                set_bkg_data(0x0f, 1, water2);
                frame++;
                break;
            case 2:
                set_bkg_data(0x0f, 1, water3);
                frame++;
                break;
            case 3:
                set_bkg_data(0x0f, 1, water0);
                frame = 0;
                break;
        }
    }
}
