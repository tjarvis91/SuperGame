/*****************************************
* ag_container.cpp
*
* Functionality for AG_Container()
*****************************************/

#ifndef ag_container_cpp
#define ag_container_cpp

#include "allegui.h"

AG_Container::AG_Container(AG_Widget * parent_in) : AG_Alignable(parent_in)
{}

AG_Container::AG_Container(AG_Widget * parent_in, int x_in, int y_in, int w_in = -1, int h_in = -1, int padding_in = 0, Alignment align_in = TOP_LEFT) : AG_Alignable(parent_in)
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

void AG_Container::Draw()
{
    ALLEGRO_BITMAP *bkgd = al_create_bitmap(w, h);
    al_set_target_bitmap(bkgd);
    al_clear_to_color(al_map_rgb(0, 255, 255));
    al_set_target_bitmap(al_get_backbuffer(GetDisplay()));
    al_draw_bitmap(bkgd, 0, 0, 0);
    al_flip_display();
    al_destroy_bitmap(bkgd);
}

#endif