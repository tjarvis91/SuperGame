/*****************************************
* ag_container.cpp
*
* Functionality for AG_Container()
*****************************************/

#ifndef ag_container_cpp
#define ag_container_cpp

#include "allegui.h"

AG_Container::AG_Container()
{}

AG_Container::AG_Container(AG_Widget * parent_in, int x_in = 0, int y_in = 0, int w_in = -1, int h_in = -1, int padding_in = 0, Alignment align_in = TOP_LEFT)
{
    parent = parent_in;
    x = x_in;
    y = y_in;
    w = w_in;
    h = h_in;
    padding = padding_in;
    w = w_in;
    h = h_in;

    if(w < 0)
        w = parent_in->GetWidth();
    if(h < 0)
        h = parent_in->GetHeight();

    AlignObject(align_in);
}

void AG_Container::SetBackgroundColor(ALLEGRO_COLOR color)
{
    background = color;
}

#endif