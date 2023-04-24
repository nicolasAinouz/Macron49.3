#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/const.h"
#include "../include/struct_entity.h"

Player *init_player()
{

    Player *player = malloc(sizeof(Player));
    assert(player != NULL);

    
    player->size = SIZE_PLAYER;
    Position *position = malloc(sizeof(Position));
    assert(position != NULL);
    position->x = (player->size);
    position->y = HEIGHT_FRAME  / 2 - player->size /2;
    player->position = position;
   

    player->health = 5;

    

    player->speed = 0;
    player->score = 0;
    Hitbox *hitbox = malloc(sizeof(Hitbox));
    assert(hitbox != NULL);
    hitbox->position = player->position;
    hitbox->size = player->size;
    player->hitbox = hitbox;

    return player;
}

void move_player_left(Player *player)
{
    if (player->position->x > 0)
    {
        player->position->x = player->position->x - player->speed;
    }
}

void move_player_right(Player *player)
{
    if (player->position->x < WIDTH_FRAME - player->size)
    {
        player->position->x = player->position->x + player->speed;
    }
}
void move_player_up(Player *player)
{
    if (player->position->y > 0)
    {
        player->position->y = player->position->y - player->speed;
    }
}
void move_player_down(Player *player)
{
    if (player->position->y < HEIGHT_FRAME - player->size)
    {
        player->position->y = player->position->y + player->speed;
    }
}
