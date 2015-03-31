/*****************************************
* ag_menubar.cpp
*
* Functionality for AG_MenuBar()
*****************************************/

#ifndef ag_menubar_cpp
#define ag_menubar_cpp

#include "allegui.h"

#define MENUBAR_HEIGHT      20;
#define MENUBAR_COLOR       {220, 220, 220, 255}

AG_MenuBar::AG_MenuBar(AG_Window *parent_in) : AG_Container((AG_Widget *)parent_in)
{
    x = 0;
    y = 0;
    w = parent_in->GetWidth();
    h = MENUBAR_HEIGHT;
    background = MENUBAR_COLOR;
}

void AG_MenuBar::AddMenuButton(AG_MenuButton *button_in)
{
    buttons.insert(button_in);
}

void AG_MenuBar::RemoveMenuButton(AG_MenuButton *button_in)
{
    buttons.erase(button_in);
}

void AG_MenuBar::Draw()
{
    al_flip_display();
    ALLEGRO_BITMAP *bkgd = al_create_bitmap(w, h);
    al_set_target_bitmap(bkgd);
    al_clear_to_color(background);
    al_set_target_bitmap(al_get_backbuffer(GetDisplay()));
    al_draw_bitmap(bkgd, GetX(), GetY(), 0);
    std::for_each(buttons.begin(), buttons.end(), [&](AG_MenuButton *l)
    {
        l->Draw();
    });
    al_flip_display();
    al_destroy_bitmap(bkgd);
}
#endif