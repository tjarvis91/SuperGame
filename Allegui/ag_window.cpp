/*****************************************
* ag_window.cpp
*
* Functionality for AG_Window()
*****************************************/

#ifndef ag_window_cpp
#define ag_window_cpp

#include "allegui.h"

AG_Window::AG_Window()
{
}

AG_Window::~AG_Window()
{
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}

boolean AG_Window::Setup(int w, int h)
{
    if(!al_init())
    {
        return error("al_init() failed in AG_Window.Setup()");
    }

    if(!al_init_image_addon())
    {
        return error("al_init_image_addon() failed in AG_Window.Setup()");
    }

    if(!al_install_keyboard())
    {
        return error("al_install_keyboard() failed in AG_Window.Setup()");
    }

    if(!al_install_mouse())
    {
        return error("al_install_mouse() failed in AG_Window.Setup()");
    }

    timer = al_create_timer(1.0 / FRAMES_PER_SECOND);
    if(!timer)
    {
        return error("al_create_timer() failed in AG_Window.Setup()");
    }

    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(w, h);
    if(!display)
    {
        return error("al_create_display() failed in AG_Window.Setup()");
    }

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        return error("al_create_event_queue() failed in AG_Window.Setup()");
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    return true;
}

#endif
