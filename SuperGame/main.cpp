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
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
enum wasd_keys : int {
    W_KEY = KEY_UP,
    A_KEY = KEY_LEFT,
    S_KEY = KEY_DOWN,
    D_KEY = KEY_RIGHT
};

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *melee_char = NULL;
   ALLEGRO_BITMAP *terrain = NULL;
   float melee_char_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float melee_char_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
   int character_direction = 0;
   int map [SCREEN_W/32][SCREEN_H/32];

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



   al_convert_mask_to_alpha(melee_char, al_map_rgb(255, 0, 255));

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

   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

      if(ev.type == ALLEGRO_EVENT_TIMER) {
         if(key[KEY_UP] && melee_char_y >= 4.0) {
            melee_char_y -= 4.0;
         }

         if(key[KEY_DOWN] && melee_char_y <= SCREEN_H - BOUNCER_SIZE - 4.0) {
            melee_char_y += 4.0;
         }

         if(key[KEY_LEFT] && melee_char_x >= 4.0) {
            melee_char_x -= 4.0;
         }

         if(key[KEY_RIGHT] && melee_char_x <= SCREEN_W - BOUNCER_SIZE - 4.0) {
            melee_char_x += 4.0;
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
			   character_direction = 1;
               break;

            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
			   character_direction = 0;
               break;

            case ALLEGRO_KEY_LEFT:
               key[KEY_LEFT] = true;
			   character_direction = 2;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
			   character_direction = 3;
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

		 //This draws the side of the character that corresponds with the direction of his movement
		 if (character_direction == 1)
		 {
         al_draw_bitmap(melee_char, melee_char_x, melee_char_y, 0);
		 }
		 else if (character_direction == 2)
		 {
			 al_draw_bitmap_region(melee_char, 64, 0, 32, 32, melee_char_x, melee_char_y, 0);
		 }
		 else if (character_direction == 3)
		 {
			 al_draw_bitmap_region(melee_char, 96, 0, 32, 32, melee_char_x, melee_char_y, 0);
		 }
		 else
		 {
			 al_draw_bitmap_region(melee_char, 0, 0, 32, 32, melee_char_x, melee_char_y, 0);
		 }

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