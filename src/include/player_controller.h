#ifndef _PLAYCONTROLLER_
#define _PLAYCONTROLLER_

#include "struct_entity.h"

void init_player();

int get_player_position_x();
void set_player_position_x(int x);

int get_player_position_y();
void set_player_position_y(int y);
Position get_player_position();

void set_player_health(int health);
int get_player_health();

int get_player_size();

void move_player_left();
void move_player_right();
void move_player_up();
void move_player_down();

void free_rocket(Rocket * l);

#endif