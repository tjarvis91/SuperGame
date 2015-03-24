/*****************************************
* ag_window.cpp
*
* Functionality for AG_Window()
*****************************************/

#ifndef ag_window_cpp
#define ag_window_cpp

#include "allegui.h"

AG_Window::AG_Window(char* title_in)
{
    game = new Game(title_in);
}

AG_Window::~AG_Window()
{
}

int AG_Window::Setup(int w, int h)
{
    if(!g.Setup(w, h))
    {
        return -1;
    }

    if(!al_install_mouse())
    {
        error("al_install_mouse() failed in main.cpp");
        return -1;
    }
}

#endif
