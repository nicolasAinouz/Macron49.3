#ifndef __STRUCTENTITY__
#define __STRUCTENTITY__

#include "MLV/MLV_all.h"

typedef struct position
{
    int x;
    int y;
} Position;

typedef struct player
{
    Position position;
    int size;
    int health;
    int speed;
} Player;

typedef struct rocket
{
    Position position;
    int size;
    int speed;

} Rocket;

#endif