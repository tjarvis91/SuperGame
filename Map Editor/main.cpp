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
#include "../SuperGame/bitmaps.h"
#include "../SuperGame/game.h"

int main(int argc, char **argv)
{
boolean exit = false;

    Game g = Game("Map Editor");
    if(!g.Setup())
    {
        return -1;
    }

    if(!al_install_mouse())
    {
        error("al_install_mouse() failed in main.cpp");
        return -1;
    }

    while(true)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(g.event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {

        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

    }

    return 0;
}