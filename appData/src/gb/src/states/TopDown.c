#pragma bank=18

#include "TopDown.h"
#include "Scroll.h"
#include "Input.h"
#include "Collision.h"
#include "Actor.h"
#include "GameTime.h"
#include <rand.h>

UBYTE *ptr_div_reg_1 = (UBYTE *)0xFF04;

void Start_TopDown()
{
    UBYTE rnd;
    LOG("START TOPDOWN\n");
    scroll_target = &player.pos;
    game_time = 0;


    rnd = *(ptr_div_reg_1);
    initrand(rnd);
    // set_sprite_tile(0, 24);
    // set_sprite_tile(1, 24);
    // set_sprite_tile(2, 24);
    // set_sprite_tile(3, 24);
    // set_sprite_tile(4, 24);
    // set_sprite_tile(5, 24);
    // set_sprite_tile(6, 24);
    // set_sprite_tile(7, 24);
    // set_sprite_tile(8, 24);
    // set_sprite_tile(9, 24);

    LOG("END START TOPDOWN\n");
}

void Update_TopDown()
{
    UBYTE tile_x, tile_y, i, a, rnd;

    tile_x = player.pos.x >> 3;
    tile_y = player.pos.y >> 3;


    // Move NPCs
    for (i = 1; i < actors_active_size; i++)
    {
        a = actors_active[i];
        if (ACTOR_ON_TILE(a))
        {
            if (IS_FRAME_32)
            {
                rnd = rand();
                if (rnd & 0x1u)
                {
                    rnd = rand();
                    actors[a].vel.x = 1 - ((rnd & 0x1u) * 2);
                    actors[a].vel.y = 0;
                }
                else
                {
                    rnd = rand();
                    actors[a].vel.x = 0;
                    actors[a].vel.y = 1 - ((rnd & 0x1u) * 2);
                }
            }
            else
            {
                actors[a].vel.x = 0;
                actors[a].vel.y = 0;
            }
        }
    }

    // Move
    if (ACTOR_ON_TILE(0))
    {
        player.vel.x = 0;
        player.vel.y = 0;

        if (INPUT_LEFT)
        {
            UBYTE tile_left = tile_x - 1;
            player.dir.y = 0;
            player.dir.x = -1;
            if (!TileAt(tile_left, tile_y) && !ActorOverlapsActorTile(tile_left, tile_y))
            {
                player.vel.x = -1;
            }
        }
        else if (INPUT_RIGHT)
        {
            UBYTE tile_right = tile_x + 1;
            player.dir.y = 0;
            player.dir.x = 1;
            if (!TileAt(tile_right + 1, tile_y) && !ActorOverlapsActorTile(tile_right, tile_y))
            {
                player.vel.x = 1;
            }
        }
        else
        {
            if (INPUT_UP)
            {
                UBYTE tile_up = tile_y - 1;
                player.dir.x = 0;
                player.dir.y = -1;
                if (!TileAt(tile_x, tile_up) && !TileAt(tile_x + 1, tile_up) && !ActorOverlapsActorTile(tile_x, tile_up))
                {
                    player.vel.y = -1;
                }
            }
            else if (INPUT_DOWN)
            {
                UBYTE tile_down = tile_y + 1;
                player.dir.x = 0;
                player.dir.y = 1;
                if (!TileAt(tile_x, tile_down) && !TileAt(tile_x + 1, tile_down) && !ActorOverlapsActorTile(tile_x, tile_down))
                {
                    player.vel.y = 1;
                }
            }
        }
    }

    // LOG("[%u, %u] [%u, %u]\n", player.vel.x, player.vel.y, player.pos.x, player.pos.y);

    if (INPUT_SELECT_PRESSED)
    {
        player.pos.x = 32;
        player.pos.y = 32;
    }

    if (INPUT_START_PRESSED)
    {
        player.pos.x = 512;
        player.pos.y = 512;
    }   
}
