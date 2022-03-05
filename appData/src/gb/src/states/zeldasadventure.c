#pragma bank 3

#include "data/states_defines.h"
#include "states/zeldasadventure.h"
#include "states/topdown.h"

#include "actor.h"
#include "camera.h"
#include "collision.h"
#include "data_manager.h"
#include "game_time.h"
#include "input.h"
#include "trigger.h"
#include "math.h"
#include "vm.h"

void zeldasadventure_init() BANKED {
    topdown_init();
}

void zeldasadventure_update() BANKED {
    topdown_update();
}
