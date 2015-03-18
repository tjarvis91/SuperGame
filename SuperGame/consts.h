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
#define FRAMES_PER_SECOND           60
#define SCREEN_H                    480
#define SCREEN_W                    640
#define STANDARD_CHARACTER_SPEED    4.0

#define MAP_BLOCK_H                 SCREEN_H / BLOCK_SIZE
#define MAP_BLOCK_W                 SCREEN_W / BLOCK_SIZE

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
    int floor;
    bool filled;
};

struct Map
{
    MapTile block[MAP_BLOCK_W][MAP_BLOCK_H];
};

#endif