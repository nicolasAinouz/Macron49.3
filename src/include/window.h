#ifndef __WINDOW__
#define __WINDOW__

#include <MLV/MLV_all.h>
#include "const.h"
#include "struct_entity.h"

void shoot();
void init_window(Game *game);
void draw_window(Game *game);
int clear_window();
int free_window();
void draw_enemy(Enemy *enemy, MLV_Image *img_enemy);
void draw_rocket(Rocket *rocket, MLV_Image *img_rocket);
void draw_explosion(int x, int y, MLV_Image *img_explosion);
void draw_enemy_health(Enemy *enemy);
void draw_powerup(Game *game);
void draw_power_up_dbz(Game *game);
void draw_powerup(Game *game);
void draw_player(Game *game);
void draw_health(Game *game);
void draw_score(Game *game);

void print_game_over(Game *game);

#endif