#ifndef ZELDAS_ADVENTURE_CORE_H
#define ZELDAS_ADVENTURE_CORE_H

#include <gb/gb.h>

/**
 * Takes a number and returns the associated tile image
 */
UINT8 GetNumberTile(UINT8 number);

/**
 * Draws the HUD rupee counter for a given value
 */
void CalculateRupees(char *hud, UINT8 rupees);

/**
 * Draws the HUD hearts/health values
 */
void CalculateHearts(char *hud, UINT8 maxHearts, UINT8 health);

/**
 * Updates the rupee and hearts HUD based on provided values
 */
void CalculateHud(char *hud, UINT8 rupees, UINT8 maxHearts, UINT8 health, BYTE heartsChanged, BYTE maxHeartsChanged, BYTE rupeesChanged);

/**
 * Combine the how to draw HUD logic with the GBDK native call to set the background tiles
 */
void DrawZeldaHud(BYTE heartsChanged, BYTE maxHeartsChanged, BYTE rupeesChanged);

/**
 * The reference to the known Zelda HUD tiles gets cached and if the references
 * in tile memory get shifted, it causes a garbled HUD to be drawn
 */
void InvalidateZeldaHudCache();

/**
 * All Zelda Adventure scenes have the necessary HUD elements in the first row of the scene
 * As their location in tile memory can change we need to find and store their location before 
 * attempting to draw the HUD
 */
void InitZeldaHud();

/**
 * If the player health, max hearts or rupees collected has changed, update the HUD
 */
void CheckForHudRedraw();

#endif
