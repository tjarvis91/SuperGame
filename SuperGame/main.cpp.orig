#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "game_bitmaps.h"

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;
enum directional_keys : int {
   KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT
};

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *melee_char = NULL;
   ALLEGRO_BITMAP *terrain = NULL;
   ALLEGRO_BITMAP *obstacle = NULL;
   float melee_char_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float melee_char_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
   bool character_collision[4];
   character_collision[0] = false;
   character_collision[1] = false;
   character_collision[2] = false;
   character_collision[3] = false;
   int character_direction = 0;
   int map [SCREEN_W/32][SCREEN_H/32];
   double character_speed = 4.0;
   int obstacle_x = 0;
   int obstacle_y = 0;
   int obstacle_w = 32;
   int obstacle_h = 32;
   int character_size = 32;

   srand(time(NULL));

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   if (!al_init_image_addon()) {
       al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
           NULL, ALLEGRO_MESSAGEBOX_ERROR);
       return 0;
   }

   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -2;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -3;
   }

   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }

   if(!al_init_image_addon()) {
      fprintf(stderr, "failed to initialize image addon!\n");
      return -1;
   }

    melee_char = al_load_bitmap(MELEE_CHAR_BMP);
    terrain = al_load_bitmap(GRASS_BMP);
	obstacle = al_load_bitmap(OBSTACLE_PNG);



   al_convert_mask_to_alpha(melee_char, al_map_rgb(255, 0, 255));

   al_convert_mask_to_alpha(obstacle, al_map_rgb(255, 0, 255));

   al_set_target_bitmap(al_get_backbuffer(display));

   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(melee_char);
      al_destroy_bitmap(terrain);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   al_register_event_source(event_queue, al_get_display_event_source(display));

   al_register_event_source(event_queue, al_get_timer_event_source(timer));

   al_register_event_source(event_queue, al_get_keyboard_event_source());

   al_flip_display();

   al_start_timer(timer);

   //This generates the map
   for (int i = 0; i < (SCREEN_W / 32); i++)
   {
       for (int j = 0; j < (SCREEN_H / 32); j++)
       {
           int k = rand() % 4;
           map[i][j] = k;
       }
   }

   obstacle_x = 32 * (rand() % (SCREEN_W / 32));
   obstacle_y = 32 * (rand() % (SCREEN_H / 32));

   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

      if(ev.type == ALLEGRO_EVENT_TIMER) {
		  if (key[KEY_UP] && melee_char_y >= character_speed && !character_collision[0]) {
			  melee_char_y -= character_speed;
         }

		  if (key[KEY_DOWN] && melee_char_y <= SCREEN_H - BOUNCER_SIZE - character_speed && !character_collision[1]) {
			 melee_char_y += character_speed;
         }

		  if (key[KEY_LEFT] && melee_char_x >= character_speed && !character_collision[2]) {
			 melee_char_x -= character_speed;
         }

		  if (key[KEY_RIGHT] && melee_char_x <= SCREEN_W - BOUNCER_SIZE - character_speed && !character_collision[3]) {
			 melee_char_x += character_speed;
         }

         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = true;
               character_direction = KEY_UP;
               break;

            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
               character_direction = KEY_DOWN;
               break;

            case ALLEGRO_KEY_LEFT:
               key[KEY_LEFT] = true;
               character_direction = KEY_LEFT;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               character_direction = KEY_RIGHT;
               break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = false;
               break;

            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = false;
               break;

            case ALLEGRO_KEY_LEFT:
               key[KEY_LEFT] = false;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               break;

            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
         }
      }

	  //Obstacle X Character collision
	  if ((melee_char_x < obstacle_x + obstacle_w && melee_char_x > obstacle_x - obstacle_w) && melee_char_y <= obstacle_y + obstacle_h && melee_char_y > obstacle_y)
	  {
		  character_collision[0] = true;
	  }
	  else
	  {
		  character_collision[0] = false;
	  }
	  if ((melee_char_x < obstacle_x + obstacle_w && melee_char_x > obstacle_x - obstacle_w) && melee_char_y + character_size >= obstacle_y && melee_char_y < obstacle_y)
	  {
		  character_collision[1] = true;
	  }
	  else
	  {
		  character_collision[1] = false;
	  }
	  if ((melee_char_y < obstacle_y + obstacle_h && melee_char_y > obstacle_y - obstacle_h) && melee_char_x + character_size >= obstacle_x && melee_char_x < obstacle_x)
	  {
		  character_collision[3] = true;
	  }
	  else
	  {
		  character_collision[3] = false;
	  }
	  if ((melee_char_y < obstacle_y + obstacle_h && melee_char_y > obstacle_y - obstacle_h) && melee_char_x <= obstacle_x + obstacle_w && melee_char_x > obstacle_x)
	  {
		  character_collision[2] = true;
	  }
	  else
	  {
		  character_collision[2] = false;
	  }

      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;


         //This draws the map
         for (int i = 0; i < (SCREEN_W / 32); i++)
         {
             for (int j = 0; j < (SCREEN_H / 32); j++)
             {
                 al_draw_bitmap_region(terrain, 32 * map[i][j], 0, 32, 32, 32 * i, 32 * j, 0);
             }
         }
		 
		 //This draws an obstacle
		 al_draw_bitmap_region(obstacle, 0, 0, obstacle_w, obstacle_h, obstacle_x, obstacle_y, 0);

			 al_draw_bitmap_region(melee_char, character_size * 1, 0, character_size, character_size, melee_char_x, melee_char_y, 0);
			 al_draw_bitmap_region(melee_char, character_size * 2, 0, character_size, character_size, melee_char_x, melee_char_y, 0);
			 al_draw_bitmap_region(melee_char, character_size * 3, 0, character_size, character_size, melee_char_x, melee_char_y, 0);
			 al_draw_bitmap_region(melee_char, character_size * 0, 0, character_size, character_size, melee_char_x, melee_char_y, 0);

         al_flip_display();
      }
   }

   al_destroy_bitmap(melee_char);
   al_destroy_bitmap(terrain);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

   return 0;
}