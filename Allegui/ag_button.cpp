/*****************************************
* ag_button.cpp
*
* Functionality for AG_Button()
*****************************************/

#ifndef ag_button_cpp
#define ag_button_cpp

#include "allegui.h"

#define STANDARD_BUTTON_WIDTH       100
#define STANDARD_BUTTON_HEIGHT      25

AG_Button::AG_Button(AG_Container *parent_in, char *button_text_in, float w_scale_in, float h_scale_in, int padding_in, Alignment align_in) : AG_Alignable(parent_in)
{
    padding = padding_in;
    alignment = align_in;
    buttonBack = new AG_ScaledContainer(parent_in, w_scale_in, h_scale_in, padding_in, align_in);
    label = new AG_Label(buttonBack, button_text_in, MIDDLE_CENTER);
    buttonBack->SetBackgroundColor(al_map_rgb(255,255,255));
    AddClickable(this);
    AlignObject(alignment);
}

void AG_Button::Draw()
{
    buttonBack->Draw();
    label->Draw();
}

void AG_Button::Notify()
{

}

#endif