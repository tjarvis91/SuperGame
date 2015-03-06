/*****************************************
* game.h
*
* Game class structure
*****************************************/

#ifndef game_h
#define game_h

/* Includes */
// Libraries
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
// Project Headers
#include "consts.h"
#include "error.h"

/* Classes */
class Game
{
public:
    ALLEGRO_DISPLAY     *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER       *timer;
    Game();
    int Setup();
    void ShutDown(){};
};

Game::Game()
{
    timer = NULL;
    display = NULL;
    event_queue = NULL;
}

int Game::Setup()
{
    if(!al_init())
    {
        return error("al_init() failed in main_setup()");
    }

    if(!al_init_image_addon())
    {
        return error("al_init_image_addon() failed in main_setup()");
    }

    if(!al_install_keyboard())
    {
        return error("al_install_keyboard() failed in main_setup()");
    }

    timer = al_create_timer(1.0 / FRAMES_PER_SECOND);
    if(!timer)
    {
        return error("al_create_timer() failed in main()");
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        return error("al_create_display() failed in main()");
    }

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        return error("al_create_event_queue() failed in main()");
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    return true;
}


#endif