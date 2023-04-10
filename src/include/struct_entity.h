#ifndef __STRUCTENTITY__
#define __STRUCTENTITY__

#include "MLV/MLV_all.h"

typedef struct position
{
    int x;
    int y;
} Position;

typedef struct hitbox
{
    Position position;
    int size;
} Hitbox;

typedef struct player
{
    Position position;
    int size;
    int health;
    int speed;
    Hitbox hitbox;
} Player;

typedef struct rocket
{
    Position position;
    int size;
    int speed;
    int damage;
    int is_alive;
    Hitbox hitbox;
} Rocket;

typedef struct enemy
{
    Position position;
    int size;
    int health;
    int speed;
    int damage;
    int is_alive;
    Hitbox hitbox;
} Enemy;

#endif