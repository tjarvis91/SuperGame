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

class AG_Widget
{
public:
    AG_Widget();
    AG_Widget(AG_Widget *);
    ALLEGRO_DISPLAY * GetDisplay();
    ALLEGRO_EVENT_QUEUE * GetEventQueue();
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
    int Setup(int, int);

};

bool error(const char*);

#endif