#ifndef __GAMEUTILS__
#define __GAMEUTILS__

#include <MLV/MLV_all.h>
#include <MLV/MLV_time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../include/const.h"
#include "../include/struct_entity.h"

Game *create_game();
double normal_delay(double mean);
void free_all(Game *game);

#endif