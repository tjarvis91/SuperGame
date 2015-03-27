/*****************************************
* consts.h
*
* Constants, enums, and structs needed
* throughout the game
*****************************************/

#ifndef consts_h
#define consts_h

/* Constants */
#define BLOCK_SIZE                  32
#define SCREEN_H                    480
#define SCREEN_W                    640
#define STANDARD_CHARACTER_SPEED    4.0

#define MAP_BLOCK_H                 75
#define MAP_BLOCK_W                 100

#define MAP_BLOCK_DRAWN_H           SCREEN_H / BLOCK_SIZE //15
#define MAP_BLOCK_DRAWN_W           SCREEN_W / BLOCK_SIZE //20

#define FOLLOW_BUFFER               10
#define NUM_CHARACTERS              3

/* Enums */
enum Direction : int
{
    DOWN, UP, LEFT, RIGHT
};

/* Structs */
struct MapTile
{
    int type;
    int variant;
};

struct MapLayer
{
    MapTile tile[MAP_BLOCK_W][MAP_BLOCK_H];
};

struct Map
{
    MapLayer ground;
    MapLayer low;
    MapLayer high;
    MapLayer obstacle;
    int w;
    int h;
};

#endif