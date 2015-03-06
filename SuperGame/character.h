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
    Map *map;
    int x, y, w, h, speed;
    Direction direction;
    Character(Map*, int, int);
    ~Character();
    bool Move(bool[4]);
    void Draw();
    void SetBitmap(const char*);

};

Character::Character(Map *map_in, int x_in, int y_in)
{
    x = x_in;
    y = y_in;
    speed = STANDARD_CHARACTER_SPEED;
    w = BLOCK_SIZE;
    h = BLOCK_SIZE;
    direction = DOWN;
    map = map_in;
    image = NULL;
}

Character::~Character()
{
    al_destroy_bitmap(image);
}

bool Character::Move(bool dir[])
{
int try_x = 0;
int try_y = 0;

    if (dir[UP] && y >= speed)
    {
        try_y = -speed;
        direction = UP;
    }

    if (dir[DOWN] && y <= SCREEN_H - BLOCK_SIZE - speed )
    {
        try_y = speed;
        direction = DOWN;
    }

    if (dir[LEFT] && x >= speed )
    {
        try_x = -speed;
        direction = LEFT;
    }

    if (dir[RIGHT] && x <= SCREEN_W - BLOCK_SIZE - speed )
    {
        try_x = speed;
        direction = RIGHT;
    }

    if (!map->block[(x + try_x) / BLOCK_SIZE][(y + try_y) / BLOCK_SIZE].filled &&
        !map->block[(x + w + try_x) / BLOCK_SIZE][(y + try_y) / BLOCK_SIZE].filled &&
        !map->block[(x + try_x) / BLOCK_SIZE][(y + h + try_y) / BLOCK_SIZE].filled &&
        !map->block[(x + w + try_x) / BLOCK_SIZE][(y + h + try_y) / BLOCK_SIZE].filled )
    {
        x += try_x;
        y += try_y;
        return true;
    }

    return false;
}

void Character::Draw()
{
    al_draw_bitmap_region(image, w * direction, 0, w, h, x, y, 0);
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