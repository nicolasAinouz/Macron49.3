#ifndef _PLAYCONTROLLER_
#define _PLAYCONTROLLER_

#include "struct_entity.h"

Player * init_player();

void move_player_left(Player *player);
void move_player_right(Player *player);
void move_player_up(Player *player);
void move_player_down(Player *player);
void active_power_up(Game *game);

#endif