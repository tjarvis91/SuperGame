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
	AG_Container *menuContainer = new AG_Container((AG_Widget *)(&g), 0, 0, g.GetWidth(), 20, 0, TOP_LEFT);
	AG_Container *workAreaContainer = new AG_Container((AG_Widget *)(&g), 0, menuContainer->GetHeight(), g.GetWidth(), g.GetHeight()-menuContainer->GetHeight(), 0, BOTTOM_LEFT);
    AG_ScaledContainer *leftContainer = new AG_ScaledContainer((AG_Widget*)workAreaContainer, 0.15, 1.0, 0, TOP_LEFT);
    AG_ScaledContainer *rightContainer = new AG_ScaledContainer((AG_Widget*)workAreaContainer, 0.15, 1.0, 0, TOP_RIGHT);
	AG_ScaledContainer *topTabsContainer = new AG_ScaledContainer((AG_Widget*)workAreaContainer, 0.7, 0.05, 0, TOP_CENTER);
	AG_ScaledContainer *layerContainer = new AG_ScaledContainer((AG_Widget *)workAreaContainer, 0.7, 0.05, 0, BOTTOM_CENTER);
	menuContainer->SetBackgroundColor(al_map_rgb(110, 110, 110));
	workAreaContainer->SetBackgroundColor(al_map_rgb(255, 255, 255));
    leftContainer->SetBackgroundColor(al_map_rgb(0, 0, 255));
    rightContainer->SetBackgroundColor(al_map_rgb(0, 255, 255));
	topTabsContainer->SetBackgroundColor(al_map_rgb(255, 255, 0));
	layerContainer->SetBackgroundColor(al_map_rgb(255, 0, 0));
	menuContainer->Draw();
	workAreaContainer->Draw();
	leftContainer->Draw();
	rightContainer->Draw();
	topTabsContainer->Draw();
	layerContainer->Draw();


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