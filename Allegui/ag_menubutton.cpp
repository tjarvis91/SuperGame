/*****************************************
* ag_menubutton.cpp
*
* Functionality for AG_MenuButton()
*****************************************/

#ifndef ag_menubutton_cpp
#define ag_menubutton_cpp

#include "allegui.h"

#define MENUBAR_W_SCALE     0.1

AG_MenuButton::AG_MenuButton(AG_MenuBar *parent_in, char *button_name_in) :  AG_Button(parent_in, button_name_in)
{
    parent_in->AddMenuButton(this);
}


#endif