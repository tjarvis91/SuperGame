/*****************************************
* ag_menubar.cpp
*
* Functionality for AG_MenuBar()
*****************************************/

#ifndef ag_menubar_cpp
#define ag_menubar_cpp

#include "allegui.h"

#define MENUBAR_HEIGHT      25;
#define MENUBAR_COLOR       {110, 110, 110, 0}

AG_MenuBar::AG_MenuBar(AG_Window *parent_in) : AG_Container((AG_Widget *)parent_in)
{
    x = 0;
    y = 0;
    w = parent_in->GetWidth();
    h = MENUBAR_HEIGHT;
    background = MENUBAR_COLOR;
    buttonCount = 0;
}

void AG_MenuBar::AddMenuButton(AG_MenuButton *button_in)
{
    if(buttonCount < AG_MAX_BUTTONS)
    {
        if(buttonCount > 0)
            button_in->x = buttons[buttonCount-1]->GetX() + buttons[buttonCount-1]->GetWidth();
        buttons[buttonCount] = button_in;
        AlignObject(alignment);
        buttonCount++;
    }
    else
    {
        error("AddMenuButton() failed in AG_MenuBar.cpp.  Cannot hold any more buttons!");
    }
}

void AG_MenuBar::RemoveMenuButton(AG_MenuButton *button_in)
{
    //buttons.erase(button_in);
}

void AG_MenuBar::Draw()
{
    al_flip_display();
    ALLEGRO_BITMAP *bkgd = al_create_bitmap(w, h);
    al_set_target_bitmap(bkgd);
    al_clear_to_color(background);
    al_set_target_bitmap(al_get_backbuffer(GetDisplay()));
    al_draw_bitmap(bkgd, GetX(), GetY(), 0);
    al_flip_display();
    al_destroy_bitmap(bkgd);

    for(int i = 0; i < buttonCount; i++)
    {
        buttons[i]->Draw();
    }
}
#endif