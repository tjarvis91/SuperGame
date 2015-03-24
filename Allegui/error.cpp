/*****************************************
* error.cpp
*
* Error function for simple output box
*****************************************/

#ifndef error_cpp
#define error_cpp

#include <allegro5\allegro_native_dialog.h>

bool error(const char* err_str)
{
    ALLEGRO_DISPLAY *display = NULL;

    al_show_native_message_box(display, "Error", "Error", err_str, NULL, ALLEGRO_MESSAGEBOX_ERROR);

    return false;
}

#endif