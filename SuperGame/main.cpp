/*****************************************
* main.cpp
*
* Main run function for game
*****************************************/

/* Includes */
// Libraries
#include <stdio.h>
// Project Headers
#include "bitmaps.h"
#include "character.h"
#include "game.h"

int main(int argc, char **argv)
{
    Game g = Game("SuperGame: A Game of Super Fun!");
    if(!g.Setup(SCREEN_W, SCREEN_H))
    {
        return -1;
    }

    ALLEGRO_BITMAP *terrain[] = {al_load_bitmap(WOOD_PNG), al_load_bitmap(GRASS_PNG), al_load_bitmap(COBBLESTONE_PNG)};
    ALLEGRO_BITMAP *obstacle[] = {al_load_bitmap(OBSTACLE_PNG)};
    Character melee_char  = Character(&g.map, (SCREEN_W / 2.0 - BLOCK_SIZE / 2.0), (SCREEN_H / 2.0 - BLOCK_SIZE / 2.0));
    Character archer_char = Character(&g.map, melee_char.x, melee_char.y);
    Character magic_char  = Character(&g.map, melee_char.x, melee_char.y);
    Character *char_order[NUM_CHARACTERS] = {&melee_char, &archer_char, &magic_char};
    Character *buffer;
    bool key[4] = { false, false, false, false };
    bool redraw = true;
    bool exit = false;
    ALLEGRO_TRANSFORM transform;
    int start_x, start_y;

    g.ParseMap("Maps/test_large_map.mp");
    srand(time(NULL));

    melee_char.SetBitmap(MELEE_CHAR_PNG);
    archer_char.SetBitmap(ARCHER_CHAR_PNG);
    magic_char.SetBitmap(MAGIC_CHAR_PNG);

   al_convert_mask_to_alpha(obstacle[0], al_map_rgb(255, 0, 255));
   al_set_target_bitmap(al_get_backbuffer(g.GetDisplay()));
   al_flip_display();
   al_start_timer(g.GetTimer());

    while(!exit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(g.GetEventQueue(), &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            if ((key[UP] + key[DOWN] == 1) || (key[LEFT] + key[RIGHT]) == 1)
            {
                if(char_order[0]->Move(key))
                {
                    char_order[1]->Follow(char_order[0]);
                    char_order[2]->Follow(char_order[1]);
                    redraw = true;
                }
            }
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
        {
            g.Resize();
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    key[UP] = true;
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[DOWN] = true;
                    break;

                case ALLEGRO_KEY_LEFT:
                    key[LEFT] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[RIGHT] = true;
                    break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    key[UP] = false;
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[DOWN] = false;
                    break;

                case ALLEGRO_KEY_LEFT:
                    key[LEFT] = false;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[RIGHT] = false;
                    break;

                case ALLEGRO_KEY_TAB:
                    char_order[0]->SwapPlacement(char_order[1]);
                    char_order[0]->SwapPlacement(char_order[2]);
                    buffer = char_order[0];
                    char_order[0] = char_order[1];
                    char_order[1] = char_order[2];
                    char_order[2] = buffer;
                    redraw = true;
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    exit = true;
                    break;
            }
        }

        if(redraw && al_is_event_queue_empty(g.GetEventQueue()))
        {
            redraw = false;

            start_x = min(max(char_order[0]->x - (SCREEN_W/2), 0), (g.map.w - MAP_BLOCK_DRAWN_W) * BLOCK_SIZE);
            start_y = min(max(char_order[0]->y - (SCREEN_H/2), 0), (g.map.h - MAP_BLOCK_DRAWN_H) * BLOCK_SIZE);


            al_identity_transform(&transform);
            al_translate_transform(&transform, -start_x, -start_y);

            al_use_transform(&transform);
            al_clear_to_color(al_map_rgb(0, 0, 0));

            //Draw ground layer
            for (int i = 0; i < g.map.w; i++)
            {
                for (int j = 0; j < g.map.h; j++)
                {
                    al_draw_bitmap_region(terrain[g.map.ground.tile[i][j].type],
                                          BLOCK_SIZE * g.map.ground.tile[i][j].variant,
                                          0,
                                          BLOCK_SIZE,
                                          BLOCK_SIZE,
                                          BLOCK_SIZE * i,
                                          BLOCK_SIZE * j,
                                          0);

                }
            }


            //Draw low layer
            for (int i = 0; i < g.map.w; i++)
            {
                for (int j = 0; j < g.map.h; j++)
                {
                    if(g.map.low.tile[i][j].type != 0)
                        al_draw_bitmap_region(terrain[g.map.low.tile[i][j].type - 1],
                                              BLOCK_SIZE * g.map.low.tile[i][j].variant,
                                              0,
                                              BLOCK_SIZE,
                                              BLOCK_SIZE,
                                              BLOCK_SIZE * i,
                                              BLOCK_SIZE * j,
                                              0);
                }
            }

            //Draw characters
            char_order[2]->Draw();
            char_order[1]->Draw();
            char_order[0]->Draw();

            //Draw obstacle layer
            for (int i = 0; i < g.map.w; i++)
            {
                for (int j = 0; j < g.map.h; j++)
                {
                    if( g.map.obstacle.tile[i][j].type != 0)
                        al_draw_bitmap_region(obstacle[g.map.obstacle.tile[i][j].type - 1],
                                              BLOCK_SIZE * g.map.obstacle.tile[i][j].variant,
                                              0,
                                              BLOCK_SIZE,
                                              BLOCK_SIZE,
                                              BLOCK_SIZE * i,
                                              BLOCK_SIZE * j,
                                              0);
                }
            }

            //Draw high layer
            for (int i = 0; i < g.map.w; i++)
            {
                for (int j = 0; j < g.map.h; j++)
                {
                    if( g.map.high.tile[i][j].type != 0)
                        al_draw_bitmap_region(terrain[g.map.high.tile[i][j].type - 1],
                                              BLOCK_SIZE * g.map.high.tile[i][j].variant,
                                              0,
                                              BLOCK_SIZE,
                                              BLOCK_SIZE,
                                              BLOCK_SIZE * i,
                                              BLOCK_SIZE * j,
                                              0);
                }
            }

            al_identity_transform(&transform);
            al_use_transform(&transform);

            al_flip_display();
        }
    }

    al_destroy_bitmap(terrain[0]);
    al_destroy_bitmap(terrain[1]);
    al_destroy_bitmap(terrain[2]);
    al_destroy_bitmap(obstacle[0]);

    return 0;
}