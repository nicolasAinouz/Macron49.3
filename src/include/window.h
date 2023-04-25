#ifndef __WINDOW__
#define __WINDOW__

#include <MLV/MLV_all.h>
#include "const.h"
#include "struct_entity.h"


void shoot();
void init_window(Game *game);
int draw_window(Player *player, int scale, MLV_Image *img_background, MLV_Image *img_player);
int clear_window();
int free_window();
void draw_enemy(Enemy *enemy, MLV_Image *img_enemy);
void draw_rocket(Rocket *rocket, MLV_Image *img_rocket);
void draw_explosion(int x, int y, MLV_Image *img_explosion);
void draw_enemy_health(Enemy *enemy);

#endif