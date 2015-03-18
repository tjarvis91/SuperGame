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
    int x, y, follow_x, follow_y, w, h, speed;
    Direction direction;
    Character(Map*, int, int);
    ~Character();
    void Draw();
    void Follow(int x, int y);
    bool Move(bool[4]);
    void SetBitmap(const char*);

private:
    int follow_buffer_x[FOLLOW_BUFFER], follow_buffer_y[FOLLOW_BUFFER];
    void UpdateFollowBuffer(int, int);
};

Character::Character(Map *map_in, int x_in, int y_in)
{
    x = x_in;
    y = y_in;
    follow_x = 0;
    follow_y = 0;
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

void Character::Draw()
{
    al_draw_bitmap_region(image, w * direction, 0, w, h, x, y, 0);
}

void Character::Follow(int x, int y)
{
bool dir[] = {false, false, false, false};

if(x<0) dir[LEFT]  = true;
if(x>0) dir[RIGHT] = true;
if(y<0) dir[UP]    = true;
if(y>0) dir[DOWN]  = true;
Move(dir);
}

bool Character::Move(bool dir[])
{
boolean moved = false;
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

    if (map->obstacle.tile[(x + try_x)     / BLOCK_SIZE][(y + try_y)     / BLOCK_SIZE] == 0 &&
        map->obstacle.tile[(x + try_x + w) / BLOCK_SIZE][(y + try_y)     / BLOCK_SIZE] == 0 &&
        map->obstacle.tile[(x + try_x)     / BLOCK_SIZE][(y + try_y + h) / BLOCK_SIZE] == 0 &&
        map->obstacle.tile[(x + try_x + w) / BLOCK_SIZE][(y + try_y + h) / BLOCK_SIZE] == 0 )
    {
        x += try_x;
        y += try_y;
        UpdateFollowBuffer(try_x, try_y);
        moved = true;
    }

    return moved;
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

void Character::UpdateFollowBuffer(int new_x, int new_y)
{
int i;

    for(i = 0; i < FOLLOW_BUFFER - 1; i++)
    {
        follow_buffer_x[i] = follow_buffer_x[i+1];
        follow_buffer_y[i] = follow_buffer_y[i+1];
    }
    follow_buffer_x[i] = new_x;
    follow_buffer_y[i] = new_y;
    follow_x = follow_buffer_x[0];
    follow_y = follow_buffer_y[0];
}

#endif