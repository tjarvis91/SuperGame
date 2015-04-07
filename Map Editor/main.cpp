/*****************************************
* main.cpp
*
* Main run function for Map Editor
*****************************************/

#define MAP_EDITOR_W    1000
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
    AG_MenuBar *menu = new AG_MenuBar((AG_Window *)(&g));
    AG_MenuButton *file = new AG_MenuButton(menu, "File");
    AG_MenuButton *edit = new AG_MenuButton(menu, "Edit");
    AG_MenuButton *save = new AG_MenuButton(menu, "Save");
    AG_MenuButton *load = new AG_MenuButton(menu, "Load");

    AG_Container *workArea = new AG_Container((AG_Widget *)(&g), 0, menu->GetHeight(), g.GetWidth(), g.GetHeight()-menu->GetHeight(), 0, BOTTOM_LEFT);

    AG_ScaledContainer *toolbox = new AG_ScaledContainer((AG_Widget*)workArea, 0.15, 1.0, 0, TOP_LEFT);
    AG_ScaledContainer *tileChooser = new AG_ScaledContainer((AG_Widget*)toolbox, 1.0, 0.5, 5, TOP_CENTER);
    AG_Label *tileChooserLabel = new AG_Label(tileChooser, "Tile Chooser", TOP_CENTER);
    AG_Button *tile1 = new AG_Button(tileChooser, "Click me!", 1, 0.15, 5, MIDDLE_CENTER);
    tile1->AddListener((AG_Widget *)tileChooserLabel);

    AG_ScaledContainer *tileOptions = new AG_ScaledContainer((AG_Widget*)toolbox, 1.0, 0.5, 5, BOTTOM_CENTER);
    AG_Label *tileOptionsLabel = new AG_Label(tileOptions, "Tile Options", TOP_CENTER);

    AG_ScaledContainer *mapExplorer = new AG_ScaledContainer((AG_Widget*)workArea, 0.15, 1.0, 0, TOP_RIGHT);
    AG_ScaledContainer *mapTabs = new AG_ScaledContainer((AG_Widget*)workArea, 0.7, 0.05, 0, TOP_CENTER);
    AG_ScaledContainer *layerTabs = new AG_ScaledContainer((AG_Widget *)workArea, 0.7, 0.05, 0, BOTTOM_CENTER);
    workArea->SetBackgroundColor(al_map_rgb(255,255, 255));
    toolbox->SetBackgroundColor(al_map_rgb(0, 0, 0));
    tileChooser->SetBackgroundColor(al_map_rgb(50, 50, 50));
    tileChooserLabel->SetColor(al_map_rgb(255,255,255));
    tileOptions->SetBackgroundColor(al_map_rgb(50, 50, 50));
    tileOptionsLabel->SetColor(al_map_rgb(255,255,255));

    mapExplorer->SetBackgroundColor(al_map_rgb(0, 0, 0));
    mapTabs->SetBackgroundColor(al_map_rgb(255, 255, 0));
    layerTabs->SetBackgroundColor(al_map_rgb(255, 0, 0));
    menu->Draw();
    workArea->Draw();
    toolbox->Draw();
    tileChooser->Draw();
    tileChooserLabel->Draw();
    tile1->Draw();
    tileOptions->Draw();
    tileOptionsLabel->Draw();
    mapExplorer->Draw();
    mapTabs->Draw();
    layerTabs->Draw();

    ALLEGRO_EVENT ev;
    while(true)
    {
        al_wait_for_event(g.GetEventQueue(), &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {

        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
        {
            g.Resize();
            menu->Draw();
            workArea->Draw();
            toolbox->Draw();
            tileChooser->Draw();
            tileChooserLabel->Draw();
            tileOptions->Draw();
            tileOptionsLabel->Draw();
            mapExplorer->Draw();
            mapTabs->Draw();
            layerTabs->Draw();
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
    }

    return 0;
}