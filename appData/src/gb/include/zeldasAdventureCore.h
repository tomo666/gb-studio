#ifndef ZELDAS_ADVENTURE_CORE_H
#define ZELDAS_ADVENTURE_CORE_H

#include <gb/gb.h>

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
