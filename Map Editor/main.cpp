/*****************************************
* main.cpp
*
* Main run function for Map Editor
*****************************************/

#define MAP_EDITOR_W    1280
#define MAP_EDITOR_H    800

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
    AG_ScaledContainer *cont = new AG_ScaledContainer((AG_Widget*)(&g), 0.33, 0.33, 3, TOP_LEFT);
    AG_ScaledContainer *cont2 = new AG_ScaledContainer((AG_Widget*)(&g), 0.33, 0.33, 3, MIDDLE_LEFT);
    cont->SetBackgroundColor(al_map_rgb(0, 0, 255));
    cont2->SetBackgroundColor(al_map_rgb(0, 255, 255));
    cont->Draw();
    cont2->Draw();

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