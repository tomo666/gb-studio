#ifndef ZELDAS_INVENTORY_DATA_H
#define ZELDAS_INVENTORY_DATA_H

#include <gb/gb.h>

/**
 * Load the core tiles that won't change (22 tiles)
 * data starts at 194 to account for inventory item tiles
 */
void DrawStaticInventory() BANKED;

/**
 * Draw the 7 segment circle indicating how many
 * celestial signs have been collected
 */
void DrawCelestialSigns(UINT8 shrinesComplete) BANKED;

/**
 * Draw the key indicator, this is either 0 or 1
 */
void DrawKeyIndicator(UBYTE keys) BANKED;

#endif
