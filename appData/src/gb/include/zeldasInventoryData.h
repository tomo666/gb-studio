#ifndef ZELDAS_INVENTORY_DATA_H
#define ZELDAS_INVENTORY_DATA_H

#include <gb/gb.h>

void DrawStaticInventory() BANKED;
void DrawCelestialSigns(UINT8 shrinesComplete) BANKED;
void DrawKeyIndicator(UBYTE keys) BANKED;
#endif
