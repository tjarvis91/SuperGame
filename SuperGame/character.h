/*****************************************
* character.h
*
* Character class structure
*****************************************/

#ifndef character_h
#define character_h

#include "game.h"

class Character
{
public:
    ALLEGRO_BITMAP *image;
    int x, y, w, h, speed;
    direction dir;
    Character(int, int);
    ~Character();
    bool Move(int, int);
    void Draw();
    void SetBitmap(const char*);

};

Character::Character(int x_in, int y_in)
{
    x = x_in;
    y = y_in;
    speed = STANDARD_CHARACTER_SPEED;
    w = BLOCK_SIZE;
    h = BLOCK_SIZE;
    dir = DOWN;
    image = NULL;
}

Character::~Character()
{
    al_destroy_bitmap(image);
}

void Character::Draw()
{
    al_draw_bitmap_region(image, w * dir, 0, w, h, x, y, 0);
}

void Character::SetBitmap(const char* file)
{
    image = al_load_bitmap(file);
    if(!image)
    {
        error("al_load_bitmap() failed in SetBitmap()");
        return;
    }

    al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));
    return;
}

#endif