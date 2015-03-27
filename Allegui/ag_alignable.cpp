/*****************************************
* ag_alignable.cpp
*
* Functionality for AG_Alignable()
*****************************************/

#ifndef ag_container_cpp
#define ag_container_cpp

#include "allegui.h"

void AG_Alignable::AlignObject(Alignment align_in)
{
    alignment = align_in;

    switch(alignment)
    {
        case TOP_LEFT:
            x = padding;
            y = padding;
            break;

        case TOP_CENTER:
            x = max(padding, (parent->GetWidth() - w) * 0.5 );
            y = padding;
            break;

        case TOP_RIGHT:
            x = parent->GetWidth() -  w - padding;
            y = padding;
            break;

        case MIDDLE_LEFT:
            x = padding;
            y = max(padding, (parent->GetHeight() - h) * 0.5);
            break;

        case MIDDLE_CENTER:
            x = max(padding, (parent->GetWidth() - w) * 0.5 );
            y = max(padding, (parent->GetHeight() - h) * 0.5);
            break;

        case MIDDLE_RIGHT:
            x = parent->GetWidth() -  w - padding;
            y = max(padding, (parent->GetHeight() - h) * 0.5);
            break;

        case BOTTOM_LEFT:
            x = padding;
            y = parent->GetHeight() - h - padding;
            break;

        case BOTTOM_CENTER:
            x = max(padding, (parent->GetWidth() - w) * 0.5 );
            y = parent->GetHeight() - h - padding;
            break;

        case BOTTOM_RIGHT:
            x = parent->GetWidth() -  w - padding;
            y = parent->GetHeight() - h - padding;
            break;
    }
}

#endif