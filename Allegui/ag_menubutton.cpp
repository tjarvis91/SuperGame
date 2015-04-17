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
    label = new AG_Label(this, button_name_in, MIDDLE_CENTER);
    dropMenu = new AG_Container(this, GetX(), GetY() + GetHeight(), GetWidth(), 15, 0);
    parent_in->AddMenuButton(this);
    AddClickable(this);
}

void AG_MenuButton::Draw()
{
    if(visible)
    {
        AG_ScaledContainer::Draw();
        label->Draw();
        dropMenu->Draw();
    }
}

void AG_MenuButton::Notify()
{
    //dropMenu->SetVisible(!dropMenu->GetVisible());
}

#endif