/*****************************************
* main.cpp
*
* Main run function for Map Editor
*****************************************/

#define MAP_EDITOR_W    640
#define MAP_EDITOR_H    480

/* Includes */
// Libraries
#include <stdio.h>
// Project Headers
#include "allegui.h"
#include "game.h"

int main(int argc, char **argv)
{
//boolean exit, redraw = false;

    Game g = Game("Map Editor");
    if(!g.Setup(MAP_EDITOR_W, MAP_EDITOR_H))
    {
        return -1;
    }
    AG_MenuBar *menu = new AG_MenuBar((AG_Window *)(&g));
    AG_MenuButton *file = new AG_MenuButton(menu, "File");
    AG_MenuButton *edit = new AG_MenuButton(menu, "Edit");
    ALLEGRO_FONT *font = al_load_font("Fonts/arial.ttf", 18, 0);
    al_draw_text(font, al_map_rgb(255,255,255),0,0,0,"TEST");
    AG_Container *workArea = new AG_Container((AG_Widget *)(&g), 0, menu->GetHeight(), g.GetWidth(), g.GetHeight()-menu->GetHeight(), 0, BOTTOM_LEFT);
    AG_ScaledContainer *toolbox = new AG_ScaledContainer((AG_Widget*)workArea, 0.15, 1.0, 0, TOP_LEFT);
    AG_ScaledContainer *mapExplorer = new AG_ScaledContainer((AG_Widget*)workArea, 0.15, 1.0, 0, TOP_RIGHT);
    AG_ScaledContainer *mapTabs = new AG_ScaledContainer((AG_Widget*)workArea, 0.7, 0.05, 0, TOP_CENTER);
    AG_ScaledContainer *layerTabs = new AG_ScaledContainer((AG_Widget *)workArea, 0.7, 0.05, 0, BOTTOM_CENTER);
    menu->SetBackgroundColor(al_map_rgb(220, 220, 220));
    workArea->SetBackgroundColor(al_map_rgb(255, 255, 255));
    toolbox->SetBackgroundColor(al_map_rgb(0, 0, 255));
    mapExplorer->SetBackgroundColor(al_map_rgb(0, 255, 255));
    mapTabs->SetBackgroundColor(al_map_rgb(255, 255, 0));
    layerTabs->SetBackgroundColor(al_map_rgb(255, 0, 0));
    menu->Draw();
    workArea->Draw();
    toolbox->Draw();
    mapExplorer->Draw();
    mapTabs->Draw();
    layerTabs->Draw();


    while(true)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(g.GetEventQueue(), &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {

        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
        {
            g.Resize();
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
    }

    return 0;
}