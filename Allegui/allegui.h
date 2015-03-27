/*****************************************
* allegui.h
*
* Simple GUI functionality for Allegro
*****************************************/

#ifndef allegui_h
#define allegui_h

#define ALLEGRO_NO_MAGIC_MAIN
#define FRAMES_PER_SECOND   60

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

inline bool error(char* err_str)
{
    ALLEGRO_DISPLAY *display = NULL;
    al_show_native_message_box(display, "Error", "Error", err_str, NULL, ALLEGRO_MESSAGEBOX_ERROR);
    return false;
}

class AG_Widget
{
public:
    AG_Widget();
    AG_Widget(AG_Widget *);
    ALLEGRO_DISPLAY * GetDisplay();
    ALLEGRO_EVENT_QUEUE * GetEventQueue();
    ALLEGRO_TIMER * GetTimer();
protected:
    AG_Widget *parent;
    ALLEGRO_DISPLAY * display;
    ALLEGRO_EVENT_QUEUE * event_queue;
    ALLEGRO_TIMER * timer;
    bool visible;
    int w, h;
};

class AG_Window : public AG_Widget
{
public:
    AG_Window();
    ~AG_Window();
    boolean Setup(int, int);

};

#endif