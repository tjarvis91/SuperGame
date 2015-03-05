/*****************************************
* main.cpp
*
* Main run function for game
*****************************************/

/* Includes */
// Libraries
#include <stdio.h>
// Project Headers
#include "game_bitmaps.h"
#include "game.h"

int main(int argc, char **argv)
{
    ALLEGRO_BITMAP *melee_char = NULL;
    ALLEGRO_BITMAP *terrain = NULL;
    ALLEGRO_BITMAP *obstacle = NULL;
    int melee_char_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
    int melee_char_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
    int try_x;
    int try_y;
    bool key[4] = { false, false, false, false };
    bool redraw = true;
    bool doexit = false;
    int character_direction = 0;
    MapTile map[SCREEN_W/32][SCREEN_H/32];
    double character_speed = 4.0;
    int obstacle_x = 0;
    int obstacle_y = 0;
    int obstacle_w = 32;
    int obstacle_h = 32;
    int character_size = 32;

   memset(map, 0, sizeof(map));
   srand(time(NULL));

    Game g = Game();
    if(!g.Setup())
    {
        return -1;
    }

    melee_char = al_load_bitmap(MELEE_CHAR_PNG);
    terrain = al_load_bitmap(WOOD_PNG);
    obstacle = al_load_bitmap(OBSTACLE_PNG);

   al_convert_mask_to_alpha(melee_char, al_map_rgb(255, 0, 255));

   al_convert_mask_to_alpha(obstacle, al_map_rgb(255, 0, 255));

   al_set_target_bitmap(al_get_backbuffer(g.display));

   al_flip_display();

   al_start_timer(g.timer);

   //This generates the map
   for (int i = 0; i < (SCREEN_W / 32); i++)
   {
       for (int j = 0; j < (SCREEN_H / 32); j++)
       {
           int k = rand() % 4;
           map[i][j].floor = k;
       }
   }

   obstacle_x = 32 * (rand() % (SCREEN_W / 32));
   obstacle_y = 32 * (rand() % (SCREEN_H / 32));
   map[obstacle_x/32][obstacle_y/32].filled = true;

   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(g.event_queue, &ev);

      try_x = 0;
      try_y = 0;
      if(ev.type == ALLEGRO_EVENT_TIMER) {
          if (key[UP] && melee_char_y >= character_speed)
          {
              try_y = -character_speed;
          }

          if (key[DOWN] && melee_char_y <= SCREEN_H - BOUNCER_SIZE - character_speed )
          {
               try_y = character_speed;
          }

          if (key[LEFT] && melee_char_x >= character_speed )
          {
             try_x = -character_speed;
          }

          if (key[RIGHT] && melee_char_x <= SCREEN_W - BOUNCER_SIZE - character_speed )
          {
             try_x = character_speed;
          }

          if (!map[(melee_char_x + try_x) / 32][(melee_char_y + try_y) / 32].filled &&
              !map[(melee_char_x + character_size + try_x) / 32][(melee_char_y + try_y) / 32].filled &&
              !map[(melee_char_x + try_x) / 32][(melee_char_y + character_size + try_y) / 32].filled &&
              !map[(melee_char_x + character_size + try_x) / 32][(melee_char_y + character_size + try_y) / 32].filled )
          {
              melee_char_x += try_x;
              melee_char_y += try_y;
              if (try_y < 0)
              {
                  character_direction = UP;
              }
              else if (try_y > 0)
              {
                  character_direction = DOWN;
              }
              else if (try_x < 0)
              {
                  character_direction = LEFT;
              }
              else if (try_x > 0)
              {
                  character_direction = RIGHT;
              }
          }

         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
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
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
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

      if(redraw && al_is_event_queue_empty(g.event_queue)) {
         redraw = false;


         //This draws the map
         for (int i = 0; i < (SCREEN_W / 32); i++)
         {
             for (int j = 0; j < (SCREEN_H / 32); j++)
             {
                 al_draw_bitmap_region(terrain, 32 * map[i][j].floor, 0, 32, 32, 32 * i, 32 * j, 0);
             }
         }

         //This draws an obstacle
         al_draw_bitmap_region(obstacle, 0, 0, obstacle_w, obstacle_h, obstacle_x, obstacle_y, 0);

             al_draw_bitmap_region(melee_char, character_size * character_direction, 0, character_size, character_size, melee_char_x, melee_char_y, 0);

         al_flip_display();
      }
   }

   al_destroy_bitmap(melee_char);
   al_destroy_bitmap(terrain);
   al_destroy_bitmap(obstacle);
   al_destroy_timer(g.timer);
   al_destroy_display(g.display);
   al_destroy_event_queue(g.event_queue);

   return 0;
}