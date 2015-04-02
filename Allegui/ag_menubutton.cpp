/*****************************************
* ag_menubutton.cpp
*
* Functionality for AG_MenuButton()
*****************************************/

#ifndef ag_menubutton_cpp
#define ag_menubutton_cpp

#include "allegui.h"

#define MENUBAR_W_SCALE     0.1

AG_MenuButton::AG_MenuButton(AG_MenuBar *parent_in, char *button_name_in) :  AG_ScaledContainer((AG_Widget *)parent_in, MENUBAR_W_SCALE, 1.0, 2, MIDDLE_LEFT)
{
    label = new AG_Label(this, button_name_in);
    parent_in->AddMenuButton(this);
}

void AG_MenuButton::Draw()
{
    AG_ScaledContainer::Draw();
    label->AG_Label::Draw();
}

#endif