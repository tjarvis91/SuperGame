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
#include <set>
#include <algorithm>

enum Alignment
{
    TOP_LEFT = 0,
    TOP_CENTER,
    TOP_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_CENTER,
    MIDDLE_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT,

    NUM_ALIGNMENTS
};

inline bool error(char* err_str)
{
    ALLEGRO_DISPLAY *display = NULL;
    al_show_native_message_box(display, "Error", "Error", err_str, NULL, ALLEGRO_MESSAGEBOX_ERROR);
    return false;
}

class AG_Listener
{
public:
       virtual void HandleNotify() = 0;
};


class AG_Widget
{
private:
    std::set<AG_Listener*> listeners;

protected:
    AG_Widget();
    AG_Widget *parent;
    ALLEGRO_DISPLAY * display;
    ALLEGRO_EVENT_QUEUE * event_queue;
    ALLEGRO_TIMER * timer;
    bool visible;
    int x, y, w, h;
    virtual void Notify()
    {
        std::for_each(listeners.begin(), listeners.end(), [&](AG_Listener *l) {l->HandleNotify(); });
    }

public:
    AG_Widget(AG_Widget *);
    ALLEGRO_DISPLAY * GetDisplay();
    ALLEGRO_EVENT_QUEUE * GetEventQueue();
    ALLEGRO_TIMER * GetTimer();
    int GetWidth();
    int GetHeight();
    int GetX();
    int GetY();
    virtual void AddListener(AG_Listener *l)
    {
        listeners.insert(l);
    }
    virtual void RemoveListener(AG_Listener *l)
    {
        std::set<AG_Listener *>::const_iterator iter = listeners.find(l);
        if(iter != listeners.end())
        {
            listeners.erase(iter);
        }
        else
        {
            error("Could not unregister the specified listener object as it is not registered.");
        }
    }
};

class AG_Window : public AG_Widget
{
public:
    AG_Window();
    ~AG_Window();
    boolean Setup(int, int);

};

class AG_Alignable : public AG_Widget
{
public:
    Alignment alignment;
    int padding;
    void AlignObject(Alignment);
};

class AG_Container : public AG_Alignable
{
protected:
    ALLEGRO_COLOR background;
    AG_Container();
public:
    AG_Container(AG_Widget *, int, int, int, int, int, Alignment);
    void SetBackgroundColor(ALLEGRO_COLOR);
};

class AG_ScaledContainer : public AG_Container
{
protected:
    float w_scale, h_scale;

public:
    AG_ScaledContainer(AG_Widget *, float, float, int, Alignment);
};


#endif