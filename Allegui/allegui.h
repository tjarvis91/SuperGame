/*****************************************
* allegui.h
*
* Simple GUI functionality for Allegro
*****************************************/

#ifndef allegui_h
#define allegui_h

#include "game.h"

class AG_Widget
{
public:
    AG_Widget();
    AG_Widget(AG_Widget *);
protected:
    AG_Widget *parent;
    bool visible;
    int w, h;
};

class AG_Window : AG_Widget
{
public:
    Game *game;
    AG_Window(char *);
    ~AG_Window();
    int Setup(int, int);

};


#endif