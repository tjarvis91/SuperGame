/*****************************************
* allegui.h
*
* Simple GUI functionality for Allegro
*****************************************/

#ifndef allegui_h
#define allegui_h

#define ALLEGRO_NO_MAGIC_MAIN
#define AG_MAX_BUTTONS      12
#define FRAMES_PER_SECOND   60

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <set>
#include <vector>
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

/* Class Declarations */
class AG_Alignable;
class AG_Container;
class AG_Listener;
class AG_MenuBar;
class AG_MenuButton;
class AG_ScaledContainer;
class AG_Widget;
class AG_Window;

/* Class Definitions */
//AG_Listener
class AG_Listener
{
    public:
        virtual void HandleNotify() = 0;
};

//AG_Widget
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
        AG_Widget(AG_Widget *parent);
        ALLEGRO_DISPLAY * GetDisplay();
        ALLEGRO_EVENT_QUEUE * GetEventQueue();
        ALLEGRO_TIMER * GetTimer();
        int GetWidth();
        int GetHeight();
        int GetX();
        int GetY();
        int GetLocalX();
        int GetLocalY();
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

//AG_Window
class AG_Window : public AG_Widget
{
    public:
        AG_Window();
        ~AG_Window();
        void Resize();
        boolean Setup(int w, int h);

};

//AG_Alignable
class AG_Alignable : public AG_Widget
{
    protected:
        AG_Alignable(AG_Widget *parent);
    public:
        Alignment alignment;
        int padding;
        void AlignObject(Alignment alignment);
};

//AG_Container
class AG_Container : public AG_Alignable
{
    protected:
        ALLEGRO_COLOR background;
        AG_Container(AG_Widget *parent);
    public:
        AG_Container(AG_Widget *parent, int x, int y, int w, int h, int padding, Alignment alignment);
        void SetBackgroundColor(ALLEGRO_COLOR color);
        virtual void Draw();
};

//AG_Label
class AG_Label : public AG_Alignable
{
    protected:
        char *labelName;
        ALLEGRO_FONT *font;
        ALLEGRO_COLOR color;
    public:
        AG_Label(AG_Container *parent, char *label_name, Alignment align_in=TOP_LEFT);
        void Draw();
        void SetColor(ALLEGRO_COLOR color);
};

//AG_ScaledContainer
class AG_ScaledContainer : public AG_Container
{
    protected:
        float w_scale, h_scale;
        ALLEGRO_COLOR background;
    public:
        AG_ScaledContainer(AG_Widget *parent, float w_scale, float h_scale, int padding, Alignment alignment);
};

//AG_MenuButton
class AG_MenuButton : AG_ScaledContainer
{
    friend class AG_MenuBar;
    protected:
        void Draw();
        AG_Label *label;
    public:
        AG_MenuButton(AG_MenuBar *parent, char *button_name);
};

//AG_MenuBar
class AG_MenuBar : public AG_Container
{
    protected:
        AG_MenuButton *buttons[AG_MAX_BUTTONS];
        int buttonCount;
    public:
        AG_MenuBar(AG_Window *parent);
        void AddMenuButton(AG_MenuButton *button);
        void RemoveMenuButton(AG_MenuButton *button);
        void Draw();
};

#endif