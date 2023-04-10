#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/const.h"
#include "../include/struct_entity.h"

Player player;

void init_player()
{
    player.health = 5;
    player.size = 50;
    player.speed = 30;
    player.position.x = WIDTH_FRAME / 2 - player.size;
    player.position.y = HEIGHT_FRAME - (player.size * 2);
}

Position get_player_position()
{
    return player.position;
}
int get_player_position_x()
{
    return player.position.x;
}
void set_player_position_x(int x)
{
    player.position.x = x;
}

int get_player_position_y()
{
    return player.position.y;
}
void set_player_position_y(int y)
{
    player.position.y = y;
}

void set_player_health(int health)
{
    player.health = health;
}

int get_player_health()
{
    return player.health;
}

int get_player_size()
{
    return player.size;
}
void move_player_left()
{
    if (get_player_position_x() > 0)
    {
        set_player_position_x(get_player_position_x() - player.speed);
    }
}

void move_player_right()
{
    if (get_player_position_x() < WIDTH_FRAME - get_player_size())
    {
        set_player_position_x(get_player_position_x() + player.speed);
    }
}
void move_player_up()
{
    if (get_player_position_y() > 0)
    {
        set_player_position_y(get_player_position_y() - player.speed);
    }
}
void move_player_down()
{
    if (get_player_position_y() < HEIGHT_FRAME - get_player_size())
    {
        set_player_position_y(get_player_position_y() + player.speed);
    }
}


