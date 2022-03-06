#ifndef ZELDAS_INVENTORY_DATA_H
#define ZELDAS_INVENTORY_DATA_H

#include <gb/gb.h>

void DrawWeaponsTreasures(ZELDA_WEAPONS weapons[19], ZELDA_TREASURES treasures[25], UINT16 equipped) BANKED;
void ConditionalScrollWeaponsRight(ZELDA_WEAPONS weapons[19], ZELDA_TREASURES treasures[25], UINT16 equipped, UINT8 totalWeaponsFound) BANKED;
void ConditionalScrollWeaponsLeft(ZELDA_WEAPONS weapons[19], ZELDA_TREASURES treasures[25], UINT16 equipped) BANKED;
void ConditionalScrollTreasuresRight(ZELDA_WEAPONS weapons[19], ZELDA_TREASURES treasures[25], UINT16 equipped, UINT8 totalTreasuresFound) BANKED;
void ConditionalScrollTreasuresLeft(ZELDA_WEAPONS weapons[19], ZELDA_TREASURES treasures[25], UINT16 equipped) BANKED;
UINT8 GetWeaponScrollOffset() BANKED;
UINT8 GetTreasureScrollOffset() BANKED;

void DrawStaticInventory() BANKED;
void DrawCelestialSigns(UINT8 shrinesComplete) BANKED;
void DrawKeyIndicator(UBYTE keys) BANKED;
#endif
