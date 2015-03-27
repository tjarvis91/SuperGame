/*****************************************
* ag_scaledcontainer.cpp
*
* Functionality for AG_ScaledContainer()
*****************************************/

#ifndef ag_container_cpp
#define ag_container_cpp

#include "allegui.h"

AG_ScaledContainer::AG_ScaledContainer(AG_Widget *parent_in, float w_scale_in = 1.0, float h_scale_in = 1.0, int padding_in = 0, Alignment align_in = TOP_LEFT)
{
    parent = parent_in;
    w_scale = w_scale_in;
    h_scale = h_scale_in;
    padding = padding_in;
    w = parent->GetWidth() * w_scale_in;
    h = parent->GetHeight() * h_scale_in;
    AlignObject(align_in);
}

#endif