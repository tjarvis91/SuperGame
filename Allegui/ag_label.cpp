/*****************************************
* ag_label.cpp
*
* Functionality for AG_Label()
*****************************************/

#ifndef ag_menubutton_cpp
#define ag_menubutton_cpp

#include "allegui.h"

AG_Label::AG_Label(AG_Container *parent_in, char *label_name_in) : AG_Alignable(parent_in)
{
    labelName = label_name_in;
    font = al_load_font("Fonts/arial.ttf", 14, 0);
    color = al_map_rgb(0, 0, 0);
    alignment = TOP_LEFT;
    w = al_get_text_width(font, label_name_in);
    h = font->height;
}

void AG_Label::Draw()
{
    al_flip_display();
    al_draw_text(font, color, GetX(), GetY(), 0, labelName);
    al_flip_display();
}

#endif