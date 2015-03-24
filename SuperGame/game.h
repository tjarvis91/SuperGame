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
#include <allegui.h>
#include <iostream>
#include <fstream>
#include <string>

// Project Headers
#include "consts.h"

using namespace std;

/* Classes */
class Game : public AG_Window
{
public:
    Map map;
    char *title;
    Game(char *);
    void ParseMap(const char*);
    void Resize();
    int Setup(int, int);
    void ShutDown(){};
};

Game::Game(char *title_in)
{
    title = title_in;
    memset(&map, 0, sizeof(map));
}

void Game::ParseMap(const char *file)
{
string line;
ifstream map_file(file);

    if(!map_file.is_open())
        error("map_file.open() failed in Game.ParseMap()");

    getline(map_file, line);
    map.w = stoi(line);
    getline(map_file, line);
    map.h = stoi(line);

    //Empty space
    getline(map_file, line);

    for(int i = 0; i < map.h; i++)
    {
        getline(map_file, line);
        for(int j = 0; j < map.w; j++)
        {
            map.ground.tile[j][i].type = line[2*j]-48;
            map.ground.tile[j][i].variant = line[2*j + 1]-48;
        }
    }
    getline(map_file, line);

    for(int i = 0; i < map.h; i++)
    {
        getline(map_file, line);
        for(int j = 0; j < map.w; j++)
        {
            map.low.tile[j][i].type = line[2*j]-48;
            map.low.tile[j][i].variant = line[2*j + 1]-48;
        }
    }
    getline(map_file, line);

    for(int i = 0; i < map.h; i++)
    {
        getline(map_file, line);
        for(int j = 0; j < map.w; j++)
        {
            map.high.tile[j][i].type = line[2*j]-48;
            map.high.tile[j][i].variant = line[2*j + 1]-48;
        }
    }
    getline(map_file, line);

    for(int i = 0; i < map.h; i++)
    {
        getline(map_file, line);
        for(int j = 0; j < map.w; j++)
        {
            map.obstacle.tile[j][i].type = line[2*j]-48;
            map.obstacle.tile[j][i].variant = line[2*j + 1]-48;
        }
    }

    map_file.close();
}

void Game::Resize()
{
float screen_w, screen_h, sx, sy;
ALLEGRO_TRANSFORM trans;


    screen_w = al_get_display_width(GetDisplay());
    screen_h = al_get_display_height(GetDisplay());

    sx = screen_w / (float)SCREEN_W;
    sy = screen_h / (float)SCREEN_H;

    al_identity_transform(&trans);
    al_scale_transform(&trans, sx, sy);
    al_use_transform(&trans);
};

int Game::Setup(int w, int h)
{
boolean ret = false;

    if(!AG_Window::Setup(w, h))
    {
        error("AG_Window::Setup() failed in Game.Setup()");
    }
    al_set_window_title(GetDisplay(), title);
    return true;
}


#endif