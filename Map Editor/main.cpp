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