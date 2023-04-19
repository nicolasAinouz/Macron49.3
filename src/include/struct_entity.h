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
    int score;
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
    int is_player; //1 si tiré par le joueur
} Rocket;

typedef struct enemy
{
    Position position;
    int size;
    int health;
    int speed;
    int damage;
    int is_alive; //est en vie si = 1
    Hitbox hitbox; 
} Enemy;



#endif