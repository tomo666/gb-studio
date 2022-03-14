#pragma bank 3

#include "data/states_defines.h"
#include "states/zeldasinventory.h"
#include "states/pointnclick.h"

#include "actor.h"
#include "camera.h"
#include "data_manager.h"
#include "game_time.h"
#include "input.h"
#include "trigger.h"
#include "vm.h"

void zeldasinventory_init() BANKED {
    pointnclick_init();
}

void zeldasinventory_update() BANKED {
    pointnclick_update();
}
