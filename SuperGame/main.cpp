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
    int obstacle_x = 0;
    int obstacle_y = 0;
    int obstacle_w = 32;
    int obstacle_h = 32;
    int start_x, start_y, tile_start_x, tile_start_y;

    g.ParseMap("Maps/test_large_map.mp");
    srand(time(NULL));

    melee_char.SetBitmap(MELEE_CHAR_PNG);
    archer_char.SetBitmap(ARCHER_CHAR_PNG);
    magic_char.SetBitmap(MAGIC_CHAR_PNG);

   al_convert_mask_to_alpha(obstacle[0], al_map_rgb(255, 0, 255));
   al_set_target_bitmap(al_get_backbuffer(g.display));
   al_flip_display();
   al_start_timer(g.timer);

    while(!exit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(g.event_queue, &ev);

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

        if(redraw && al_is_event_queue_empty(g.event_queue))
        {
            start_x = max(char_order[0]->x - ((MAP_BLOCK_DRAWN_W * BLOCK_SIZE)/2), 0);
            start_x = min(char_order[0]->x - ((MAP_BLOCK_DRAWN_W * BLOCK_SIZE)/2), ((MAP_BLOCK_W - MAP_BLOCK_DRAWN_W) * BLOCK_SIZE));
            start_y = max(char_order[0]->y - ((MAP_BLOCK_DRAWN_H * BLOCK_SIZE)/2), 0);
            start_y = min(char_order[0]->y - ((MAP_BLOCK_DRAWN_H * BLOCK_SIZE)/2), ((MAP_BLOCK_H - MAP_BLOCK_DRAWN_H) * BLOCK_SIZE));
            tile_start_x = start_x % BLOCK_SIZE;
            tile_start_y = start_y % BLOCK_SIZE;

            //Draw ground layer
            for(int i = start_x / BLOCK_SIZE; i < (start_x / BLOCK_SIZE) + MAP_BLOCK_DRAWN_W; i++)
            {
                for (int j = start_y / BLOCK_SIZE; j < (start_y / BLOCK_SIZE) + MAP_BLOCK_DRAWN_H; j++)
                {
                    al_draw_bitmap_region(terrain[g.map.ground.tile[i][j].type],
                                            BLOCK_SIZE * g.map.ground.tile[i][j].variant,
                                            0,
                                            BLOCK_SIZE - tile_start_x,
                                            BLOCK_SIZE - tile_start_y,
                                            BLOCK_SIZE * i,
                                            BLOCK_SIZE * j,
                                            0);
                }
            }

            //Draw low layer
            for (int i = 0; i < (MAP_BLOCK_W); i++)
            {
                for (int j = 0; j < (MAP_BLOCK_H); j++)
                {
                    if(g.map.low.tile[i][j].type != 0)
                        al_draw_bitmap_region(terrain[g.map.low.tile[i][j].type - 1],
                                                BLOCK_SIZE * g.map.low.tile[i][j].variant,
                                                0,
                                                BLOCK_SIZE - tile_start_x,
                                                BLOCK_SIZE - tile_start_y,
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
            for (int i = 0; i < (MAP_BLOCK_W); i++)
            {
                for (int j = 0; j < (MAP_BLOCK_H); j++)
                {
                    if( g.map.obstacle.tile[i][j].type != 0)
                        al_draw_bitmap_region(terrain[g.map.obstacle.tile[i][j].type - 1],
                                                BLOCK_SIZE * g.map.obstacle.tile[i][j].variant,
                                                0,
                                                BLOCK_SIZE - tile_start_x,
                                                BLOCK_SIZE - tile_start_y,
                                                BLOCK_SIZE * i,
                                                BLOCK_SIZE * j,
                                                0);
                }
            }

            //Draw high layer
            for (int i = 0; i < (MAP_BLOCK_W); i++)
            {
                for (int j = 0; j < (MAP_BLOCK_H); j++)
                {
                    if( g.map.high.tile[i][j].type != 0)
                        al_draw_bitmap_region(terrain[g.map.high.tile[i][j].type - 1],
                                                BLOCK_SIZE * g.map.high.tile[i][j].variant,
                                                0,
                                                BLOCK_SIZE - char_order[0]->x % BLOCK_SIZE,
                                                BLOCK_SIZE - char_order[0]->y % BLOCK_SIZE,
                                                BLOCK_SIZE * i,
                                                BLOCK_SIZE * j,
                                                0);
                }
            }

            al_flip_display();

        }
    }

    al_destroy_bitmap(terrain[0]);
    al_destroy_bitmap(terrain[1]);
    al_destroy_bitmap(terrain[2]);
    al_destroy_bitmap(obstacle[0]);
    al_destroy_timer(g.timer);
    al_destroy_display(g.display);
    al_destroy_event_queue(g.event_queue);

    return 0;
}
