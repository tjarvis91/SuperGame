/*****************************************
* error.h
*
* Header file for error.cpp
*****************************************/

#ifndef error_h
#define error_h

bool error(const char* err_str)
{
    ALLEGRO_DISPLAY *display = NULL;

    al_show_native_message_box(display, "Error", "Error", err_str, NULL, ALLEGRO_MESSAGEBOX_ERROR);

    return false;
}

#endif