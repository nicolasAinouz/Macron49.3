#ifndef __ROCKET__
#define __ROCKET__
#include "struct_entity.h"


void move_rocket(Game *game);
void init_tab_rocket(Rocket **tab_rocket);
void rocket_available(Game *game);
void shoot(Game *game, Enemy *enemy, int is_special, int is_player);

#endif