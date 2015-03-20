/*****************************************
* game.h
*
* Game class structure
*****************************************/

#ifndef game_h
#define game_h

/* Includes */
// Libraries
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>
#include <fstream>
#include <string>
// Project Headers
#include "consts.h"
#include "error.h"

using namespace std;

/* Classes */
class Game
{
public:
    ALLEGRO_DISPLAY     *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER       *timer;
    Map map;
    char *title;
    Game(char *);
    void ParseMap(const char*);
    int Setup(int, int);
    void ShutDown(){};
};

Game::Game(char *title_in)
{
    timer = NULL;
    display = NULL;
    event_queue = NULL;
    title = title_in;
    memset(&map, 0, sizeof(map));
}

void Game::ParseMap(const char *file)
{
string line;
ifstream map_file(file);

    if(!map_file.is_open())
        error("map_file.open() failed in Game.ParseMap()");

    for(int i = 0; i < MAP_BLOCK_H; i++)
    {
        getline(map_file, line);
        for(int j = 0; j < MAP_BLOCK_W; j++)
        {
            map.ground.tile[j][i].type = line[2*j]-48;
            map.ground.tile[j][i].variant = line[2*j + 1]-48;
        }
    }
    getline(map_file, line);

    for(int i = 0; i < MAP_BLOCK_H; i++)
    {
        getline(map_file, line);
        for(int j = 0; j < MAP_BLOCK_W; j++)
        {
            map.low.tile[j][i].type = line[2*j]-48;
            map.low.tile[j][i].variant = line[2*j + 1]-48;
        }
    }
    getline(map_file, line);

    for(int i = 0; i < MAP_BLOCK_H; i++)
    {
        getline(map_file, line);
        for(int j = 0; j < MAP_BLOCK_W; j++)
        {
            map.high.tile[j][i].type = line[2*j]-48;
            map.high.tile[j][i].variant = line[2*j + 1]-48;
        }
    }
    getline(map_file, line);

    for(int i = 0; i < MAP_BLOCK_H; i++)
    {
        getline(map_file, line);
        for(int j = 0; j < MAP_BLOCK_W; j++)
        {
            map.obstacle.tile[j][i].type = line[2*j]-48;
            map.obstacle.tile[j][i].variant = line[2*j + 1]-48;
        }
    }
    getline(map_file, line);

    map_file.close();
}

int Game::Setup(int w, int h)
{
    if(!al_init())
    {
        return error("al_init() failed in Game.Setup()");
    }

    if(!al_init_image_addon())
    {
        return error("al_init_image_addon() failed in Game.Setup()");
    }

    if(!al_install_keyboard())
    {
        return error("al_install_keyboard() failed in Game.Setup()");
    }

    timer = al_create_timer(1.0 / FRAMES_PER_SECOND);
    if(!timer)
    {
        return error("al_create_timer() failed in Game.Setup()");
    }

    display = al_create_display(w, h);
    if(!display)
    {
        return error("al_create_display() failed in Game.Setup()");
    }

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        return error("al_create_event_queue() failed in Game.Setup()");
    }

    al_set_window_title(display, title);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    return true;
}


#endif