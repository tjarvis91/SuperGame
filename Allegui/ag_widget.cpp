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
    visible = true;
}

AG_Widget::AG_Widget(AG_Widget *parent_in)
{
    parent = parent_in;
    visible = parent_in->visible;
    x = parent_in->x;
    y = parent_in->y;
    w = parent_in->w;
    h = parent_in->h;
    display = parent_in->display;
    event_queue = parent_in->event_queue;
    timer = parent_in->timer;
}

ALLEGRO_DISPLAY * AG_Widget::GetDisplay()
{
    return display;
}

ALLEGRO_EVENT_QUEUE * AG_Widget::GetEventQueue()
{
    return event_queue;
}

int AG_Widget::GetWidth()
{
    return w;
}

int AG_Widget::GetHeight()
{
    return h;
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

int AG_Widget::GetLocalX()
{
	return x;
}

int AG_Widget::GetLocalY()
{
	return y;
}

ALLEGRO_TIMER * AG_Widget::GetTimer()
{
    return timer;
}

#endif