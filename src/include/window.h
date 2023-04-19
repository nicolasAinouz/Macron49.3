#ifndef __WINDOW__
#define __WINDOW__

#include "const.h"
#include "struct_entity.h"


void shoot();
void init_window(Enemy* tab_enemy_view, Rocket* tab_rocket);
int draw_window();
int clear_window();
int free_window();
void draw_enemy(Enemy enemy);
void draw_rocket(Rocket rocket);

#endif