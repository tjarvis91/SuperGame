/*****************************************
* ag_widget.cpp
*
* Functionality for AG_Widget()
*****************************************/

#ifndef ag_widget_cpp
#define ag_widget_cpp

#include "allegui.h"

AG_Widget::AG_Widget(AG_Window *window_in)
{
    window = window_in;
    parent = NULL;
    x = 0;
    y = 0;
}

AG_Widget::AG_Widget(AG_Widget *parent_in)
{
    parent = parent_in;
    window = parent->window;
    x = parent_in->x;
    y = parent_in->y;
    w = parent_in->w;
    h = parent_in->h;
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

#endif