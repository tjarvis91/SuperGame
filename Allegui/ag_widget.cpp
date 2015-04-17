/*****************************************
* ag_widget.cpp
*
* Functionality for AG_Widget()
*****************************************/

#ifndef ag_widget_cpp
#define ag_widget_cpp

#include "allegui.h"

AG_Widget::AG_Widget()
{
    parent = NULL;
    x = 0;
    y = 0;
}

AG_Widget::AG_Widget(AG_Widget *parent_in)
{
    parent = parent_in;
    x = parent_in->x;
    y = parent_in->y;
    w = parent_in->w;
    h = parent_in->h;
    display = parent_in->display;
    event_queue = parent_in->event_queue;
    timer = parent_in->timer;
}

AG_Widget::~AG_Widget()
{
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}

void AG_Widget::AddClickable(AG_Widget *add)
{
    parent->AddClickable(add);
}

void AG_Widget::RemoveClickable(AG_Widget *remove)
{
    parent->RemoveClickable(remove);
}

int AG_Widget::GetX()
{
    if (parent)
        return x + parent->GetX();
    else
        return x;
}

int AG_Widget::GetY()
{
    if (parent)
        return y + parent->GetY();
    else
        return y;
}

int AG_Widget::GetWidth()
{
    return w;
}

int AG_Widget::GetHeight()
{
    return h;
}

int AG_Widget::GetLocalX()
{
    return x;
}

int AG_Widget::GetLocalY()
{
    return y;
}

ALLEGRO_DISPLAY * AG_Widget::GetDisplay()
{
    return display;
}

ALLEGRO_EVENT_QUEUE * AG_Widget::GetEventQueue()
{
    return event_queue;
}

ALLEGRO_TIMER * AG_Widget::GetTimer()
{
    return timer;
}

#endif