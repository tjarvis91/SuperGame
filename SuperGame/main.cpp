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
    Character melee_char = Character((SCREEN_W / 2.0 - BLOCK_SIZE / 2.0), (SCREEN_H / 2.0 - BLOCK_SIZE / 2.0));
    ALLEGRO_BITMAP *terrain = NULL;
    ALLEGRO_BITMAP *obstacle = NULL;
    int try_x;
    int try_y;
    bool key[4] = { false, false, false, false };
    bool redraw = true;
    bool doexit = false;
    MapTile map[MAP_BLOCK_W][MAP_BLOCK_H];
    int obstacle_x = 0;
    int obstacle_y = 0;
    int obstacle_w = 32;
    int obstacle_h = 32;

    memset(map, 0, sizeof(map));
    srand(time(NULL));

    Game g = Game();
    if(!g.Setup())
    {
        return -1;
    }

    melee_char.SetBitmap(MELEE_CHAR_PNG);
    terrain = al_load_bitmap(WOOD_PNG);
    obstacle = al_load_bitmap(OBSTACLE_PNG);

   al_convert_mask_to_alpha(obstacle, al_map_rgb(255, 0, 255));

   al_set_target_bitmap(al_get_backbuffer(g.display));

   al_flip_display();

   al_start_timer(g.timer);

   //This generates the map
   for (int i = 0; i < (MAP_BLOCK_W); i++)
   {
       for (int j = 0; j < (MAP_BLOCK_H); j++)
       {
           int k = rand() % 4;
           map[i][j].floor = k;
       }
   }

   obstacle_x = BLOCK_SIZE * (rand() % (MAP_BLOCK_W));
   obstacle_y = BLOCK_SIZE * (rand() % (MAP_BLOCK_H));
   map[obstacle_x/BLOCK_SIZE][obstacle_y/BLOCK_SIZE].filled = true;

    while(!doexit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(g.event_queue, &ev);

        try_x = 0;
        try_y = 0;
        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            if ((key[UP] + key[DOWN] == 1) || (key[LEFT] + key[RIGHT]) == 1)
                melee_char.Move(key);

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

                case ALLEGRO_KEY_ESCAPE:
                    doexit = true;
                    break;
            }
        }

        if(redraw && al_is_event_queue_empty(g.event_queue))
        {
            redraw = false;


            //This draws the map
            for (int i = 0; i < (MAP_BLOCK_W); i++)
            {
                for (int j = 0; j < (MAP_BLOCK_H); j++)
                {
                    al_draw_bitmap_region(terrain, 32 * map[i][j].floor, 0, 32, 32, 32 * i, 32 * j, 0);
                }
            }

            //This draws an obstacle
            al_draw_bitmap_region(obstacle, 0, 0, obstacle_w, obstacle_h, obstacle_x, obstacle_y, 0);

            melee_char.Draw();

            al_flip_display();
        }
    }

    al_destroy_bitmap(terrain);
    al_destroy_bitmap(obstacle);
    al_destroy_timer(g.timer);
    al_destroy_display(g.display);
    al_destroy_event_queue(g.event_queue);

    return 0;
}