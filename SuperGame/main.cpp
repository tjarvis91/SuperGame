#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
 
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
   ALLEGRO_BITMAP *bouncer = NULL;
   ALLEGRO_BITMAP *terrain = NULL;
   float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
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
      return -4;
   }
   /*
   bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   
   if(!bouncer) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -5;
   }
   */
   //FOR SOME STUPID REASON, Allegro could not find the image file unless it was in the same folder as the
   //	executable, regardless of what file paths I put in the code. I know there is a fix for this, but I
   //	am not fucking with it right now. Far too angry.
   bouncer = al_load_bitmap("MeleeChar.png");

   terrain = al_load_bitmap("grassy.png");

   if (!bouncer) {
	   al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
		   NULL, ALLEGRO_MESSAGEBOX_ERROR);
	   al_destroy_display(display);
	   al_destroy_timer(timer);
	   return -5;
   }

   //dat magic pink
   al_convert_mask_to_alpha(bouncer, al_map_rgb(255, 0, 255));
   
 /*
   al_set_target_bitmap(bouncer);
 
   al_clear_to_color(al_map_rgb(255, 0, 255));
 */
   
   al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(bouncer);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -6;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source());
 
   //al_clear_to_color(al_map_rgb(0,0,0));
 
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
         if(key[KEY_UP] && bouncer_y >= 4.0) {
            bouncer_y -= 4.0;
         }
 
         if(key[KEY_DOWN] && bouncer_y <= SCREEN_H - BOUNCER_SIZE - 4.0) {
            bouncer_y += 4.0;
         }
 
         if(key[KEY_LEFT] && bouncer_x >= 4.0) {
            bouncer_x -= 4.0;
         }
 
         if(key[KEY_RIGHT] && bouncer_x <= SCREEN_W - BOUNCER_SIZE - 4.0) {
            bouncer_x += 4.0;
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
 
        // al_clear_to_color(al_map_rgb(0,0,0));

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
			 al_draw_bitmap_region(bouncer, 32, 0, 32, 32, bouncer_x, bouncer_y, 0);
		 }
		 else if (character_direction == 2)
		 {
			 al_draw_bitmap_region(bouncer, 64, 0, 32, 32, bouncer_x, bouncer_y, 0);
		 }
		 else if (character_direction == 3)
		 {
			 al_draw_bitmap_region(bouncer, 96, 0, 32, 32, bouncer_x, bouncer_y, 0);
		 }
		 else
		 {
			 al_draw_bitmap_region(bouncer, 0, 0, 32, 32, bouncer_x, bouncer_y, 0);
		 }

         al_flip_display();
      }
   }
 
   al_destroy_bitmap(bouncer);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}