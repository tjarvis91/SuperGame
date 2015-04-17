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
class AG_MenuBar;
class AG_MenuButton;
class AG_ScaledContainer;
class AG_Widget;
class AG_Window;

/* Class Definitions */

//AG_Widget
class AG_Widget
{
    private:
        std::set<AG_Widget *> listeners;

    protected:
        AG_Widget();
        AG_Widget *parent;
        ALLEGRO_DISPLAY * display;
        ALLEGRO_EVENT_QUEUE * event_queue;
        ALLEGRO_TIMER * timer;
        bool visible;
        int x, y, w, h;

    public:
        AG_Widget(AG_Widget *parent);
        virtual void AddClickable(AG_Widget *add);
        virtual void RemoveClickable(AG_Widget *remove);
        ALLEGRO_DISPLAY * GetDisplay();
        ALLEGRO_EVENT_QUEUE * GetEventQueue();
        ALLEGRO_TIMER * GetTimer();
        int GetWidth();
        int GetHeight();
        int GetX();
        int GetY();
        int GetLocalX();
        int GetLocalY();
        bool GetVisible();
        void SetVisible(bool visible_in);
        virtual void HandleNotify(){};
        virtual void Notify()
        {
            std::for_each(listeners.begin(), listeners.end(), [&](AG_Widget *l) {l->HandleNotify(); });
        }
        virtual void AddListener(AG_Widget *l)
        {
            AddClickable(this);
            listeners.insert(l);
        }
        virtual void RemoveListener(AG_Widget *l)
        {
            std::set<AG_Widget *>::const_iterator iter = listeners.find(l);
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
    private:
        ALLEGRO_THREAD *listen;
    public:
        AG_Window();
        ~AG_Window();
        std::vector<AG_Widget *> clickables;
        void AddClickable(AG_Widget *add);
        void RemoveClickable(AG_Widget *remove);
        void Press(int x, int y);
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
        AG_Container(AG_Widget *parent, int x, int y, int w, int h, int padding);
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

//AG_Button
class AG_Button : public AG_Alignable
{
    protected:
        AG_Label *label;
        AG_Container *buttonBack;
    public:
        AG_Button(AG_Container *parent, char *button_text, float w_scale = 1.0, float h_scale = 1.0, int padding = 0, Alignment align_in=TOP_LEFT);
        void Draw();
        void Notify();
};

//AG_MenuButton
class AG_MenuButton : AG_ScaledContainer
{
    friend class AG_MenuBar;
    protected:
        void Draw();
        AG_Label *label;
        AG_Container *dropMenu;
    public:
        AG_MenuButton(AG_MenuBar *parent, char *button_name);
        void Notify();
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