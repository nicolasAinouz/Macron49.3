#ifndef __WINDOW__
#define __WINDOW__

#include "const.h"
#include "struct_entity.h"


void shoot();
void init_window();
int draw_window(Player *player, int scale);
int clear_window();
int free_window();
void draw_enemy(Enemy *enemy);
void draw_rocket(Rocket *rocket);
void draw_explosion(int x, int y);

#endif