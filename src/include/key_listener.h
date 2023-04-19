#ifndef __KEYLISTENER__
#define __KEYLISTENER__
#include "struct_entity.h"

void key_listener(Rocket *tab_rocket);
void rocket_available(Rocket *tab_rocket);
int get_number_rocket();
void get_tab_rocket(Rocket **tab_rocket, int size);
void set_number_rocket(int number);
void move_rocket(Rocket *tab_rocket);
void set_tab_rocket(Rocket **tab_rocket, int size);
void add_rocket(Rocket *rocket);

#endif