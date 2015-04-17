/*****************************************
* ag_window.cpp
*
* Functionality for AG_Window()
*****************************************/

#ifndef ag_window_cpp
#define ag_window_cpp

#include "allegui.h"

static void *Listen(ALLEGRO_THREAD *listen, void *arg);

AG_Window::AG_Window() : AG_Widget()
{
    w = 0;
    h = 0;
    listen = NULL;
    visible = true;
}

AG_Window::~AG_Window()
{
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}

void AG_Window::AddClickable(AG_Widget *add)
{
std::vector<AG_Widget *>::iterator it = clickables.begin();
clickables.insert(it, add);
}

void AG_Window::RemoveClickable(AG_Widget *remove)
{
    for(unsigned int i = 0; i < clickables.size(); i++)
    {
        if(clickables.at(i) == remove)
            {
            clickables.erase(clickables.begin() + i);
            return;
            }
    }

    error("Could not unregister the specified clickable object as it is not registered.");
}

void AG_Window::Press(int x_press, int y_press)
{
    std::for_each(clickables.begin(), clickables.end(), [&](AG_Widget *l)
    {
        if(x_press > l->GetX() && x_press < l->GetX() + l->GetWidth()
        && y_press > l->GetY() && y_press < l->GetY() + l->GetHeight())
        {
            l->Notify();
        }
    });
}

void AG_Window::Resize()
{
float screen_w, screen_h, sx, sy;
ALLEGRO_TRANSFORM trans;


    screen_w = al_get_display_width(display);
    screen_h = al_get_display_height(display);

    sx = screen_w / (float)w;
    sy = screen_h / (float)h;

    al_identity_transform(&trans);
    al_scale_transform(&trans, sx, sy);
    al_use_transform(&trans);
}

boolean AG_Window::Setup(int w_in, int h_in)
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
    w = w_in;
    h = h_in;
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

    al_init_font_addon();
    al_init_ttf_addon();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    listen = al_create_thread(Listen, this);
    al_start_thread(listen);

    return true;
}

static void *Listen(ALLEGRO_THREAD *listen, void *arg)
{
    AG_Window *window = (AG_Window *)arg;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT ev;
    if(!window)
        return NULL;

    queue = window->GetEventQueue();

    while(!al_get_thread_should_stop(listen))
    {
        al_peek_next_event(queue, &ev);
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            window->Press(ev.mouse.x, ev.mouse.y);
        }
    }
    return NULL;
}


#endif
