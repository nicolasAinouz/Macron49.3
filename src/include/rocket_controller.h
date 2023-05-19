#ifndef __ROCKET__
#define __ROCKET__
#include "struct_entity.h"

int get_number_rocket();
void get_tab_rocket(Rocket **tab_rocket, int size);
void set_number_rocket(int number);
void move_rocket(Game *game);
void set_tab_rocket(Rocket **tab_rocket, int size);
void add_rocket(Rocket *rocket);
void init_tab_rocket(Rocket **tab_rocket);
void rocket_available(Game *game);

#endif